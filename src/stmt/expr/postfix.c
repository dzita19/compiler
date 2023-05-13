#include "postfix.h"

// semantics of a[b] is the same as of *(a + b) - no need to add a new rule for that
void ArrayRefExpr(){
  extern void AddExpr();
  extern void DerefExpr();

  AddExpr();
  DerefExpr();
}

void FunctionCallExpr(){
  int args_count = (int)(long)StackPop(&function_call_stack);

  TreeNode* node = TreeInsertNode(tree, FUNCTION_CALL_EXPR, 1 + args_count);

  if(!CheckSubexprValidity(node, 1 + args_count)) return;

  ExprNode* function_designator = node->children[0]->expr_node;

  if(function_designator->type->type == TYPE_FUNCTION){
    ConvertChildToPointer(node, 0);
    function_designator = node->children[0]->expr_node;
  }
  
  if(!StructIsFunctionPtr(function_designator->type)){
    ReportError("Symbol doesn't designate function.");
    return;
  }

  if((function_designator->type->parent->attributes & NONPROTOTYPE_FUNCTION) == 0){

    int arg_cntr = 1; // counts current argument - from syntax tree

    for(Node* param_node = function_designator->type->parent->parameters.first; param_node; param_node = param_node->next){
      if(arg_cntr >= node->num_of_children){ // check so you don't reference a non-existing child
        ReportError("Not enough args for function call.");
        return;
      }
      ExprNode* current_arg = node->children[arg_cntr]->expr_node;
      Struct* current_param = param_node->info;

      if(!StructIsCastable(current_arg->type, current_param)
          && !(IsNullPointer(current_arg) && StructIsPointer(current_param))){
        ReportError("Expression cannot be cast into param type.");
        return;
      }

      // cast arg

      arg_cntr++;
    }

    if(arg_cntr < node->num_of_children && (function_designator->type->parent->attributes & ELLIPSIS_FUNCTION) == 0){
      ReportError("Too many args for function call.");
      return;
    }

  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetParentUnqualified(StructGetParentUnqualified(function_designator->type));

  node->expr_node = expr_node;
}

void FieldRefExpr(){
  TreeNode* node = StackPeek(&tree->stack);

  if(node->expr_node == 0) return;

  const char* member_name = QueueDelete(&identifier_queue);

  Struct* type = StructGetUnqualified(node->expr_node->type);
  if(!StructIsStructOrUnion(type)){
    ReportError("Field can be referenced only on struct or union objects.");
    return;
  }

  Obj* tag_obj = type->obj;
  Obj* member = ObjFindMember(tag_obj, member_name);

  StringDrop(member_name);

  if(member == 0){
    ReportError("Illegal member name.");
    return;
  }

  node->expr_node->address += member->address;
  node->expr_node->type     = member->type;

}

void PtrRefExpr(){
  extern void DerefExpr();
  extern void FieldRefExpr();

  DerefExpr();
  FieldRefExpr();
}

void IncDecExpr(Production production){

  InsertConstant(0);
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* type = node->children[0]->expr_node->type;

  if(!StructIsScalar(type)){
    ReportError("Increment only scalar values.");
    return;
  }
  if(node->children[0]->expr_node->kind != LVALUE && !StructIsModifiable(type)){
    ReportError("Cannot increment non-modifiable or non-lvalue objects.");
    return;
  }
  if(StructIsPointer(type) && type->parent->type != TYPE_OBJECT){
    ReportError("Incremented pointer must point to object type.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = type;

  if(StructIsPointer(type)){
    node->children[1]->expr_node->address = StructGetParentUnqualified(type)->size;
  }
  else{
    node->children[1]->expr_node->address = 1;
  }

  node->expr_node = expr_node;
}

void FunctionArgsOpen(){
  StackPush(&function_call_stack, 0);
}

void FunctionArgsClose(){

}

void FunctionArg(){
  function_call_stack.top->info++;

  TreeNode* node = TreeInsertNode(tree, FUNCTION_ARG, 1);
  if(!CheckSubexprValidity(node, 1)) return;

  ExprNode* expr_node = ExprNodeCreateEmpty(); 
  expr_node->kind = RVALUE;
  expr_node->type = node->children[0]->expr_node->type;

  node->expr_node = expr_node;

  if(StructIsInteger(node->children[0]->expr_node->type)) ConvertChildToArithmetic(node, 0);

  SubexprImplCast(node, 0, expr_node->type);
}