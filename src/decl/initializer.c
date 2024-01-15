#include "initializer.h"

#include "stmt/tree.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "stmt/fold.h"

// error - only in case there is an error inside initializer logic
// if there is an error regarding expected type of initializer expression, it's NOT CONSIDER AN ERROR OF THIS KIND
// in that case, initializer will be analyzed as if nothing is wrong with it

// this kind of error can be triggered only by:
// - type to be initialized is incomplete or is NULL - don't check incoming expressions
// - forwarding a member cannot be performed as the member is the last one 
//   this is only a case for expl openned ones - don't check incoming expressions
//   because impl openned ones are implicitely closed

// types are always unqualified

// static Stack initializer_count_stack       = { 0 }; // counts total number of initializer expressions

// drop all InitFrames if error
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
  }

  // transform linked list into initialization expression
  // or store it inside a static object
  else{
    // non-static initializer
    if(!StackPeek(&init_attrib_stack)){

      LinkedList* initializer_list = StackPeek(&initializer_stack);
      int initializer_counter = 0;

      for(Node* node = initializer_list->first; node; node = node->next){
        InitVal* init_val = node->info;

        Obj* current_obj_definition = StackPeek(&obj_definiton_stack);

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

      TreeInsertNode(tree, INITIALIZATION, initializer_counter);
      Statement();
    }
  }
  
}

void NotCompoundLiteral(void){
  StackPop(&obj_definiton_stack); // #1
  LinkedListDrop(StackPop(&initializer_stack)); // #2
  StackDrop(StackPop(&init_frame_stack)); // #3
  StackPop(&init_attrib_stack); // #4
  StackPop(&init_error_stack); // #5
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

  /*printf("Before opening: ");
  StructDump(current_init_frame->type);
  printf("\n"); fflush(stdout);*/

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

  /*printf("After opening: ");
  current_init_frame = StackPeek(init_frames);
  StructDump(current_init_frame->type);
  printf("\n"); fflush(stdout);*/
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

  /*printf("Before closing: ");
  InitFrame* current_init_frame = StackPeek(init_frames);
  StructDump(current_init_frame->type);
  printf("\n"); fflush(stdout);*/

  // close until we hit explicit frame
  while(1){
    InitFrame* current_init_frame = StackPeek(init_frames);
    if(current_init_frame->xopen == INIT_FRAME_IMPLICIT_OPEN
        || current_init_frame->xopen == INIT_FRAME_ACTIVE){
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

  /*printf("After closing: ");
  current_init_frame = !StackEmpty(init_frames) ? StackPeek(init_frames) : NULL;
  if(current_init_frame) StructDump(current_init_frame->type);
  else printf("Finished");
  printf("\n"); fflush(stdout);*/
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
  // InitFrame* current_init_frame = StackPeek(init_frames);

  /*printf("Before initializer: ");
  InitFrame* current_init_frame = StackPeek(init_frames);
  StructDump(current_init_frame->type);
  printf("\n"); fflush(stdout);*/

  // CHECK IF ASSIGNMENT IS CORRECT

  InitFrame* current_init_frame = StackPeek(init_frames);

  if(current_init_frame->type == NULL){
    ReportError("Cannot initialize excess member.");
    TreeNodeDrop(StackPop(&tree->stack));
    init_error_stack.top->info = (void*)(long)1;
    return;
  }

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

  // current_init_frame = StackPeek(init_frames);

  /*printf("After initializer: ");
  current_init_frame = !StackEmpty(init_frames) ? StackPeek(init_frames) : NULL;
  if(current_init_frame) StructDump(current_init_frame->type);
  else printf("Finished");
  printf("\n"); fflush(stdout);*/
}