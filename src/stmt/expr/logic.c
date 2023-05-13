#include "logic.h"

void RelationExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  Struct* comparison_type = 0;

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = predefined_types_struct + INT32_T;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    comparison_type = StructGetHigherRank(op1, op2);
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)
      && StructIsCompatible(op1, op2)){
    comparison_type = StructComposite(op1, op2);
  }
  else {
    ReportError("Illegal operands for relational operation.");
    return;
  }

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, comparison_type);
  SubexprImplCast(node, 1, comparison_type);
}

void EqualityExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  Struct* comparison_type = 0;

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = predefined_types_struct + INT32_T;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    comparison_type = StructGetHigherRank(op1, op2);
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)
      && StructIsCompatible(op1, op2)){
    comparison_type = StructComposite(op1, op2);
  }
  else if(StructIsPointer(op1) && (StructIsVoidPtr(op2))){
    comparison_type = op1;
  }
  else if(StructIsPointer(op2) && (StructIsVoidPtr(op1))){
    comparison_type = op2;
  }
  else if(StructIsPointer(op1) && IsNullPointer(node->children[1]->expr_node)){
    comparison_type = op1;
  }
  else if(StructIsPointer(op2) && IsNullPointer(node->children[0]->expr_node)){
    comparison_type = op2;
  }
  else {
    ReportError("Illegal operands for relational operation.");
    return;
  }

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, comparison_type);
  SubexprImplCast(node, 1, comparison_type);
}

void LogExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsScalar(op1) || !StructIsScalar(op2)){
    ReportError("Illegal operands for logic operation.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = predefined_types_struct + INT32_T;

  node->expr_node = expr_node;
  
  ConvertChildToLogic(node, 0);
  ConvertChildToLogic(node, 1);
}

void CondExpr(){
  TreeNode* node = TreeInsertNode(tree, COND_EXPR, 3);

  if(!CheckSubexprValidity(node, 3)) return;

  Struct* condition = node->children[0]->expr_node->type;
  Struct* if_true   = node->children[1]->expr_node->type;
  Struct* if_false  = node->children[2]->expr_node->type;

  if(!StructIsScalar(condition)){
    ReportError("Illegal first operand for ternary operator.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsArithmetic(if_true) && StructIsArithmetic(if_false)){
    expr_node->type = StructGetHigherRank(if_true, if_false);
  }
  else if(StructIsStructOrUnion(if_true) && StructIsStructOrUnion(if_false) 
      && StructIsCompatible(if_true, if_false)){
    expr_node->type = if_true;
  }
  else if(StructIsVoid(if_true) && StructIsVoid(if_false)){
    expr_node->type = predefined_types_struct + VOID_T;
  }
  else if(StructIsPointer(if_true) && StructIsPointer(if_false)){
    Struct* pointed1 = StructGetParentUnqualified(if_true);
    Struct* pointed2 = StructGetParentUnqualified(if_false);

    if(StructIsCompatible(pointed1, pointed2)){
      expr_node->type = StructComposite(pointed1, pointed2);
    }
    else if(StructIsVoidPtr(pointed1)){
      expr_node->type = pointed2;
    }
    else if(StructIsVoidPtr(pointed2)){
      expr_node->type = pointed1;
    }
    else{
      ReportError("Incompatible second and third operand for ternary operator.");
      return;
    }
  }
  else if(StructIsPointer(if_true) && IsNullPointer(node->children[2]->expr_node)){
    expr_node->type = if_true;
  }
  else if(StructIsPointer(if_true) && IsNullPointer(node->children[2]->expr_node)){
    expr_node->type = if_false;
  }
  else{
    ReportError("Incompatible second and third operand for ternary operator.");
    return;
  }
  
  node->expr_node = expr_node;

  ConvertChildToLogic     (node, 0);
  ConvertChildToArithmetic(node, 1);
  ConvertChildToArithmetic(node, 2);

  SubexprImplCast(node, 1, expr_node->type);
  SubexprImplCast(node, 2, expr_node->type);
}