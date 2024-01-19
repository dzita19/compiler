#include "initializer.h"

#include "stmt/tree.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "stmt/fold.h"

#include <string.h>

// error - only in case there is an error inside initializer logic
// if there is an error regarding expected type of initializer expression, it's NOT CONSIDER AN ERROR OF THIS KIND
// in that case, initializer will be analyzed as if nothing is wrong with it

// this kind of error can be triggered only by:
// - type to be initialized is incomplete or is NULL - don't check incoming expressions
// - forwarding a member cannot be performed as the member is the last one 
//   this is only a case for expl openned ones - don't check incoming expressions
//   because impl openned ones are implicitely closed



static void ZeroInitializeAllMembers(LinkedList* list, Struct* type, int offset){
  type = StructGetUnqualified(type);

  if(StructIsArray(type)){
    for(int i = 0; i < type->attributes; i++){
      ZeroInitializeAllMembers(list, type->parent, offset + type->parent->size * i);
    }
  }
  else if(StructIsStruct(type)){
    for(Node* node = type->obj->members.first; node; node = node->next){
      Obj* member = node->info;
      ZeroInitializeAllMembers(list, member->type, offset + member->address);
    }
  }
  else if(StructIsUnion(type)){
    ZeroInitializeAllMembers(list, type->obj->members.first->info, offset);
  }
  else if(StructIsScalar(type)){
    InitVal* init_val = InitValCreateEmpty();

    TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);
    node->expr_node = ExprNodeCreateEmpty();
    node->expr_node->address = 0;
    node->expr_node->type    = type;
    node->expr_node->kind    = NUM_LITERAL;

    init_val->expression = StackPop(&tree->stack);
    init_val->offset = offset;
    init_val->size   = type->size;
    InitValAddToList(init_val, list);
  }
}

// types are always unqualified

// drop all InitFrames if error
// always insert one initialization node (even if empty)
void FullInitialization(void){
  
  if(init_error_stack.top->info){
    Stack* init_frames = StackPeek(&init_frame_stack);
    while(!StackEmpty(init_frames)){
      InitFrameDrop(StackPop(init_frames));
    }

    LinkedList* initializer_list = StackPeek(&initializer_stack);
    for(Node* node = initializer_list->first; node; node = node->next){
      InitValDrop(node->info);
    }

    TreeInsertNode(tree, INITIALIZATION, 0);
  }
  // transform linked list into initialization expression
  // or store it inside a static object
  else{
    // non-static initializer
    if(!StackPeek(&init_attrib_stack)){

      LinkedList* initializer_list = StackPeek(&initializer_stack);
      int initializer_counter = 0;

      Obj* current_obj_definition = StackPeek(&obj_definiton_stack);

      if(current_obj_definition->type->type == TYPE_ARRAY_UNSPEC){
        int size_specification = (int)(long)init_size_stack.top->info;
        current_obj_definition->type = StructArrayLengthSpecification(current_obj_definition->type, size_specification);
      }

      // initialize all members at least with zero
      LinkedList* resovled_initializers = LinkedListCreateEmpty();
      ZeroInitializeAllMembers(resovled_initializers, current_obj_definition->type, 0);

      Node* current_node = initializer_list->first;
      while(current_node){
        InitValAddToList(current_node->info, resovled_initializers);
        Node* old_node = current_node;
        current_node = old_node->next;

        NodeDrop(LinkedListRemoveFirst(initializer_list));
      }

      for(Node* node = resovled_initializers->first; node; node = node->next){
        InitVal* init_val = node->info;

        // push address of initialized object
        TreeNode* primary = TreeInsertNode(tree, ADDRESS_PRIMARY, 0);

        primary->expr_node = ExprNodeCreateEmpty();
        primary->expr_node->type = StructToPtr(init_val->expression->expr_node->type);
        primary->expr_node->kind = ADDRESS_OF;
        primary->expr_node->obj_ref = current_obj_definition;
        primary->expr_node->address = init_val->offset;

        extern void DerefExpr(void);
        extern void SimpleAssignExpr(int);

        // deref, push expression, assign
        DerefExpr();
        StackPush(&tree->stack, init_val->expression);
        SimpleAssignExpr(1);

        initializer_counter++;

        init_val->expression = NULL;
        InitValDrop(init_val);
      }

      LinkedListDrop(resovled_initializers);

      TreeInsertNode(tree, INITIALIZATION, initializer_counter);
    }
    else{
      LinkedList* initializer_list = StackPeek(&initializer_stack);
      int correct = 1;

      for(Node* node = initializer_list->first; node; node = node->next){
        InitVal* init_val = node->info;

        if(init_val->expression->production == CONSTANT_PRIMARY
            || init_val->expression->production == STRING_PRIMARY){
          // all good
        }
        else if(init_val->expression->production == ADDRESS_PRIMARY
            || init_val->expression->production == COMPOUND_LITERAL){
          if((init_val->expression->expr_node->obj_ref->specifier & STORAGE_FETCH) != STORAGE_STATIC){
            ReportError("Static object cannot be initialized by non-const expression.");
            correct = 0;
            break;
          }
        }
        else {
          ReportError("Static object cannot be initialized by non-const expression.");
          correct = 0;
          break;
        }
      }

      if(correct){
        Obj* current_obj_definition = StackPeek(&obj_definiton_stack);

        if(current_obj_definition->type->type == TYPE_ARRAY_UNSPEC){
          int size_specification = (int)(long)init_size_stack.top->info;
          current_obj_definition->type = StructArrayLengthSpecification(current_obj_definition->type, size_specification);
        }

        // set all members at least to zero
        LinkedList* resovled_initializers = LinkedListCreateEmpty();
        ZeroInitializeAllMembers(resovled_initializers, current_obj_definition->type, 0);

        Node* current_node = initializer_list->first;
        while(current_node){
          InitValAddToList(current_node->info, resovled_initializers);
          Node* old_node = current_node;
          current_node = old_node->next;

          NodeDrop(LinkedListRemoveFirst(initializer_list));
        }
        
        for(Node* node = resovled_initializers->first; node; node = node->next){
          Node* new_node = NodeCreateEmpty();
          new_node->info = node->info;
          LinkedListInsertLast(current_obj_definition->init_vals, new_node);
        }

        LinkedListDrop(resovled_initializers);
      }
      else{
        for(Node* node = initializer_list->first; node; node = node->next){
          InitValDrop(node->info);
        }
      }

      TreeInsertNode(tree, INITIALIZATION, 0);
    }
  }
  
}

void NotCompoundLiteral(void){
  StackPop(&obj_definiton_stack); // #1
  LinkedListDrop(StackPop(&initializer_stack)); // #2
  StackDrop(StackPop(&init_frame_stack)); // #3
  StackPop(&init_attrib_stack); // #4
  StackPop(&init_error_stack); // #5
  StackPop(&init_size_stack); // #6

  // can't be added in full initializer because it's unknown whether it's regular initializer or compound literal
  Statement();
}


// ignore functions and incomplete types
void InitializerOpen(void){
  if(init_error_stack.top->info) {
    return;
  }

  Stack* init_frames = StackPeek(&init_frame_stack);
  InitFrame* current_init_frame = StackPeek(init_frames);

  if(current_init_frame->type == 0) {
    ReportError("Cannot open nested initializer.");
    init_error_stack.top->info = (void*)(long)1;
    return; // ERROR
  }

  InitFrame* temp_init_frame = StackPop(init_frames);
  if(!StackEmpty(init_frames)){
    InitFrame* one_before_init_frame = StackPeek(init_frames);
    if(one_before_init_frame->type->type == TYPE_ARRAY_UNSPEC){
      int initializer_size = one_before_init_frame->index + 1;
      if(initializer_size > (int)(long)init_size_stack.top->info){
        init_size_stack.top->info = (void*)(long)initializer_size;
      }
    }
  }
  StackPush(init_frames, temp_init_frame);

  Struct* type = StructGetUnqualified(current_init_frame->type);

  if(StructIsArray(type)){
    if(type->type != TYPE_ARRAY_UNSPEC && current_init_frame->index >= type->attributes){
      ReportError("Excess array member.");
      init_error_stack.top->info = (void*)(long)1;
      return; // ERROR
    }
    else{
      InitFrame* new_init_frame = InitFrameCreateEmpty();
      InitFrameInitializeWithType(new_init_frame, type->parent, 0);
      current_init_frame->xopen = current_init_frame->xopen == INIT_FRAME_FIRST_ACTIVE 
        ? INIT_FRAME_FIRST_OPEN 
        : INIT_FRAME_EXPLICIT_OPEN;
        
      StackPush(init_frames, new_init_frame);
    }
  }
  else if(StructIsStruct(type)){
    if(current_init_frame->field == NULL){
      ReportError("Excess struct member.");
      init_error_stack.top->info = (void*)(long)1;
      return; // ERROR
    }
    else{
      InitFrame* new_init_frame = InitFrameCreateEmpty();
      Obj* field_obj = current_init_frame->field->info;
      InitFrameInitializeWithType(new_init_frame, field_obj->type, 0);
      current_init_frame->xopen = current_init_frame->xopen == INIT_FRAME_FIRST_ACTIVE 
        ? INIT_FRAME_FIRST_OPEN 
        : INIT_FRAME_EXPLICIT_OPEN;
        
      StackPush(init_frames, new_init_frame);
    }
  }
  // same as struct
  else if(StructIsUnion(type)){
    if(current_init_frame->field == NULL){
      ReportError("Excess struct member.");
      init_error_stack.top->info = (void*)(long)1;
      return; // ERROR
    }
    else{
      InitFrame* new_init_frame = InitFrameCreateEmpty();
      Obj* field_obj = current_init_frame->field->info;
      InitFrameInitializeWithType(new_init_frame, field_obj->type, 0);
      current_init_frame->xopen = current_init_frame->xopen == INIT_FRAME_FIRST_ACTIVE 
        ? INIT_FRAME_FIRST_OPEN 
        : INIT_FRAME_EXPLICIT_OPEN;
        
      StackPush(init_frames, new_init_frame);
    }
  }
  else if(StructIsScalar(type)){
    if(current_init_frame->xopen == INIT_FRAME_FIRST_ACTIVE){
      InitFrame* new_init_frame = InitFrameCreateEmpty();
      InitFrameInitializeWithType(new_init_frame, type, 0);
      current_init_frame->xopen = INIT_FRAME_EXPLICIT_OPEN;
        
      StackPush(init_frames, new_init_frame);
    }
    else {
      ReportError("Cannot open nested initializer for scalar objects.");
      init_error_stack.top->info = (void*)(long)1;
      return; // ERROR
    }
  }
}

static int ShouldBeClosed(InitFrame* init_frame){
  return init_frame->xopen == INIT_FRAME_IMPLICIT_OPEN;
}

// current frame on top of the stack is the one that should be advanced
static int Advance(void){
  Stack* init_frames = StackPeek(&init_frame_stack);
  
  while(1){
    if(StackEmpty(init_frames)) break; // nothing to advance
    InitFrame* current_init_frame = StackPeek(init_frames);

    Struct* type = StructGetUnqualified(current_init_frame->type);

    if(StructIsArray(type)){
      current_init_frame->index++;
      if(type->type != TYPE_ARRAY_UNSPEC && current_init_frame->index >= type->attributes){
        if(ShouldBeClosed(current_init_frame)){
          InitFrameDrop(StackPop(init_frames));
        }
        else{
          InitFrame* new_init_frame = InitFrameCreateEmpty();
          new_init_frame->xopen = INIT_FRAME_ACTIVE;

          StackPush(init_frames, new_init_frame);
          break;
        }
      }
      else{
        InitFrame* new_init_frame = InitFrameCreateEmpty();
        InitFrameInitializeWithType(new_init_frame, type->parent, 0);
          
        StackPush(init_frames, new_init_frame);
        break;
      }
    }
    else if(StructIsStruct(type)){
      current_init_frame->field = current_init_frame->field->next;
      if(current_init_frame->field == NULL){
        if(ShouldBeClosed(current_init_frame)){
          InitFrameDrop(StackPop(init_frames));
        }
        else{
          InitFrame* new_init_frame = InitFrameCreateEmpty();
          new_init_frame->xopen = INIT_FRAME_ACTIVE;

          StackPush(init_frames, new_init_frame);
          break;
        }
      }
      else{
        InitFrame* new_init_frame = InitFrameCreateEmpty();
        Obj* field_obj = current_init_frame->field->info;
        InitFrameInitializeWithType(new_init_frame, field_obj->type, 0);
          
        StackPush(init_frames, new_init_frame);
        break;
      }
    }
    else if(StructIsUnion(type)){
      if(ShouldBeClosed(current_init_frame)){
        InitFrameDrop(StackPop(init_frames));
      }
      else{
        InitFrame* new_init_frame = InitFrameCreateEmpty();
        new_init_frame->xopen = INIT_FRAME_ACTIVE;
          
        StackPush(init_frames, new_init_frame);
        break;
      }
    }
    else if(StructIsScalar(type)){
      InitFrame* new_init_frame = InitFrameCreateEmpty();
      new_init_frame->xopen = INIT_FRAME_ACTIVE;

      StackPush(init_frames, new_init_frame);
      break;
    }
  }

  return 0;
}

void InitializerClose(void){
  if(init_error_stack.top->info){
    return;
  }

  Stack* init_frames = StackPeek(&init_frame_stack);

  // close until we hit explicit frame
  while(1){
    InitFrame* current_init_frame = StackPeek(init_frames);

    if(current_init_frame->xopen == INIT_FRAME_IMPLICIT_OPEN
        || current_init_frame->xopen == INIT_FRAME_ACTIVE
        || current_init_frame->xopen == INIT_FRAME_ACTIVE_DESIGNATED){
      InitFrameDrop(StackPop(init_frames));
    }
    else{ // for explicit open
      break;
    }
  }

  // remove explicite open frame (or open scalar frame)
  InitFrameDrop(StackPop(init_frames));

  // advance
  Advance();
}

static int CalculateInitializerOffset(void){
  Stack* init_frames = StackPeek(&init_frame_stack);
  StackNode* current_init_frame_wrapper = init_frames->top;

  int offset = 0;

  current_init_frame_wrapper = current_init_frame_wrapper->next;

  while(current_init_frame_wrapper){
    InitFrame* current_init_frame = current_init_frame_wrapper->info;
    if(StructIsArray(current_init_frame->type)){
      offset += current_init_frame->index * current_init_frame->type->parent->size;
    }
    else if(StructIsStruct(current_init_frame->type)){
      Obj* current_member = current_init_frame->field->info;
      offset += current_member->address;
    }

    current_init_frame_wrapper = current_init_frame_wrapper->next;
  }

  return offset;
}

// drop one expression on error
void Initializer(void){
  if(init_error_stack.top->info){
    TreeNodeDrop(StackPop(&tree->stack));
    return;
  }

  Stack* init_frames = StackPeek(&init_frame_stack);

  // CHECK IF ASSIGNMENT IS CORRECT

  InitFrame* current_init_frame = StackPeek(init_frames);

  if(current_init_frame->type == NULL){
    ReportError("Cannot initialize excess member.");
    TreeNodeDrop(StackPop(&tree->stack));
    init_error_stack.top->info = (void*)(long)1;
    return;
  }

  InitFrame* temp_init_frame = StackPop(init_frames);
  if(!StackEmpty(init_frames)){
    InitFrame* one_before_init_frame = StackPeek(init_frames);
    if(one_before_init_frame->type->type == TYPE_ARRAY_UNSPEC){
      int initializer_size = one_before_init_frame->index + 1;
      if(initializer_size > (int)(long)init_size_stack.top->info){
        init_size_stack.top->info = (void*)(long)initializer_size;
      }
    }
  }
  StackPush(init_frames, temp_init_frame);

  TreeNode* initializer_expression = StackPop(&tree->stack);
  // after this point, initializer_expression is owned by this function
  
  if(StructIsArray(initializer_expression->expr_node->type)
      || StructIsFunction(initializer_expression->expr_node->type)){
    initializer_expression = ConvertTreeNodeToPointer(initializer_expression);
  }

  while(1){
    current_init_frame = StackPeek(init_frames);
    Struct* current_type = StructGetUnqualified(current_init_frame->type); // to be sure
    Struct* expression_type = StructGetUnqualified(initializer_expression->expr_node->type);

    AssignStatus assign_status = StructIsAssignable(current_type, 
      expression_type,
      IsNullPointer(initializer_expression->expr_node));

    if(assign_status == ASSIGN_OK){
      initializer_expression = ConvertTreeNodeToArithmetic(initializer_expression);
      initializer_expression = ExprImplCast(initializer_expression, current_type);

      InitVal* init_val = InitValCreateEmpty();
      init_val->offset = CalculateInitializerOffset();
      init_val->size   = current_init_frame->type->size;
      init_val->expression = initializer_expression;
      
      Node* new_node = NodeCreateEmpty();
      new_node->info = init_val;

      LinkedListInsertLast(StackPeek(&initializer_stack), new_node);
      break;
    }
    else{
      if(StructIsArray(current_type)){
        InitFrame* new_init_frame = InitFrameCreateEmpty();
        InitFrameInitializeWithType(new_init_frame, current_type->parent, 0);
        current_init_frame->xopen = INIT_FRAME_IMPLICIT_OPEN;

        StackPush(init_frames, new_init_frame);
      }
      else if(StructIsStruct(current_type)){
        InitFrame* new_init_frame = InitFrameCreateEmpty();
        Obj* current_member = current_init_frame->field->info;
        InitFrameInitializeWithType(new_init_frame, current_member->type, 0);
        current_init_frame->xopen = INIT_FRAME_IMPLICIT_OPEN;

        StackPush(init_frames, new_init_frame);
      }
      else if(StructIsUnion(current_type)){
        InitFrame* new_init_frame = InitFrameCreateEmpty();
        Obj* current_member = current_init_frame->field->info;
        InitFrameInitializeWithType(new_init_frame, current_member->type, 0);
        current_init_frame->xopen = INIT_FRAME_IMPLICIT_OPEN;

        StackPush(init_frames, new_init_frame);
      }
      else if(StructIsScalar(current_type)){
        switch(assign_status){
        case ASSIGN_OK: break; // impossible
        case ASSIGN_ERROR_INCOMPATIBLE_TYPES:
          ReportError("Incompatible types for initialization.");
          break;
        case ASSIGN_ERROR_POINTER_INCOMPATIBLE:
          ReportError("Incompatible pointer types for initialization.");
          break;
        case ASSIGN_ERROR_POINTER_QUALIFICATION:
          ReportError("Pointed objects qualifications are not compatible for initialization.");
          break;
        }

        TreeNodeDrop(initializer_expression);
        init_error_stack.top->info = (void*)(long)1;
        return;
      }
    }
  }

  // ADVANCE
  InitFrameDrop(StackPop(init_frames));
  Advance();
}

void FieldDesignatorOpen(void){
  TypeFrame* type_frame = StackPeek(&type_stack);
  type_frame->identifier_expected = 1;
}

void FieldDesignator(void){
  TypeFrame* type_frame = StackPeek(&type_stack);
  type_frame->identifier_expected = 0;

  if(init_error_stack.top->info){
    StringDrop(QueueDelete(&identifier_queue));
    return;
  }

  Stack* init_frames = StackPeek(&init_frame_stack);

  while(1){
    InitFrame* current_init_frame = StackPeek(init_frames);

    if(current_init_frame->xopen == INIT_FRAME_IMPLICIT_OPEN
        || current_init_frame->xopen == INIT_FRAME_ACTIVE){
      InitFrameDrop(StackPop(init_frames));
    }
    else if(current_init_frame->xopen == INIT_FRAME_ACTIVE_DESIGNATED){
      current_init_frame->xopen = INIT_FRAME_IMPLICIT_OPEN;
      break;
    }
    else{ // for explicit open
      break;
    }
  }

  InitFrame* current_init_frame = StackPeek(init_frames);
  
  const char* symbol_name = QueueDelete(&identifier_queue);

  if(StructIsStruct(current_init_frame->type)){
    Node* member_node = NULL;
    for(Node* node = current_init_frame->type->obj->members.first; node; node = node->next){
      Obj* member = node->info;
      if(strcmp(member->name, symbol_name) == 0){
        member_node = node;
        break;
      }
    }

    current_init_frame->field = member_node;

    if(member_node){
      InitFrame* new_init_frame = InitFrameCreateEmpty();
      Obj* field_obj = current_init_frame->field->info;
      InitFrameInitializeWithType(new_init_frame, field_obj->type, 0);
      new_init_frame->xopen = INIT_FRAME_ACTIVE_DESIGNATED;
      StackPush(init_frames, new_init_frame);

      StringDrop(symbol_name);
    }
    else{
      ReportError("Designated member doesn't exist.");
      init_error_stack.top->info = (void*)(long)1;
      StringDrop(symbol_name);
    }
  }
  else{
    ReportError("Cannot use field designator on type that is not struct-or-union.");
    init_error_stack.top->info = (void*)(long)1;
    StringDrop(symbol_name);
  }
}

void ArrayDesignator(void){
  if(init_error_stack.top->info){
    ConstExprDrop(StackPop(&const_expr_stack));
    return;
  }

  Stack* init_frames = StackPeek(&init_frame_stack);

  while(1){
    InitFrame* current_init_frame = StackPeek(init_frames);

    if(current_init_frame->xopen == INIT_FRAME_IMPLICIT_OPEN
        || current_init_frame->xopen == INIT_FRAME_ACTIVE){
      InitFrameDrop(StackPop(init_frames));
    }
    else if(current_init_frame->xopen == INIT_FRAME_ACTIVE_DESIGNATED){
      current_init_frame->xopen = INIT_FRAME_IMPLICIT_OPEN;
      break;
    }
    else{ // for explicit open
      break;
    }
  }

  InitFrame* current_init_frame = StackPeek(init_frames);

  ConstExpr* const_expr = StackPop(&const_expr_stack);

  if(StructIsArray(current_init_frame->type)){
    if(const_expr->kind != VAL_ARITHM || !StructIsArithmetic(const_expr->type)) {
      ReportError("Array designator must be a constant arithmetic value.");
      ConstExprDrop(const_expr);
      return;
    }

    current_init_frame->index = const_expr->value;
    if(current_init_frame->type->type != TYPE_ARRAY_UNSPEC
        && current_init_frame->index >= current_init_frame->type->attributes){
      ReportError("Designated array index exceeds array size.");
      init_error_stack.top->info = (void*)(long)1;
      ConstExprDrop(const_expr);
    }
    else{
      InitFrame* new_init_frame = InitFrameCreateEmpty();
      InitFrameInitializeWithType(new_init_frame, current_init_frame->type->parent, 0);
      new_init_frame->xopen = INIT_FRAME_ACTIVE_DESIGNATED;
        
      StackPush(init_frames, new_init_frame);
      ConstExprDrop(const_expr);
    }
  }
  else{
    ReportError("Cannot use array designator on type that is not array.");
    init_error_stack.top->info = (void*)(long)1;
    ConstExprDrop(const_expr);
  }
}