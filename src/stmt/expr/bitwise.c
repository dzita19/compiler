#include "bitwise.h"

void BitExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsInteger(op1) || !StructIsInteger(op2)){
    printf("ERROR: Illegal operators for bitwise operation.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}

void BitAssignExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    printf("ERROR: Cannot modify non-modifiable object.\n");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  
  if(!StructIsInteger(op1) || !StructIsInteger(op2)){
    printf("ERROR: Illegal operators for bitwise operation.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
}