#include "postfix.h"

#include <string.h>

// semantics of a[b] is the same as of *(a + b) - no need to add a new rule for that
void ArrayRefExpr(void){
  extern void AddExpr(void);
  extern void DerefExpr(void);

  AddExpr();
  DerefExpr();
}

void FunctionCallExpr(void){
  int args_count = (int)(long)StackPop(&function_call_stack);

  TreeNode* node = TreeInsertNode(tree, FUNCTION_CALL_EXPR, 1 + args_count);

  if(!CheckSubexprValidity(node, 1 + args_count)) return;

  // convert function to be called
  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);

  // convert args
  for(int i = 1; i < node->num_of_children; i++){
    if(StructIsArray(node->children[i]->expr_node->type)
      || StructIsFunction(node->children[i]->expr_node->type)) ConvertChildToPointer(node, i);
  }

  ExprNode* function_designator = node->children[0]->expr_node;
  Struct* expr_type = 0;
  
  if(!StructIsFunctionPtr(function_designator->type)){
    ReportError("Symbol doesn't designate function.");
    return;
  }

  if((function_designator->type->parent->attributes & NONPROTOTYPE_FUNCTION) == 0){

    int arg_cntr = 1; // counts current argument - from syntax tree

    for(Node* param_node = function_designator->type->parent->parameters.first; param_node; param_node = param_node->next){
      if(arg_cntr >= node->num_of_children){ // check so you don't reference a non-existing child
        ReportError("Not enough arguments for function call.");
        return;
      }
      
      Struct* current_param = StructGetUnqualified(param_node->info);
      Struct* current_arg   = StructGetUnqualified(node->children[arg_cntr]->expr_node->type);

      switch(StructIsPassable(current_param, current_arg, IsNullPointer(node->children[arg_cntr]->expr_node))){
      case ASSIGN_OK:
        break;
      case ASSIGN_ERROR_INCOMPATIBLE_TYPES:
        ReportError("Incompatible argument type for function call.");
        return;
      case ASSIGN_ERROR_POINTER_INCOMPATIBLE:
        ReportError("Incompatible argument pointer type for function call.");
        return;
      case ASSIGN_ERROR_POINTER_QUALIFICATION:
        ReportError("Pointed objects qualifications are not compatible for function call.");
        return;
      }

      // params are aligned to 4byte address
      ConvertChildToArithmetic(node, arg_cntr);
      if(StructIsArithmetic(current_param)){
        SubexprImplCast(node, arg_cntr, StructGetExprIntType(current_param, current_param));
      }
      SubexprImplCast(node, arg_cntr, current_param);

      // params are not aligned to 4byte address
      // SubexprImplCast(node, arg_cntr, current_param);

      arg_cntr++;
    }

    if(arg_cntr < node->num_of_children && (function_designator->type->parent->attributes & ELLIPSIS_FUNCTION) == 0){
      ReportError("Too many arguments for function call.");
      return;
    }

  }

  expr_type = StructGetParentUnqualified(StructGetParentUnqualified(function_designator->type));

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  if(StructIsStructOrUnion(expr_type)){

    TreeNode* fcall = StackPop(&tree->stack);

    if(rval_call_storage == 0){
      rval_call_storage = ObjCreateEmpty();
      rval_call_storage->kind = OBJ_VAR;
      rval_call_storage->specifier = LINKAGE_NONE | STORAGE_AUTO | DEFINED;
      rval_call_storage->name = StringDuplicate("$storage00");
    }

    if(rval_call_storage->type == 0 || rval_call_storage->type->size < expr_type->size){
      rval_call_storage->type = expr_type;
    }

    // push storage_obj to tree stack
    extern void DerefExpr(void);
    extern void SimpleAssignExpr(int);

    TreeNode* storage_node = TreeInsertNode(tree, ADDRESS_PRIMARY, 0);

    storage_node->expr_node          = ExprNodeCreateEmpty();
    storage_node->expr_node->type    = StructToPtr(expr_type);
    storage_node->expr_node->kind    = ADDRESS_OF;
    storage_node->expr_node->obj_ref = rval_call_storage;

    DerefExpr();
    StackPush(&tree->stack, fcall);
    SimpleAssignExpr(1);

    // storage_node = TreeInsertNode(tree, ADDRESS_PRIMARY, 0);

    // storage_node->expr_node = ExprNodeCreateEmpty();
    // storage_node->expr_node->type = StructToPtr(expr_type);
    // storage_node->expr_node->kind = ADDRESS_OF;
    // storage_node->expr_node->obj_ref  = rval_storage_obj;
    
    // DerefExpr();

    // CommaExprOpen();
    // CommaExpr();
    // FullExpr();
  }
}

void FieldRefExpr(void){
  TreeNode* operand = StackPeek(&tree->stack);

  if(operand->expr_node == 0) {
    StringDrop(QueueDelete(&identifier_queue));
    return;
  }

  const char* member_name = QueueDelete(&identifier_queue);

  int aggregate_qualifiers = operand->expr_node->type->kind == STRUCT_QUALIFIED ? operand->expr_node->type->attributes : 0;
  Struct* type = StructGetUnqualified(operand->expr_node->type);
  if(!StructIsStructOrUnion(type)){
    ReportError("Field can be referenced only on struct or union objects.");
    StringDrop(member_name);
    return;
  }

  Obj* tag_obj = type->obj;
  Obj* member = ObjFindMember(tag_obj, member_name);

  StringDrop(member_name);

  if(member == 0){
    ReportError("Member with name %s doesn't exist.", member_name);
    return;
  }

  // add fieldref between deref and address
  if(operand->production == DEREF_EXPR){
    TreeNode* address = operand->children[0];
    address->parent      = 0;
    operand->children[0] = 0;

    StackPop(&tree->stack); // pop
    StackPush(&tree->stack, address);

    // take into consideration qualifier propagation
    int member_qualifiers = member->type->kind == STRUCT_QUALIFIED ? member->type->attributes : 0;
    Struct* member_type = StructQualify(StructGetUnqualified(member->type), aggregate_qualifiers | member_qualifiers);

    TreeNode* node  = TreeInsertNode(tree, FIELD_REF_EXPR, 1);
    node->expr_node = ExprNodeCreateEmpty();
    node->expr_node->address = member->address;
    node->expr_node->kind = RVALUE;
    node->expr_node->type = StructToPtr(member_type);

    TryFold();
    
    TreeNode* deref = TreeInsertNode(tree, DEREF_EXPR, 1);
    deref->expr_node = ExprNodeCreateEmpty();
    deref->expr_node->kind = operand->expr_node->kind;
    deref->expr_node->type = member_type;

    TreeNodeDrop(operand);
  }
  // add fieldref, then add deref
  else{
    // take into consideration qualifier propagation
    int member_qualifiers = member->type->kind == STRUCT_QUALIFIED ? member->type->attributes : 0;
    Struct* member_type = StructQualify(StructGetUnqualified(member->type), aggregate_qualifiers | member_qualifiers);

    TreeNode* node  = TreeInsertNode(tree, FIELD_REF_EXPR, 1);
    node->expr_node = ExprNodeCreateEmpty();
    node->expr_node->address = member->address;
    node->expr_node->kind = RVALUE;
    node->expr_node->type = StructToPtr(member_type);

    TreeNode* deref = TreeInsertNode(tree, DEREF_EXPR, 1);
    deref->expr_node = ExprNodeCreateEmpty();
    deref->expr_node->kind = RVALUE;
    deref->expr_node->type = member_type;
  }

  // FieldRefPropagateOffset(node, member->type, member->address);
}

void PtrRefExpr(void){
  extern void DerefExpr(void);
  extern void FieldRefExpr(void);

  DerefExpr();
  FieldRefExpr();
}

void IncDecExpr(Production production){

  InsertConstant(0);
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(node->children[0]->expr_node->kind != LVALUE
      || !StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot increment non-modifiable or non-lvalue objects.");
    return;
  }

  Struct* type = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsScalar(type)){
    ReportError("Increment only scalar values.");
    return;
  }

  if(StructIsPointer(type) && type->parent->type != TYPE_OBJECT){
    ReportError("Increment is allowed only on pointers-to-objects.");
    return;
  }

  if(StructIsPointer(type)) expr_type = type;
  else expr_type = StructGetExprIntType(type, type);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  if(StructIsPointer(type)){
    node->children[1]->expr_node->address = StructGetParentUnqualified(type)->size;
  }
  else{
    node->children[1]->expr_node->address = 1;
  }
}

void FunctionArgsOpen(void){
  StackPush(&function_call_stack, 0);
}

void FunctionArgsClose(void){

}

void FunctionArg(void){
  function_call_stack.top->info++;
}

void CompoundLiteral(void){
  Obj* current_obj_definiton = StackPeek(&obj_definiton_stack);

  extern void DerefExpr(void);
  TreeNode* compound_literal = TreeInsertNode(tree, COMPOUND_LITERAL, 1);
  compound_literal->expr_node = ExprNodeCreateEmpty();
  compound_literal->expr_node->kind    = ADDRESS_OF;
  compound_literal->expr_node->obj_ref = current_obj_definiton;
  compound_literal->expr_node->type    = StructToPtr(current_obj_definiton->type);

  DerefExpr();

  StackPop(&obj_definiton_stack); // #1
  LinkedListDrop(StackPop(&initializer_stack)); // #2
  StackDrop(StackPop(&init_frame_stack)); // #3
  StackPop(&init_attrib_stack); // #4
  StackPop(&init_error_stack); // #5
  StackPop(&init_size_stack); // #6
}