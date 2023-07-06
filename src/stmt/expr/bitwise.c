#include "bitwise.h"

void BitExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsInteger(op1) || !StructIsInteger(op2)){
    ReportError("Illegal operators for bitwise operation.");
    return;
  }

  expr_type = StructGetExprIntType(op1, op2);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, expr_type);
  SubexprImplCast(node, 1, expr_type);

  TryFold();
}

void BitAssignExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(node->children[0]->expr_node->kind != LVALUE
      || !StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable or non-lvalue objects.");
    return;
  }
  
  if(!StructIsInteger(op1) || !StructIsInteger(op2)){
    ReportError("Illegal operators for bitwise operation.");
    return;
  }

  expr_type = op1;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 1);
  SubexprImplCast(node, 1, expr_type);
}