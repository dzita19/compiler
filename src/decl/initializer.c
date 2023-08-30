#include "initializer.h"

#include "stmt/tree.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "stmt/fold.h"

#include "../symtab/static_val.h"

static int     initializer_level = 0;
static uint8_t initializer_error = 0;
static int32_t initializer_count = 0; // used for finalizing arrays of unspec length

static int32_t total_init_count  = 0; // used for initializer list node

void FullInitialization(){
  if(current_obj_definition && (current_obj_definition->specifier & STORAGE_FETCH) == STORAGE_AUTO){
    TreeInsertNode(tree, INITIALIZATION, total_init_count);
    total_init_count = 0;

    Statement();
  }

  if(initializer_error != 0) {
    initializer_error = 0;
    initializer_count = 0;
    current_obj_definition = 0;
    return;
  }
  if(current_obj_definition->type->type == TYPE_ARRAY_UNSPEC){
    current_obj_definition->type = StructArrayLengthSpecification(current_obj_definition->type, initializer_count);
    if((current_obj_definition->specifier & STORAGE_FETCH) == STORAGE_STATIC
        && (current_obj_definition->specifier & LINKAGE_FETCH) == LINKAGE_NONE){

      extern int reserve_unnamed_static(Struct*);
      current_obj_definition->address = reserve_unnamed_static(current_obj_definition->type);
    }
    if((current_obj_definition->specifier & STORAGE_FETCH) == STORAGE_AUTO){
      extern int reserve_storage_stack(Struct*);
      current_obj_definition->address = reserve_storage_stack(current_obj_definition->type);
    }
  }

  initializer_count = 0;
  current_obj_definition = 0;
}

static InitFrame* InitializeInitFrame(Struct* type){
  type = StructGetUnqualified(type);

  if(StructIsStructOrUnion(type)){
    InitFrame* init_frame = InitFrameCreateEmpty();

    init_frame->type = StructGetUnqualified(type);
    init_frame->kind  = INIT_FIELDS;
    init_frame->field = init_frame->type->obj->members.first;

    return init_frame;
  }
  else if(StructIsArray(type)){
    InitFrame* init_frame = InitFrameCreateEmpty();

    init_frame->type = StructGetUnqualified(type);
    init_frame->kind  = INIT_ARRAY;
    init_frame->index = 0;

    return init_frame;
  }
  else return 0;
}

static void InitFrameAdvance(InitFrame* init_frame){
  if(init_frame->kind == INIT_FIELDS){
    init_frame->field = init_frame->field->next;
    // if(init_frame->field) init_frame->offset = ((Obj*)init_frame->field->info)->address;
  }
  else if(init_frame->kind == INIT_ARRAY){
    init_frame->index++;
    // init_frame->offset = init_frame->index * StructGetParentUnqualified(init_frame->type)->size;
  }
}

static void InitializerCleanup(void){
  while(!StackEmpty(&initializer_stack)){
    InitFrameDrop(StackPop(&initializer_stack));
  }

  initializer_error = 1;
  initializer_level = 0;
}

static void InitializerPushObj(void){
  StackNode* stack_node = initializer_stack.top;
  LinkedList list = (LinkedList){ 0, 0 };
  while(stack_node){
    Node* node = NodeCreateEmpty();
    node->info = stack_node->info;
    LinkedListInsertFirst(&list, node); // inserts every InitFrame*
    stack_node = stack_node->next;
  }

  TreeNode* primary = TreeInsertNode(tree, ADDRESS_PRIMARY, 0);

  primary->expr_node = ExprNodeCreateEmpty();
  primary->expr_node->type = StructToPtr(current_obj_definition->type);
  primary->expr_node->kind = ADDRESS_OF;
  primary->expr_node->obj_ref = current_obj_definition;

  for(Node* node = list.first; node; node = node->next){
    InitFrame* init_frame = node->info;

    if(init_frame->kind == INIT_FIELDS){
      TreeNode* field_ref = StackPeek(&tree->stack);
      Obj* member = init_frame->field->info;

      field_ref->expr_node->address += member->address;
      field_ref->expr_node->type     = StructToPtr(member->type);
    }
    else if(init_frame->kind == INIT_ARRAY){
      TreeNode* array_ref = StackPeek(&tree->stack);

      array_ref->expr_node->address += init_frame->index * init_frame->type->parent->size;
      array_ref->expr_node->type     = StructToPtr(init_frame->type->parent);
    }
  }

  extern void DerefExpr(void);
  DerefExpr();

  LinkedListDelete(&list);
}

static void InitializerStatic(void){
  TreeNode* initializer  = StackPop(&tree->stack);
  if(initializer->expr_node == 0) {
    TreeNodeDrop(initializer);
    return; // return if error in basic assignment
  }

  // get offset from lval of the assignment
  int        offset       = initializer->children[0]->children[0]->expr_node->address;
  Struct*    current_type = initializer->children[1]->expr_node->type;

  StackPush(&tree->stack, initializer->children[1]); // push right-hand side of the assignment 
  ConstExpression();
  ConstExpr* const_expr   = StackPop(&const_expr_stack);

  initializer->children[1] = 0;
  TreeNodeDrop(initializer);

  if(StructIsArithmetic(current_type) || StructIsPointer(current_type)){ // type is compatible (checked in basic assignment)
    if(const_expr->kind == VAL_ERROR) {
      ReportError("Incompatible types for initialization of object %s.", current_obj_definition->name);
      ConstExprDrop(const_expr);
      InitializerCleanup();
      return;
    }

    StaticVal* static_val = StaticValCreateEmpty();
    static_val->kind       = const_expr->kind;
    static_val->offset     = offset;
    static_val->size       = current_type->size;
    static_val->value      = const_expr->value;
    static_val->obj_ref    = const_expr->obj_ref;
    static_val->string_ref = const_expr->string_ref;

    StaticValAddToList(static_val, current_obj_definition->init_vals);
  }

  ConstExprDrop(const_expr);
}

void InitializerOpen(){
  if(initializer_error) return;

  initializer_level++;

  if(StackEmpty(&initializer_stack)){
    if(current_obj_definition == 0){
      InitializerCleanup();
      return;
    }

    InitFrame* init_frame = InitializeInitFrame(current_obj_definition->type);
    if(init_frame == 0){
      ReportError("Illegal initializer.");
      InitializerCleanup();
      return;
    }

    StackPush(&initializer_stack, init_frame);
    return;
  }

  InitFrame* current_frame = StackPeek(&initializer_stack);
  if(current_frame->kind == INIT_FIELDS){
    Obj* current_type_obj = current_frame->field->info;
    InitFrame* new_frame = InitializeInitFrame(current_type_obj->type);
    if(new_frame == 0){
      ReportError("Illegal initializer.");
      InitializerCleanup();
      return;
    }

    // new_frame->parent_offset = current_frame->parent_offset + current_frame->offset;
    StackPush(&initializer_stack, new_frame);
  }
  else if(current_frame->kind == INIT_ARRAY){
    InitFrame* new_frame = InitializeInitFrame(current_frame->type->parent);
    if(new_frame == 0){
      ReportError("Illegal initializer.");
      InitializerCleanup();
      return;
    }

    // new_frame->parent_offset = current_frame->parent_offset + current_frame->offset;
    StackPush(&initializer_stack, new_frame);
  }
  else{
    ReportError("Illegal initializer.");
  }
}

void InitializerClose(){
  if(initializer_error) return;

  initializer_level--;
  if(initializer_level == 1) initializer_count++;

  InitFrameDrop(StackPop(&initializer_stack));

  if(!StackEmpty(&initializer_stack)) InitFrameAdvance(StackPeek(&initializer_stack));
}

void Initializer(){
  if(initializer_error) {
    TreeNodeDrop(StackPop(&tree->stack));
    return;
  }

  TreeNode* expression = StackPop(&tree->stack);
  // Struct* current_type = 0;

  // ok
  if(current_obj_definition == 0){
    TreeNodeDrop(expression);
    InitializerCleanup();
    return;
  }

  // ok
  if(!StackEmpty(&initializer_stack)){
    InitFrame* init_frame = StackPeek(&initializer_stack);
    if(init_frame->kind == INIT_FIELDS){
      if(init_frame->field == 0 || init_frame->field->info == 0){
        ReportError("Illegal initializer.");
        TreeNodeDrop(expression);
        InitializerCleanup();
        return;
      }
    }
    else if(init_frame->kind == INIT_ARRAY){
      if(init_frame->type->attributes > 0 &&
          init_frame->index >= init_frame->type->attributes){
        ReportError("Illegal initializer.");
        TreeNodeDrop(expression);
        InitializerCleanup();
        return;
      }
    }
  }

  InitializerPushObj(); // push treenode representing current lval in obj
  StackPush(&tree->stack, expression);

  extern void BasicAssignExpr(int);
  BasicAssignExpr(1);

  if(initializer_level == 1) initializer_count++;

  if((current_obj_definition->specifier & STORAGE_FETCH) == STORAGE_AUTO)
    total_init_count++;
  else
    InitializerStatic();
  
  if(!StackEmpty(&initializer_stack)) InitFrameAdvance(StackPeek(&initializer_stack));
}