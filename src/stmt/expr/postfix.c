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

  if(node->children[0]->expr_node->type->type == TYPE_FUNCTION){
    ConvertChildToPointer(node, 0);
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
      
      Struct* current_arg   = StructGetUnqualified(node->children[arg_cntr]->expr_node->type);
      Struct* current_param = StructGetUnqualified(param_node->info);

      if(StructIsArithmetic(current_param) && StructIsArithmetic(current_arg)){
        // all good
      }
      else if(StructIsStructOrUnion(current_param) && StructIsStructOrUnion(current_arg)
          && StructIsCompatible(current_param, current_arg)){
        // all good
      }
      else if(StructIsPointer(current_param) && StructIsPointer(current_arg)){
        if(StructIsCompatibleUnqualified(current_param, current_arg)){
          // all good
        }
        else if(StructIsVoidPtr(current_arg)) {
          // all good
        }
        else {
          ReportError("Incompatible argument type for function call.");
          return;
        }
      }
      else if(StructIsPointer(current_param) && IsNullPointer(node->children[arg_cntr]->expr_node)){
        // all good
      }
      else {
        ReportError("Incompatible argument type for function call.");
        return;
      }

      ConvertChildToArithmetic(node, arg_cntr);
      SubexprImplCast(node, arg_cntr, current_param);

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

  node->children[0]->expr_node->address += member->address; // change offset of address primary (not deref)
  node->expr_node->type = member->type;

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

void FunctionArgsOpen(){
  StackPush(&function_call_stack, 0);
}

void FunctionArgsClose(){

}

void FunctionArg(){
  function_call_stack.top->info++;
}