#include "arithm.h"

void MulExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsArithmetic(op1) || !StructIsArithmetic(op2)){
    ReportError("Illegal operands for multiplication.");
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

void AddExpr(){
  TreeNode* node = TreeInsertNode(tree, ADD_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  int arithmetic_index = 0;
  Struct* arithmetic = 0;
  Struct* arithm_or_ptr = 0;
  Struct* expr_type = 0;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);
  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);

  for(int i = 0; i < 2; i++){
    if(StructIsPointer(node->children[i]->expr_node->type)){
      arithm_or_ptr = StructGetUnqualified(node->children[i]->expr_node->type);
    }
    else if(StructIsArithmetic(node->children[i]->expr_node->type)){
      if(arithmetic == 0) {
        arithmetic = StructGetUnqualified(node->children[i]->expr_node->type);
        arithmetic_index = i;
      }
      else arithm_or_ptr = StructGetUnqualified(node->children[i]->expr_node->type);
    }
  }

  if(arithmetic == 0 || arithm_or_ptr == 0){
    ReportError("Illegal operands for addition.");
    return;
  }

  if(StructIsPointer(arithm_or_ptr) && arithm_or_ptr->parent->type != TYPE_OBJECT){
    ReportError("Addition is allowed only on pointers-to-objects.");
    return;
  }

  expr_type = StructIsPointer(arithm_or_ptr) ? arithm_or_ptr : StructGetExprIntType(arithm_or_ptr, arithmetic);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, expr_type);
  SubexprImplCast(node, 1, expr_type);

  if(StructIsPointer(arithm_or_ptr)){
    SubexprMultiplyByConst(node, arithmetic_index, arithm_or_ptr->parent->size);
  }

  TryFold();
}

void SubExpr(){
  TreeNode* node = TreeInsertNode(tree, SUB_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);
  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);

  Struct* left_op  = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* right_op = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(StructIsArithmetic(left_op) && StructIsArithmetic(right_op)){
    expr_type = StructGetExprIntType(left_op, right_op);
  }
  else if(StructIsPointer(left_op) && StructIsPointer(right_op)){
    // left and right op must be of the same type
    if(StructIsCompatibleUnqualified(left_op->parent, right_op->parent)){ 
      expr_type = predefined_types_struct + UINT32_T;
    }
    else {
      ReportError("Incompatible pointers for subtraction.");
      return;
    }
  }
  else if(StructIsPointer(left_op) && StructIsArithmetic(right_op)){
    expr_type = left_op;
  }
  else {
    ReportError("Illegal operators for subtraction.");
    return;
  }

  if(StructIsPointer(left_op) && left_op->parent->type != TYPE_OBJECT){
    ReportError("Subtraction is allowed only on pointers-to-objects.");
    return;
  }

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  ConvertChildToArithmetic(node, 0);
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 0, expr_type);
  SubexprImplCast(node, 1, expr_type);

  if(StructIsPointer(left_op) && StructIsPointer(right_op)){
    ExprDivideByConst(node, expr_type, left_op->parent->size);
  }

  if(StructIsPointer(left_op) && StructIsArithmetic(right_op)){
    SubexprMultiplyByConst(node, 1, left_op->parent->size);
  }

  TryFold();
}

void SimpleAssignExpr(int initializer){
  TreeNode* node = TreeInsertNode(tree, ASSIGN_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[1]->expr_node->type)
      || StructIsFunction(node->children[1]->expr_node->type)){
    ConvertChildToPointer(node, 1);
  }

  if(initializer == 0 && (node->children[0]->expr_node->kind != LVALUE
      || !StructIsModifiable(node->children[0]->expr_node->type))){
    ReportError("Cannot modify non-modifiable or non-lvalue objects.");
    return;
  }

  Struct* dst = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* src = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  switch(StructIsAssignable(dst, src, IsNullPointer(node->children[1]->expr_node))){
  case ASSIGN_OK:
    break;
  case ASSIGN_ERROR_INCOMPATIBLE_TYPES:
    ReportError("Incompatible types for assignment.");
    return;
  case ASSIGN_ERROR_POINTER_INCOMPATIBLE:
    ReportError("Incompatible pointer types for assignment.");
    return;
  case ASSIGN_ERROR_POINTER_QUALIFICATION:
    ReportError("Pointed objects qualifications are not compatible for assignment.");
    return;
  }

  expr_type = dst;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;

  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 1, expr_type);
}

void MulAssignExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(node->children[0]->expr_node->kind != LVALUE
      || !StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable or non-lvalue objects.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsArithmetic(op1) || !StructIsArithmetic(op2)){
    ReportError("Illegal operands for multiplication.");
    return;
  }

  // expr_type = op1;
  expr_type = StructGetExprIntType(op1, op1);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = op1;
  
  ConvertChildToArithmetic(node, 1);

  SubexprImplCast(node, 1, expr_type);
}

void AddAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, ADD_ASSIGN_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);
  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);

  if(node->children[0]->expr_node->kind != LVALUE
      || !StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable or non-lvalue objects.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(StructIsPointer(op1) && StructIsArithmetic(op2)){
    // all good
  }
  else if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    // all good
  }
  else{
    ReportError("Illegal operands for addition.");
    return;
  }

  if(StructIsPointer(op1) && op1->parent->type != TYPE_OBJECT){
    ReportError("Addition is allowed only on pointers-to-objects.");
    return;
  }

  // expr_type = op1;
  expr_type = StructGetExprIntType(op1, op1);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 1);
  SubexprImplCast(node, 1, expr_type);

  if(StructIsPointer(op1)){
    SubexprMultiplyByConst(node, 1, StructGetParentUnqualified(op1)->size);
  }
}

void SubAssignExpr(){
  TreeNode* node = TreeInsertNode(tree, SUB_ASSIGN_EXPR, 2);

  if(!CheckSubexprValidity(node, 2)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);
  if(StructIsArray(node->children[1]->expr_node->type)
    || StructIsFunction(node->children[1]->expr_node->type)) ConvertChildToPointer(node, 1);

  if(node->children[0]->expr_node->kind != LVALUE
      || !StructIsModifiable(node->children[0]->expr_node->type)){
    ReportError("Cannot modify non-modifiable or non-lvalue objects.");
    return;
  }

  Struct* op1 = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* op2 = StructGetUnqualified(node->children[1]->expr_node->type);
  Struct* expr_type = 0;

  if(StructIsPointer(op1) && StructIsArithmetic(op2)){
    // all good
  }
  else if(StructIsArithmetic(op1) && StructIsArithmetic(op2)){
    // all good
  }
  else{
    ReportError("Illegal operands for subtraction.");
    return;
  }
  
  if(StructIsPointer(op1) && op1->parent->type != TYPE_OBJECT){
    ReportError("Subtraction is allowed only on pointers-to-objects.");
    return;
  }

  // expr_type = op1;
  expr_type = StructGetExprIntType(op1, op1);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 1);
  SubexprImplCast(node, 1, expr_type);

  if(StructIsPointer(op1))
    SubexprMultiplyByConst(node, 1, StructGetParentUnqualified(op1)->size);
}