#include "arithm.h"

void MulExpr(){
  TreeNode* node = TreeInsertNode(tree, MUL_EXPR, 2);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsArithmetic(op1) && !StructIsArithmetic(op2)){
    printf("ERROR: Illegal operands for multiplication.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}

void DivExpr(){
  TreeNode* node = TreeInsertNode(tree, DIV_EXPR, 2);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsArithmetic(op1) && !StructIsArithmetic(op2)){
    printf("ERROR: Illegal operands for division.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}

void ModExpr(){
  TreeNode* node = TreeInsertNode(tree, MOD_EXPR, 2);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsInteger(op1) && !StructIsInteger(op2)){
    printf("ERROR: Illegal operands for modulo.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}

void AddExpr(){
  TreeNode* node = TreeInsertNode(tree, ADD_EXPR, 2);

  Struct* arithmetic = 0;
  Struct* arith_or_ptr = 0;

  for(int i = 0; i < 2; i++){
    if(StructIsArray(node->children[i]->expr_node->type)){
      node->children[i]->expr_node->type = StructArrayToPtr(node->children[i]->expr_node->type);
    }
  }

  for(int i = 0; i < 2; i++){
    if(StructIsPointer(node->children[i]->expr_node->type)) arith_or_ptr = node->children[i]->expr_node->type;
    else if(StructIsArithmetic(node->children[i]->expr_node->type)){
      if(arithmetic == 0) arithmetic   = node->children[i]->expr_node->type;
      else                arith_or_ptr = node->children[i]->expr_node->type;
    }
  }

  if(arithmetic == 0 || arith_or_ptr == 0){
    printf("ERROR: Illegal operands for addition.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructIsPointer(arith_or_ptr) ? arith_or_ptr : StructGetHigherRank(arith_or_ptr, arithmetic);

  node->expr_node = expr_node;
}

void SubExpr(){
  TreeNode* node = TreeInsertNode(tree, ADD_EXPR, 2);

  for(int i = 0; i < 2; i++){
    if(StructIsArray(node->children[i]->expr_node->type)){
      node->children[i]->expr_node->type = StructArrayToPtr(node->children[i]->expr_node->type);
    }
  }

  Struct* left_op  = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* right_op = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsArithmetic(left_op) && StructIsArithmetic(right_op)){
    expr_node->type = StructGetHigherRank(left_op, right_op);
  }
  else if(StructIsPointer(left_op) && StructIsPointer(right_op)){
    if(left_op == right_op){ // left and right op must be of the same type
      expr_node->type = predefined_types_struct + INT32_T;
    }
    else return;
  }
  else if(StructIsPointer(left_op) && StructIsArithmetic(right_op)){
    expr_node->type = left_op;
  }
  else {
    printf("ERROR: Illegal operators for subtraction.\n");
    return;
  }

  node->expr_node = expr_node;
}

void BasicAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, ASSIGN_EXPR, 2);

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    printf("ERROR: Cannot modify non-modifiable object.\n");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    expr_node->type = StructGetHigherRank(op1, op2);
  }
  else if(StructIsStructOrUnion(op1) && StructIsStructOrUnion(op2)
      && op1 == op2){
    expr_node->type = op1;
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)){
    Struct* pointed1 = op1->parent;
    Struct* pointed2 = op2->parent;

    int qualifiers1 = pointed1->kind == STRUCT_QUALIFIED ? pointed1->attributes : 0;
    int qualifiers2 = pointed2->kind == STRUCT_QUALIFIED ? pointed2->attributes : 0;

    if(qualifiers1 != (qualifiers1 | qualifiers2)){
      printf("ERROR: Pointed objects qualifications are not compatible.\n");
      return;
    }

    if(StructGetUnqualified(pointed1) == StructGetUnqualified(pointed2)){
      expr_node->type = op1;
    }
    else if(StructGetUnqualified(pointed2) == StructVoidPtr()){
      expr_node->type = op1;
    }
    else {
      printf("ERROR: Incompatible types for assignmetn.\n");
      return;
    }
  }
  else {
    printf("ERROR: Incompatible types for assignmetn.\n");
    return;
  }

  node->expr_node = expr_node;
}

void MulAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, MUL_ASSIGN_EXPR, 2);

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    printf("ERROR: Cannot modify non-modifiable object.\n");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsArithmetic(op1) && !StructIsArithmetic(op2)){
    printf("ERROR: Illegal operands for multiplication.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}

void DivAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, DIV_ASSIGN_EXPR, 2);

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    printf("ERROR: Cannot modify non-modifiable object.\n");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsArithmetic(op1) && !StructIsArithmetic(op2)){
    printf("ERROR: Illegal operands for division.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}

void ModAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, MOD_ASSIGN_EXPR, 2);

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    printf("ERROR: Cannot modify non-modifiable object.\n");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsInteger(op1) && !StructIsInteger(op2)){
    printf("ERROR: Illegal operands for modulo.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}

void AddAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, ADD_ASSIGN_EXPR, 2);

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    printf("ERROR: Cannot modify non-modifiable object.\n");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsPointer(op1) && StructIsArithmetic(op2)){
    expr_node->type = op1;
  }
  else if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    expr_node->type = StructGetHigherRank(op1, op2);
  }
  else{
    printf("ERROR: Illegal operands for modulo.\n");
    return;
  }

  node->expr_node = expr_node;
}

void SubAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, SUB_ASSIGN_EXPR, 2);

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    printf("ERROR: Cannot modify non-modifiable object.\n");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsPointer(op1) && StructIsArithmetic(op2)){
    expr_node->type = op1;
  }
  else if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    expr_node->type = StructGetHigherRank(op1, op2);
  }
  else{
    printf("ERROR: Illegal operands for modulo.\n");
    return;
  }

  node->expr_node = expr_node;
}