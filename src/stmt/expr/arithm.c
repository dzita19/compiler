#include "arithm.h"

void MulExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsArithmetic(op1) || !StructIsArithmetic(op2)){
    ReportError("Illegal operands for multiplication.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetHigherRank(op1, op2);

  node->expr_node = expr_node;

  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, expr_node->type);
  SubexprImplCast(node, 1, expr_node->type);
}

void AddExpr(){
  TreeNode* node = TreeInsertNode(tree, ADD_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  int arithmetic_index = 0;
  Struct* arithmetic = 0;
  Struct* arithm_or_ptr = 0;

  for(int i = 0; i < 2; i++){
    if(StructIsArray(node->children[i]->expr_node->type)){
      ConvertChildToPointer(node, i);
    }
  }

  for(int i = 0; i < 2; i++){
    if(StructIsPointerToObject(node->children[i]->expr_node->type)) arithm_or_ptr = node->children[i]->expr_node->type;
    else if(StructIsArithmetic(node->children[i]->expr_node->type)){
      if(arithmetic == 0) {
        arithmetic       = node->children[i]->expr_node->type;
        arithmetic_index = i;
      }
      else arithm_or_ptr = node->children[i]->expr_node->type;
    }
  }

  if(arithmetic == 0 || arithm_or_ptr == 0){
    ReportError("Illegal operands for addition.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructIsPointer(arithm_or_ptr) ? arithm_or_ptr : StructGetHigherRank(arithm_or_ptr, arithmetic);

  node->expr_node = expr_node;

  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  if(StructIsPointer(arithm_or_ptr)){
    SubexprMultiplyByConst(node, arithmetic_index, StructGetParentUnqualified(arithm_or_ptr)->size);
  }

  SubexprImplCast(node, 0, expr_node->type);
  SubexprImplCast(node, 1, expr_node->type);
}

void SubExpr(){
  TreeNode* node = TreeInsertNode(tree, SUB_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  for(int i = 0; i < 2; i++){
    if(StructIsArray(node->children[i]->expr_node->type)){
      ConvertChildToPointer(node, i);
    }
  }

  Struct* left_op  = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* right_op = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;

  if(StructIsArithmetic(left_op) && StructIsArithmetic(right_op)){
    expr_node->type = StructGetHigherRank(left_op, right_op);
  }
  else if(StructIsPointerToObject(left_op) && StructIsPointerToObject(right_op)){
    // left and right op must be of the same type
    if(StructIsCompatibleUnqualified(left_op->parent, right_op->parent)){ 
      expr_node->type = predefined_types_struct + INT32_T;
      node->expr_node = expr_node;
      ExprDivideByConst(node, StructGetParentUnqualified(left_op)->size);
    }
    else {
      ReportError("Incompatible pointers for subtraction.");
      return;
    }
  }
  else if(StructIsPointerToObject(left_op) && StructIsArithmetic(right_op)){
    expr_node->type = left_op;
    SubexprMultiplyByConst(node, 1, StructGetParentUnqualified(left_op)->size);
  }
  else {
    ReportError("Illegal operators for subtraction.");
    return;
  }

  node->expr_node = expr_node;

  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, expr_node->type);
  SubexprImplCast(node, 1, expr_node->type);
}

void BasicAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, ASSIGN_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[1]->expr_node->type)
      || StructIsFunction(node->children[1]->expr_node->type)){
    ConvertChildToPointer(node, 1);
  }

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable object.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = op1;

  if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    // expr_node->type = op1;
  }
  else if(StructIsStructOrUnion(op1) && StructIsStructOrUnion(op2)
      && StructIsCompatible(op1, op2)){
    // expr_node->type = op1;
  }
  else if(StructIsPointer(op1) && StructIsPointer(op2)){
    Struct* pointed1 = op1->parent;
    Struct* pointed2 = op2->parent;

    int qualifiers1 = pointed1->kind == STRUCT_QUALIFIED ? pointed1->attributes : 0;
    int qualifiers2 = pointed2->kind == STRUCT_QUALIFIED ? pointed2->attributes : 0;

    if(qualifiers1 != (qualifiers1 | qualifiers2)){
      ReportError("Pointed objects qualifications are not compatible for assignment.");
      return;
    }

    if(StructIsCompatibleUnqualified(pointed1, pointed2)){
      // expr_node->type = op1;
    }
    else if(StructIsVoidPtr(StructGetUnqualified(pointed2))) {
      // expr_node->type = op1;
    }
    else {
      ReportError("Incompatible types for assignment.");
      return;
    }
  }
  else {
    ReportError("Incompatible types for assignment.");
    return;
  }

  node->expr_node = expr_node;

  ConvertChildToArithmetic(node, 1);
}

void MulAssignExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable object.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  if(!StructIsArithmetic(op1) || !StructIsArithmetic(op2)){
    ReportError("Illegal operands for multiplication.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = op1;

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 1);
}

void AddAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, ADD_ASSIGN_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable object.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = op1;

  if(StructIsPointerToObject(op1) && StructIsArithmetic(op2)){
    SubexprMultiplyByConst(node, 1, StructGetParentUnqualified(op1)->size);
  }
  else if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    
  }
  else{
    ReportError("Illegal operands for addition.");
    return;
  }

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 1);
}

void SubAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, SUB_ASSIGN_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(!StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable object.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = op1;

  if(StructIsPointerToObject(op1) && StructIsArithmetic(op2)){
    SubexprMultiplyByConst(node, 1, StructGetParentUnqualified(op1)->size);
  }
  else if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    
  }
  else{
    ReportError("Illegal operands for subtraction.");
    return;
  }
  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 1);
}