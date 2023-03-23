#include "postfix.h"

void ArrayRefExpr(){
  TreeNode* node = TreeInsertNode(tree, ARRAY_REF_EXPR, 2);

  for(int i = 0; i < 2; i++){
    if(StructIsArray(node->children[i]->expr_node->type)){
      Struct* type = node->children[i]->expr_node->type;
      node->children[i]->expr_node->type = StructArrayToPtr(type);
    }
  }
  
  ExprNode *array = 0, *index = 0;

  for(int i = 0; i < 2; i++){
    ExprNode* expr_node = node->children[i]->expr_node;
    if(StructIsPointer(expr_node->type)){
      array = expr_node;
    }
    else if(StructIsInteger(expr_node->type)){
      index = expr_node;
    }
  }
  
  if(array == 0 || index == 0) {
    printf("ERROR: Illegal expressions for array subscripting.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = array->kind;
  expr_node->type = array->type->parent;

  node->expr_node = expr_node;

}

void FunctionCallExpr(){
  int args_count = (int)(long)StackPop(&function_call_stack);

  TreeNode* node = TreeInsertNode(tree, FUNCTION_CALL_EXPR, 1 + args_count);

  ExprNode* function_designator = node->children[0]->expr_node;

  if(function_designator->type->type == TYPE_FUNCTION){
    function_designator->type = StructFunctionToPtr(function_designator->type);
  }
  
  if(!StructIsFunctionPtr(function_designator->type)){
    printf("ERROR: Symbol doesn't designate function.\n");
    return;
  }

  int arg_cntr = 1;

  for(Node* param_node = function_designator->type->parent->parameters.first; param_node; param_node = param_node->next){
    if(arg_cntr >= node->num_of_children){
      printf("ERROR: Not enough args for function call.\n");
      return;
    }
    ExprNode* current_arg = node->children[arg_cntr]->expr_node;
    Struct* current_param = param_node->info;

    if(!StructIsCastable(current_arg->type, current_param)
      && IsNullPointer(current_arg) && StructIsPointer(current_param)){
      printf("ERROR: Expression cannot be cast into param type.\n");
      return;
    }

    arg_cntr++;
  }

  if(arg_cntr < node->num_of_children){
    printf("ERROR: Too many args for function call.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = function_designator->type;

}

void FieldRefExpr(const char* member_name){
  TreeNode* node = TreeInsertNode(tree, FIELD_REF_EXPR, 1);

  Struct* type = StructGetUnqualified(node->children[0]->expr_node->type);
  if(!StructIsStructOrUnion(type)){
    printf("ERROR: Field can be referenced only on struct or union objects.\n");
    return;
  }

  Obj* tag_obj = type->obj;
  Obj* member = ObjFindMember(tag_obj, member_name);

  StringDrop(member_name);

  if(member == 0){
    printf("ERROR: Illegal member name.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = node->children[0]->expr_node->kind;
  expr_node->address = member->address;
  expr_node->type = member->type;

  node->expr_node = expr_node;
}

void PtrRefExpr(const char* member_name){
  TreeNode* node = TreeInsertNode(tree, FIELD_REF_EXPR, 1);
  
  Struct* pointer = StructGetUnqualified(node->children[0]->expr_node->type);
  if(!StructIsPointer(pointer) || !StructIsStructOrUnion(pointer->parent)){
    printf("ERROR: Fields can only be referenced through struct or union pointer.\n");
    return;
  }

  Obj* tag_obj = StructGetParentUnqualified(pointer)->obj;
  Obj* member = ObjFindMember(tag_obj, member_name);

  StringDrop(member_name);

  if(member == 0){
    printf("ERROR: Illegal member name.\n");
    return;
  }

  int qualifiers = 0;
  qualifiers |= (pointer->parent->kind == STRUCT_QUALIFIED ? pointer->parent->attributes : 0); // add ptr qualifiers
  qualifiers |= (member->type->kind == STRUCT_QUALIFIED ? member->type->attributes : 0); // add members qualifiers

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = node->children[0]->expr_node->kind;
  expr_node->address = member->address;
  expr_node->type = StructQualify(member->type, qualifiers);

  node->expr_node = expr_node;
}

void IncDecExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 1);

  Struct* type = node->children[0]->expr_node->type;

  if(!StructIsScalar(type)){
    printf("ERROR: Increment only scalar values.\n");
    return;
  }
  if(node->expr_node->kind != LVALUE && !StructIsModifiable(type)){
    printf("ERROR: Cannot increment non-modifiable or non-lvalue objects.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = type;

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

  ExprNode* expr_node = ExprNodeCreateEmpty(); 
  expr_node->kind = RVALUE;
  expr_node->type = node->children[0]->expr_node->type;

  node->expr_node = expr_node;
}