#include "logic.h"

void RelationExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    expr_node->type = StructGetHigherRank(op1, op2);
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)
      && op1 == op2){
    expr_node->type = op1;
  }
  else {
    printf("ERROR: Illegal operands for relational operation.\n");
    return;
  }

  node->expr_node = expr_node;
}

void EqualityExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    expr_node->type = StructGetHigherRank(op1, op2);
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)
      && op1 == op2){
    expr_node->type = op1;
  }
  else if(StructIsPointer(op1) && (op2 == StructVoidPtr())){
    expr_node->type = op1;
  }
  else if(StructIsPointer(op2) && (op1 == StructVoidPtr())){
    expr_node->type = op2;
  }
  else if(StructIsPointer(op1) && IsNullPointer(node->children[1]->expr_node)){
    expr_node->type = op1;
  }
  else if(StructIsPointer(op2) && IsNullPointer(node->children[0]->expr_node)){
    expr_node->type = op2;
  }
  else {
    printf("ERROR: Illegal operands for relational operation.\n");
    return;
  }

  node->expr_node = expr_node;
}

void LogExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsScalar(op1) || !StructIsScalar(op2)){
    printf("ERROR: Illegal operands for logic operation.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = predefined_types_struct + INT32_T;

  node->expr_node = expr_node;
}

void CondExpr(){
  TreeNode* node = TreeInsertNode(tree, COND_EXPR, 3);

  Struct* condition = node->children[0]->expr_node->type;
  Struct* if_true   = node->children[1]->expr_node->type;
  Struct* if_false  = node->children[2]->expr_node->type;

  if(!StructIsScalar(condition)){
    printf("ERROR: Illegal first operand for ternary operator.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsArithmetic(if_true) && StructIsArithmetic(if_false)){
    expr_node->type = StructGetHigherRank(if_true, if_false);
  }
  else if(StructIsStructOrUnion(if_true) && StructIsStructOrUnion(if_false) && if_true == if_false){
    expr_node->type = if_true;
  }
  else if(StructIsVoid(if_true) && StructIsVoid(if_false)){
    expr_node->type = predefined_types_struct + VOID_T;
  }
  else if(StructIsPointer(if_true) && StructIsPointer(if_false)){
    Struct* pointed1 = StructGetParentUnqualified(if_true);
    Struct* pointed2 = StructGetParentUnqualified(if_false);

    if(pointed1 == pointed2){
      expr_node->type = pointed1;
    }
    else if(pointed1 == StructVoidPtr()){
      expr_node->type = pointed2;
    }
    else if(pointed2 == StructVoidPtr()){
      expr_node->type = pointed1;
    }
    else{
      printf("ERROR: Incompatible second and third operand for ternary operator.\n");
    }
  }
  else if(StructIsPointer(if_true) && IsNullPointer(node->children[2]->expr_node)){
    expr_node->type = if_true;
  }
  else if(StructIsPointer(if_true) && IsNullPointer(node->children[2]->expr_node)){
    expr_node->type = if_false;
  }
  else{
    printf("ERROR: Incompatible second and third operand for ternary operator.\n");
  }
}