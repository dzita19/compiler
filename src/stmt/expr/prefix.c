#include "prefix.h"

void DerefExpr(){
  TreeNode* node = TreeInsertNode(tree, DEREF_EXPR, 1);

  Struct* operand = StructGetUnqualified(node->children[0]->expr_node->type);

  if(StructIsArray(operand)){
    operand = StructArrayToPtr(operand);
  }
  if(!StructIsPointer(operand) && !IsNullPointer(node->children[0]->expr_node)){
    printf("ERROR: Only pointers can be dereferenced.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = LVALUE;
  expr_node->type = StructGetUnqualified(operand->parent);

  node->expr_node = expr_node;
}

void UnaryExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 1);

  Struct* operand = node->children[0]->expr_node->type;

  if(!StructIsArithmetic(operand)){
    printf("ERROR: Only arithmetic types allowed for unary operations.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetUnqualified(operand);

  node->expr_node = expr_node;
}

void AddressExpr(){
  TreeNode* node = TreeInsertNode(tree, ADDRESS_EXPR, 1);

  ExprNode* operand = node->children[0]->expr_node;

  if(operand->kind != LVALUE){
    printf("ERROR: Operand of address operation must be lvalue.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructToPtr(operand->type);

  node->expr_node = expr_node;
}

void BitNegExpr(){
  TreeNode* node = TreeInsertNode(tree, BIT_NOT, 1);

  Struct* operand = node->children[0]->expr_node->type;

  if(!StructIsArithmetic(operand)){
    printf("ERROR: Only arithmetic types allowed for bitwise operations.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetUnqualified(operand);

  node->expr_node = expr_node;
}

void LogNegExpr(){
  TreeNode* node = TreeInsertNode(tree, BIT_NOT, 1);

  Struct* operand = node->children[0]->expr_node->type;

  if(!StructIsScalar(operand)){
    printf("ERROR: Only scalar types allowed for bitwise operations.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetUnqualified(operand);

  node->expr_node = expr_node;
}

void SizeofExpr(){
  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  TreeNode* expression_tree = StackPop(&tree->stack);

  Struct* type = expression_tree->expr_node->type;
  if(type->type == TYPE_INCOMPLETE || type->type == TYPE_ARRAY_UNSPEC){
    printf("ERROR: Cannot determine size of uncomplete type.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = NUM_LITERAL;
  expr_node->type = predefined_types_struct + INT32_T;
  expr_node->address = type->size;

  node->expr_node = expr_node;

  TreeNodeDrop(expression_tree);
}

void SizeofTypeExpr(){

  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);
  
  Struct* type = StackPop(&typename_stack);

  if(type->type == TYPE_INCOMPLETE || type->type == TYPE_ARRAY_UNSPEC){
    printf("ERROR: Cannot determine size of uncomplete type.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = NUM_LITERAL;
  expr_node->type = predefined_types_struct + INT32_T;
  expr_node->address = type->size;

  node->expr_node = expr_node;
}

void CastExpr(){
  TreeNode* node = TreeInsertNode(tree, CAST_EXPR, 1);
  
  Struct* from = node->children[0]->expr_node->type;
  Struct* to = StackPop(&typename_stack);

  if(!StructIsScalar(from) || !StructIsScalar(to)){
    printf("ERROR: Cast possible only between two arithmetic types.\n");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = to;

  node->expr_node = expr_node;
}