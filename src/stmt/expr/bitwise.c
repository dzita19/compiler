#include "bitwise.h"

void BitExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsInteger(op1) || !StructIsInteger(op2)){
    ReportError("Illegal operators for bitwise operation.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, expr_node->type);
  SubexprImplCast(node, 1, expr_node->type);
}

void BitAssignExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable object.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  
  if(!StructIsInteger(op1) || !StructIsInteger(op2)){
    ReportError("Illegal operators for bitwise operation.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = op1;

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 1);
}