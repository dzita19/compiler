#include "const_expr.h"

#include <stdint.h>

static int const_expr_valid = 0;

void ConstExpression(){
  TreeNode* const_expr_node = StackPop(&tree->stack);

  ConstExpr* const_expr = ConstExprCreateEmpty();
  
  const_expr_valid = 1;
  long const_expr_arith = ConstArithmeticExprProcessor(const_expr_node);

  if(const_expr_valid) {
    const_expr->type |= CONST_EXPR_ARITHMETIC;
    const_expr->value = const_expr_arith;
  }

  StackPush(&const_expr_stack, const_expr);

  TreeNodeDrop(const_expr_node);
}

long ConstArithmeticExprProcessor(TreeNode* node){

  if(const_expr_valid == 0) return 0;

  switch(node->production){
  case CONSTANT_PRIMARY: {
    return node->expr_node->address;
  }
  case UNARY_PLUS_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0]);
  }
  case UNARY_MINUS_EXPR: {
    return -ConstArithmeticExprProcessor(node->children[0]);
  }
  case BIT_NOT: {
    return ~ConstArithmeticExprProcessor(node->children[0]);
  }
  case LOG_NOT: {
    return !ConstArithmeticExprProcessor(node->children[0]);

  }
  case CAST_EXPR: {
    if(node->children[0]->expr_node->type == predefined_types_struct + INT8_T)
      return (int8_t)   ConstArithmeticExprProcessor(node->children[0]);
    if(node->children[0]->expr_node->type == predefined_types_struct + UINT8_T)
      return (uint8_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->children[0]->expr_node->type == predefined_types_struct + INT16_T)
      return (int16_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->children[0]->expr_node->type == predefined_types_struct + UINT16_T)
      return (uint16_t) ConstArithmeticExprProcessor(node->children[0]);
    if(node->children[0]->expr_node->type == predefined_types_struct + INT32_T)
      return (int32_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->children[0]->expr_node->type == predefined_types_struct + UINT32_T)
      return (uint32_t) ConstArithmeticExprProcessor(node->children[0]);
    if(node->children[0]->expr_node->type == predefined_types_struct + INT64_T)
      return (int64_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->children[0]->expr_node->type == predefined_types_struct + UINT64_T)
      return (uint64_t) ConstArithmeticExprProcessor(node->children[0]);
    const_expr_valid = 0;
    return 0;
  }

  case MUL_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      * ConstArithmeticExprProcessor(node->children[1]);
  }
  case DIV_EXPR: {
    int quotant = ConstArithmeticExprProcessor(node->children[1]);
    if(quotant == 0){
      const_expr_valid = 0;
      return 0;
    }
    return ConstArithmeticExprProcessor(node->children[0]) / quotant;
  }
  case MOD_EXPR: {
    int quotant = ConstArithmeticExprProcessor(node->children[1]);
    if(quotant == 0){
      const_expr_valid = 0;
      return 0;
    }
    return ConstArithmeticExprProcessor(node->children[0]) % quotant;
  }

  case ADD_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      + ConstArithmeticExprProcessor(node->children[1]);
  }
  case SUB_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      - ConstArithmeticExprProcessor(node->children[1]);
  }

  case BIT_LEFT_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      << ConstArithmeticExprProcessor(node->children[1]);
  }
  case BIT_RIGHT_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      >> ConstArithmeticExprProcessor(node->children[1]);
  }

  case RELA_GT_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      > ConstArithmeticExprProcessor(node->children[1]);
  }
  case RELA_LT_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      < ConstArithmeticExprProcessor(node->children[1]);
  }
  case RELA_GE_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      >= ConstArithmeticExprProcessor(node->children[1]);
  }
  case RELA_LE_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      <= ConstArithmeticExprProcessor(node->children[1]);
  }
  case RELA_EQ_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      == ConstArithmeticExprProcessor(node->children[1]);
  }
  case RELA_NE_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      != ConstArithmeticExprProcessor(node->children[1]);
  }
  
  case BIT_AND_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      & ConstArithmeticExprProcessor(node->children[1]);
  }
  case BIT_XOR_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      ^ ConstArithmeticExprProcessor(node->children[1]);
  }
  case BIT_OR_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      | ConstArithmeticExprProcessor(node->children[1]);
  }
  
  case LOG_AND_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      && ConstArithmeticExprProcessor(node->children[1]);
  }
  case LOG_OR_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      || ConstArithmeticExprProcessor(node->children[1]);
  }

  case COND_EXPR: {
    return ConstArithmeticExprProcessor(node->children[0])
      ? ConstArithmeticExprProcessor(node->children[1])
      : ConstArithmeticExprProcessor(node->children[2]);
  }

  default: {
    const_expr_valid = 0;
    return 0;
    break;
  }

  }

}

ConstExpr ConstAddressExprProcessor(TreeNode* node){

  if(const_expr_valid == 0) return (ConstExpr){ 0, 0, 0 };

  switch(node->production){
  case CONSTANT_PRIMARY: {
    if(node->expr_node->address == 0) 
      return (ConstExpr){ 0, 0, CONST_EXPR_ARITHMETIC | CONST_EXPR_ADDRESS };
    else
      return (ConstExpr){ 0, node->expr_node->address, CONST_EXPR_ARITHMETIC };
  }
  case ADDRESS_EXPR: {
    TreeNode* child = node->children[0];
    long offset = 0;
    Obj* obj_ref = 0;
    while(obj_ref != 0){
      if(child->production == IDENTIFIER_PRIMARY){
        obj_ref = child->expr_node->obj_ref;
      }
      else if(child->production == FIELD_REF_EXPR) {
        offset += child->expr_node->address;
        child = child->children[0];
      }
      else goto error;
    }
    return (ConstExpr){ obj_ref, offset, CONST_EXPR_ADDRESS };
  }
  case UNARY_PLUS_EXPR: {
    ConstExpr operand = ConstAddressExprProcessor(node->children[0]);
    if(operand.type & CONST_EXPR_ARITHMETIC) return (ConstExpr){ 0, operand.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case UNARY_MINUS_EXPR: {
    ConstExpr operand = ConstAddressExprProcessor(node->children[0]);
    if(operand.type & CONST_EXPR_ARITHMETIC) return (ConstExpr){ 0, operand.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }  
  case BIT_NOT: {
    ConstExpr operand = ConstAddressExprProcessor(node->children[0]);
    if(operand.type & CONST_EXPR_ARITHMETIC) return (ConstExpr){ 0, operand.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case LOG_NOT: {
    ConstExpr operand = ConstAddressExprProcessor(node->children[0]);
    if(operand.type & CONST_EXPR_ARITHMETIC) return (ConstExpr){ 0, operand.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }

  case CAST_EXPR: {
    ConstExpr operand = ConstAddressExprProcessor(node->children[0]);
    if(StructIsPointer(node->expr_node->type)){
      return (ConstExpr){ 0, operand.value, CONST_EXPR_ADDRESS };
    }
    else {
      return (ConstExpr){ 0, operand.value, CONST_EXPR_ARITHMETIC };
    }
  }

  case MUL_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value * op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case DIV_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC
        && op2.value != 0) 
      return (ConstExpr){ 0, op1.value / op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case MOD_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC
        && op2.value != 0) 
      return (ConstExpr){ 0, op1.value % op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }

  case ADD_EXPR: {
  }
  case SUB_EXPR: {
  }

  case BIT_LEFT_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value << op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case BIT_RIGHT_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value >> op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }

  case RELA_GT_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value > op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case RELA_LT_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value < op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case RELA_GE_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value >= op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case RELA_LE_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value <= op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }

  case RELA_EQ_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value == op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case RELA_NE_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value != op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }

  case BIT_AND_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value & op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case BIT_XOR_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value ^ op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case BIT_OR_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value | op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }

  case LOG_AND_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value && op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }
  case LOG_OR_EXPR: {
    ConstExpr op1 = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op2 = ConstAddressExprProcessor(node->children[1]);
    if(op1.type & CONST_EXPR_ARITHMETIC
        && op2.type & CONST_EXPR_ARITHMETIC) 
      return (ConstExpr){ 0, op1.value || op2.value, CONST_EXPR_ARITHMETIC };
    else goto error;
  }

  case COND_EXPR: {
    ConstExpr cond = ConstAddressExprProcessor(node->children[0]);
    ConstExpr op1  = ConstAddressExprProcessor(node->children[1]);
    ConstExpr op2  = ConstAddressExprProcessor(node->children[2]);
    if(cond.type & CONST_EXPR_ARITHMETIC){
      return cond.value
        ? (ConstExpr){ op1.obj_ref, op1.value, op1.type }
        : (ConstExpr){ op2.obj_ref, op2.value, op2.type };
    }
    else goto error;
  }

  default: {
  error:
    const_expr_valid = 0;
    return (ConstExpr){ 0, 0, 0 };
  }

  }
}