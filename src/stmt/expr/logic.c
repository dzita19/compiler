#include "logic.h"

void RelationExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);
  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;
  Struct* comparison_type = 0;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    comparison_type = StructGetExprIntType(op1, op2);
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)){
    Struct* pointed1 = StructGetParentUnqualified(op1);
    Struct* pointed2 = StructGetParentUnqualified(op2);

    if(!StructIsCompatible(pointed1, pointed2)){
      ReportError("Illegal operands for relational operation.");
      return;
    }

    comparison_type = predefined_types_struct + UINT32_T;
  }
  else {
    ReportError("Illegal operands for relational operation.");
    return;
  }

  expr_type = predefined_types_struct + INT32_T;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, comparison_type);
  SubexprImplCast(node, 1, comparison_type);

  TryFold();
}

void EqualityExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);
  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;
  Struct* comparison_type = 0;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    comparison_type = StructGetExprIntType(op1, op2);
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)){
    Struct* pointed1 = StructGetParentUnqualified(op1);
    Struct* pointed2 = StructGetParentUnqualified(op2);

    if(StructIsCompatible(pointed1, pointed2)){
      comparison_type = predefined_types_struct + UINT32_T;
    }
    else if(StructIsVoid(pointed1)){
      comparison_type = predefined_types_struct + UINT32_T;
    }
    else if(StructIsVoid(pointed2)){
      comparison_type = predefined_types_struct + UINT32_T;
    }
    else {
      ReportError("Illegal operands for relational operation.");
      return;
    }
  }
  else if(StructIsPointer(op1) && IsNullPointer(node->children[1]->expr_node)){
    comparison_type = predefined_types_struct + UINT32_T;
  }
  else if(StructIsPointer(op2) && IsNullPointer(node->children[0]->expr_node)){
    comparison_type = predefined_types_struct + UINT32_T;
  }
  else {
    ReportError("Illegal operands for relational operation.");
    return;
  } 

  expr_type = predefined_types_struct + INT32_T;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, comparison_type);
  SubexprImplCast(node, 1, comparison_type);

  TryFold();
}

void LogExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);
  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsScalar(op1) || !StructIsScalar(op2)){
    ReportError("Illegal operands for logic operation.");
    return;
  }

  expr_type = predefined_types_struct + INT32_T;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToLogic(node, 0);
  ConvertChildToLogic(node, 1);

  TryFold();
}

void CondExpr(){
  TreeInsertNode(tree, VOID_EXPR, 0);

  TreeNode* node = TreeInsertNode(tree, COND_EXPR, 4);

  if(!CheckSubexprValidity(node, 3)) return;

  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);
  if(StructIsArray(node->children[2]->expr_node->type)
    || StructIsFunction(node->children[2]->expr_node->type)) ConvertChildToPointer(node, 2);

  Struct* condition = node->children[0]->expr_node->type;
  Struct* if_true   = node->children[1]->expr_node->type;
  Struct* if_false  = node->children[2]->expr_node->type;
  Struct* expr_type = 0;

  if(!StructIsScalar(condition)){
    ReportError("Illegal first operand for ternary operator.");
    return;
  }

  if(StructIsArithmetic(if_true) && StructIsArithmetic(if_false)){
    expr_type = StructGetExprIntType(if_true, if_false);
  }
  else if(StructIsStructOrUnion(if_true) && StructIsStructOrUnion(if_false) 
      && StructIsCompatible(if_true, if_false)){
    expr_type = StructGetUnqualified(if_true);
  }
  else if(StructIsVoid(if_true) && StructIsVoid(if_false)){
    expr_type = predefined_types_struct + VOID_T;
  }
  else if(StructIsPointer(if_true) && StructIsPointer(if_false)){
    /*
    // check basic assign and function call for reference
    // -- there is one difference - in assign and function call, lval and param ARE DETERMINING THE TYPE
    // -- that's the reason why there are different qualifications allowed, and here they are not allowed
    if(StructIsCompatible(if_true, if_false)){
      expr_type = StructComposite(if_true, if_false);
    }
    else if(StructIsVoidPtr(if_false)){
      expr_type = if_true;
    }
    else if(StructIsVoidPtr(if_true)){
      expr_type = if_false;
    }
    else{
      ReportError("Incompatible second and third operand for ternary operator.");
      return;
    }*/
    Struct* pointed_true  = StructGetParentUnqualified(if_true);
    Struct* pointed_false = StructGetParentUnqualified(if_false);

    int qualifiers1 = if_true->parent->kind  == STRUCT_QUALIFIED ? if_true->parent->attributes  : 0;
    int qualifiers2 = if_false->parent->kind == STRUCT_QUALIFIED ? if_false->parent->attributes : 0;
    
    if(StructIsCompatible(pointed_true, pointed_false)){
      expr_type = StructQualify(StructToPtr(StructComposite(pointed_true, pointed_false)), qualifiers1);
    }
    else if(StructIsVoid(pointed_true)) {
      expr_type = if_false;
    }
    else if(StructIsVoid(pointed_false)){
      expr_type = if_true;
    }
    else {
      ReportError("Incompatible operand type for ternary operator.");
      return;
    }

    if(qualifiers1 != qualifiers2){
      ReportError("Pointed objects qualifications are not compatible for ternary operator.");
      return;
    }
  }
  else if(StructIsPointer(if_true) && IsNullPointer(node->children[2]->expr_node)){
    expr_type = if_true;
  }
  else if(StructIsPointer(if_true) && IsNullPointer(node->children[2]->expr_node)){
    expr_type = if_false;
  }
  else{
    ReportError("Incompatible second and third operand for ternary operator.");
    return;
  }

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  ConvertChildToLogic     (node, 0);
  ConvertChildToArithmetic(node, 1);
  ConvertChildToArithmetic(node, 2);

  SubexprImplCast(node, 1, expr_type);
  SubexprImplCast(node, 2, expr_type);

  TryFold();
}