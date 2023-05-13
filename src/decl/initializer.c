#include "initializer.h"

#include "stmt/tree.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "const_expr.h"

#include "../symtab/static_val.h"

static int     initializer_level = 0;
static uint8_t initializer_error = 0;
static int32_t initializer_count = 0; // used for finalizing arrays of unspec length

static int32_t total_init_count  = 0; // used for initializer list node

void FullInitialization(){
  if(current_obj_definition && (current_obj_definition->specifier & STORAGE_FETCH) == STORAGE_AUTO){
    TreeInsertNode(tree, INITIALIZER_LIST, total_init_count);
    total_init_count = 0; 

    Statement();
  }

  if(initializer_error != 0) {
    initializer_error = 0;
    return;
  }
  if(current_obj_definition->type->type == TYPE_ARRAY_UNSPEC){
    current_obj_definition->type = StructArrayLengthSpecification(current_obj_definition->type, initializer_count);
  }

  current_obj_definition = 0;
}

static InitFrame* InitializeInitFrame(Struct* type){
  type = StructGetUnqualified(type);

  if(StructIsStructOrUnion(type)){
    InitFrame* init_frame = InitFrameCreateEmpty();

    init_frame->type = StructGetUnqualified(type);
    init_frame->kind  = INIT_FIELDS;
    init_frame->field = init_frame->type->obj->members.first;
  }
  else if(StructIsArray(type)){
    InitFrame* init_frame = InitFrameCreateEmpty();

    init_frame->type = StructGetUnqualified(type);
    init_frame->kind  = INIT_ARRAY;
    init_frame->index = 0;
  }
  else return 0;
}

static void InitFrameAdvance(InitFrame* init_frame){
  if(init_frame->kind == INIT_FIELDS){
    init_frame->field = init_frame->field->next;
    if(init_frame->field) init_frame->offset = ((Obj*)init_frame->field->info)->address;
  }
  else if(init_frame->kind == INIT_ARRAY){
    init_frame->index++;
    init_frame->offset = init_frame->index * StructGetParentUnqualified(init_frame->type)->size;
  }
}

static void InitializerCleanup(){
  while(!StackEmpty(&initializer_stack)){
    InitFrameDrop(StackPop(&initializer_stack));
  }

  initializer_error = 1;
  initializer_level = 0;
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

    new_frame->parent_offset = current_frame->parent_offset + current_frame->offset;
    StackPush(&initializer_stack, new_frame);
  }
  else if(current_frame->kind == INIT_ARRAY){
    InitFrame* new_frame = InitializeInitFrame(current_frame->type->parent);
    if(new_frame == 0){
      ReportError("Illegal initializer.");
      InitializerCleanup();
      return;
    }

    new_frame->parent_offset = current_frame->parent_offset + current_frame->offset;
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

static void InitializerAuto(TreeNode* expression, Struct* current_type, int offset){
  // expression is not on the tree stack

  if(StructIsArithmetic(current_type) && StructIsArithmetic(expression->expr_node->type)){

    StackPush(&tree->stack, expression);
    TreeNode* node = TreeInsertNode(tree, INITIALIZER, 1);
    ExprNode* expr_node = ExprNodeCreateEmpty();
    expr_node->kind = LVALUE;
    expr_node->obj_ref = current_obj_definition;
    expr_node->address = offset;
    expr_node->type = current_type;

    node->expr_node = expr_node;

    total_init_count++;

    if(initializer_level == 1) initializer_count++;

  }
  else if(StructIsPointer(current_type) && 
      (StructIsPointer(expression->expr_node->type) || IsNullPointer(expression->expr_node))){

    if(!IsNullPointer(expression->expr_node) 
        && !StructIsCompatible(
          StructGetParentUnqualified(current_type), 
          StructGetParentUnqualified(expression->expr_node->type)
        )
        && !StructIsVoidPtr(expression->expr_node->type)){

      TreeNodeDrop(expression);
      ReportError("Incompatible types for initialization.");
      InitializerCleanup();
      return;
    }

    // check if pointed types have compatible qualifications
    int qualifiers1 = current_type->parent->kind == STRUCT_QUALIFIED 
      ? current_type->parent->attributes : 0;
    int qualifiers2 = expression->expr_node->type->parent->kind == STRUCT_QUALIFIED
      ? expression->expr_node->type->parent->attributes : 0;

    if(qualifiers1 != (qualifiers1 | qualifiers2)){
      TreeNodeDrop(expression);
      ReportError("Pointed objects qualifications are not compatible for initialization.");
      InitializerCleanup();
      return;
    }
    
    StackPush(&tree->stack, expression);
    TreeNode* node = TreeInsertNode(tree, INITIALIZER, 1);
    ExprNode* expr_node = ExprNodeCreateEmpty();
    expr_node->kind = LVALUE;
    expr_node->obj_ref = current_obj_definition;
    expr_node->address = offset;
    expr_node->type = current_type;

    node->expr_node = expr_node;

    total_init_count++;

    if(initializer_level == 1) initializer_count++;
  }
  else {
    TreeNodeDrop(expression);
    ReportError("Incompatible types for initialization.");
    InitializerCleanup();
    return;
  }

  if(!StackEmpty(&initializer_stack)) InitFrameAdvance(StackPeek(&initializer_stack));
}

static void InitializerStatic(TreeNode* expression, Struct* current_type, int offset){
  // expression is not on the tree stack

  ConstExpr const_expr = ConstExprCalculate(expression);
  Struct*   expr_type  = expression->expr_node->type;
  int       expr_is_null = IsNullPointer(expression->expr_node);
  TreeNodeDrop(expression);

  if(StructIsArithmetic(current_type)){

    if(~const_expr.type & CONST_EXPR_ARITHMETIC) {
      ReportError("Incompatible types for initialization.");
      InitializerCleanup();
      return;
    }

    StaticVal* static_val = StaticValCreateEmpty();
    static_val->type   = VAL_ARITHM;
    static_val->offset = offset;
    static_val->size   = current_type->size;
    static_val->value  = const_expr.value;

    StaticValAddToList(static_val, current_obj_definition->init_vals);

    if(initializer_level == 1) initializer_count++;

  }
  else if(StructIsPointer(current_type)){

    if(~const_expr.type & CONST_EXPR_ADDRESS
        && ~const_expr.type & CONST_EXPR_STRING) {
      ReportError("Incompatible types for initialization.");
      InitializerCleanup();
      return;
    }

    if(!expr_is_null
        && !StructIsCompatible(StructGetParentUnqualified(current_type), StructGetParentUnqualified(expr_type))
        && !StructIsVoidPtr(StructGetUnqualified(expr_type))){
      ReportError("Incompatible types for initialization.");
      InitializerCleanup();
      return;
    }

    // check if pointed types have compatible qualifications
    int qualifiers1 = current_type->kind == STRUCT_QUALIFIED 
      ? current_type->attributes : 0;
    int qualifiers2 = expression->expr_node->type->kind == STRUCT_QUALIFIED
      ? expression->expr_node->type->attributes : 0;

    if(qualifiers1 != (qualifiers1 | qualifiers2)){
      TreeNodeDrop(expression);
      ReportError("Pointed objects qualifications are not compatible for initialization.");
      InitializerCleanup();
      return;
    }

    StaticVal* static_val = StaticValCreateEmpty();
    static_val->type       = const_expr.type & CONST_EXPR_ADDRESS ? VAL_ADDRESS : VAL_STRING;
    static_val->offset     = offset;
    static_val->size       = current_type->size;
    static_val->value      = const_expr.value;
    static_val->obj_ref    = const_expr.obj_ref;
    static_val->string_ref = const_expr.string_ref;

    StaticValAddToList(static_val, current_obj_definition->init_vals);

    if(initializer_level == 1) initializer_count++;
  }
  else {
    ReportError("Incompatible types for initialization.");
    InitializerCleanup();
    return;
  }

  if(!StackEmpty(&initializer_stack)) InitFrameAdvance(StackPeek(&initializer_stack));
}

void Initializer(){
  if(initializer_error) {
    TreeNodeDrop(StackPop(&tree->stack));
    return;
  }

  TreeNode* expression = StackPop(&tree->stack);
  Struct* current_type = 0;
  int offset = 0;

  if(current_obj_definition == 0){
    TreeNodeDrop(expression);
    InitializerCleanup();
    return;
  }

  if(StackEmpty(&initializer_stack)){
    current_type = StructGetUnqualified(current_obj_definition->type);
  }
  else{
    InitFrame* init_frame = StackPeek(&initializer_stack);
    if(init_frame->kind == INIT_FIELDS){
      if(init_frame->field == 0 || init_frame->field->info == 0){
        ReportError("Illegal initializer.");
        TreeNodeDrop(expression);
        InitializerCleanup();
        return;
      }
      Obj* current_member = init_frame->field->info;
      current_type = StructGetUnqualified(current_member->type);
    }
    else if(init_frame->kind == INIT_ARRAY){
      if(init_frame->type->attributes > 0 &&
          init_frame->index >= init_frame->type->attributes){
        ReportError("Illegal initializer.");
        TreeNodeDrop(expression);
        InitializerCleanup();
        return;
      }
      current_type = StructGetParentUnqualified(init_frame->type);
    }
    offset = init_frame->offset + init_frame->parent_offset;
  }

  if(expression->expr_node == 0) { // there is an error in the expression
    // ReportError("Error in the initializer."); // error detected earlier
    TreeNodeDrop(expression);
    InitializerCleanup();
    return;
  }

  if(StructIsArray(expression->expr_node->type)
      || StructIsFunction(expression->expr_node->type)){
    expression = ExprToPointer(expression);
  }

  if((current_obj_definition->specifier & STORAGE_FETCH) == STORAGE_AUTO) 
    InitializerAuto(expression, current_type, offset);
  if((current_obj_definition->specifier & STORAGE_FETCH) == STORAGE_STATIC)
    InitializerStatic(expression, current_type, offset);

}