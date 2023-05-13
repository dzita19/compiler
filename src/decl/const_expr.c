#include "const_expr.h"

#include <stdint.h>

static int const_expr_valid = 0;

void ConstExpression(){
  TreeNode* const_expr_node = StackPop(&tree->stack);

  ConstExpr* const_expr = ConstExprCreateEmpty();
  
  const_expr_valid = 1;
  int const_expr_arith = ConstArithmeticExprProcessor(const_expr_node);

  if(const_expr_valid) {
    const_expr->type |= CONST_EXPR_ARITHMETIC;
    const_expr->value = const_expr_arith;
  }

  StackPush(&const_expr_stack, const_expr);

  TreeNodeDrop(const_expr_node);
}

ConstExpr ConstExprCalculate(TreeNode* const_expr_node){
  ConstExpr const_expr = (ConstExpr){ 0, 0, 0, 0 };
  
  const_expr_valid = 1;
  int const_expr_arith = ConstArithmeticExprProcessor(const_expr_node);

  if(const_expr_valid) {
    const_expr.type |= CONST_EXPR_ARITHMETIC;
    const_expr.value = const_expr_arith;
  }

  const_expr_valid = 1;
  ConstExpr addr_expr = ConstAddressExprProcessor(const_expr_node);
  if(const_expr_valid) {
    const_expr.type |= addr_expr.type;
    const_expr.obj_ref = addr_expr.obj_ref;
    const_expr.string_ref = addr_expr.string_ref;
    const_expr.value = addr_expr.value;
  }

  return const_expr;
}

int ConstArithmeticExprProcessor(TreeNode* node){

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
    if(node->expr_node->type == predefined_types_struct + INT8_T)
      return (int8_t)   ConstArithmeticExprProcessor(node->children[0]);
    if(node->expr_node->type == predefined_types_struct + UINT8_T)
      return (uint8_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->expr_node->type == predefined_types_struct + INT16_T)
      return (int16_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->expr_node->type == predefined_types_struct + UINT16_T)
      return (uint16_t) ConstArithmeticExprProcessor(node->children[0]);
    if(node->expr_node->type == predefined_types_struct + INT32_T)
      return (int32_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->expr_node->type == predefined_types_struct + UINT32_T)
      return (uint32_t) ConstArithmeticExprProcessor(node->children[0]);
    if(node->expr_node->type == predefined_types_struct + INT64_T)
      return (int64_t)  ConstArithmeticExprProcessor(node->children[0]);
    if(node->expr_node->type == predefined_types_struct + UINT64_T)
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

  if(const_expr_valid == 0) return (ConstExpr){ 0, 0, 0, 0 };

  switch(node->production){
  case CONSTANT_PRIMARY: {
    if(node->expr_node->address == 0) 
      return (ConstExpr){ 
        .obj_ref    = 0, 
        .string_ref = 0, 
        .value      = 0, 
        .type       = CONST_EXPR_ADDRESS
      };
    else goto error;
  }
  case STRING_PRIMARY: {
    return (ConstExpr){ 
      .obj_ref    = 0, 
      .string_ref = node->expr_node->address, 
      .value      = 0, 
      .type       = CONST_EXPR_STRING
    };
  }
  case ADDRESS_EXPR: {
    TreeNode* child = node->children[0];
    
    if(child->production == IDENTIFIER_PRIMARY){
      if((child->expr_node->obj_ref->specifier & STORAGE_FETCH) != STORAGE_STATIC) goto error;
      
      return (ConstExpr){
        .obj_ref    = child->expr_node->obj_ref, 
        .string_ref = 0, 
        .value      = child->expr_node->address, 
        .type       = CONST_EXPR_ADDRESS
      };
    }
    else if(child->production == DEREF_EXPR){
      ConstExpr ret = ConstAddressExprProcessor(child->children[0]);
      if(const_expr_valid == 0) goto error;

      return (ConstExpr){ 
        .obj_ref    = ret.obj_ref, 
        .string_ref = ret.string_ref, 
        .value      = ret.value + child->expr_node->address, 
        .type       = ret.type
      };
    }
    else goto error;
  }
  case CAST_EXPR: {
    if(StructIsArithmetic(node->children[0]->expr_node->type)){
      int operand = ConstArithmeticExprProcessor(node->children[0]);
      if(const_expr_valid == 0) goto error;

      if(StructIsPointer(node->expr_node->type))
        return (ConstExpr){ 
          .obj_ref    = 0, 
          .string_ref = 0, 
          .value      = operand, 
          .type       = CONST_EXPR_ADDRESS
        };
      
      else goto error;
    }
    else{
      ConstExpr operand = ConstAddressExprProcessor(node->children[0]);
      if(const_expr_valid == 0) goto error;

      if(StructIsPointer(node->expr_node->type))
        return (ConstExpr){ 
          .obj_ref    = operand.obj_ref, 
          .string_ref = operand.string_ref, 
          .value      = operand.value, 
          .type       = operand.type
        };
      
      else goto error;
    }
  }

  case ADD_EXPR: {
    TreeNode* op1 = node->children[0];
    TreeNode* op2 = node->children[1];

    int offset1, offset2;

    if(StructIsArithmetic(op1->expr_node->type)) offset1 = ConstArithmeticExprProcessor(op1);
    if(StructIsArithmetic(op2->expr_node->type)) offset2 = ConstArithmeticExprProcessor(op2);

    if(const_expr_valid == 0) goto error;

    if(StructIsPointer(op1->expr_node->type)){
      ConstExpr ret = ConstAddressExprProcessor(op1);
      if(const_expr_valid == 0) goto error;

      ret.value += offset2;
      return ret;
    }
    else
    if(StructIsPointer(op2->expr_node->type)){
      ConstExpr ret = ConstAddressExprProcessor(op2);
      if(const_expr_valid == 0) goto error;
      
      ret.value += offset1;
      return ret;
    }
    else goto error;
  }
  case SUB_EXPR: {
    TreeNode* op1 = node->children[0];
    TreeNode* op2 = node->children[1];

    int offset;

    if(StructIsArithmetic(op2->expr_node->type)) offset = ConstArithmeticExprProcessor(op2);
    else goto error;

    if(const_expr_valid == 0) goto error;

    if(StructIsPointer(op1->expr_node->type)){
      ConstExpr ret = ConstAddressExprProcessor(op1);
      if(const_expr_valid == 0) goto error;

      ret.value -= offset;
      return ret;
    }
    else goto error;
  }

  default: {
  error:
    const_expr_valid = 0;
    return (ConstExpr){ 
      .obj_ref    = 0, 
      .string_ref = 0, 
      .value      = 0, 
      .type       = 0
    };
  }

  }
}