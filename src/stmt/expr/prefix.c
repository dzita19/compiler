#include "prefix.h"

void DerefExpr(){
  TreeNode* node = TreeInsertNode(tree, DEREF_EXPR, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  Struct* operand = StructGetUnqualified(node->children[0]->expr_node->type);

  if(StructIsArray(operand)){
    operand = StructArrayToPtr(operand);
  }
  if(!StructIsPointer(operand) && !IsNullPointer(node->children[0]->expr_node)){
    ReportError("Only pointers can be dereferenced.");
    return;
  }

  if(operand->parent->type == TYPE_INCOMPLETE){
    ReportError("Incomplete type not allowed.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = LVALUE;
  expr_node->type = operand->parent;

  node->expr_node = expr_node;
}

void UnaryExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  Struct* operand = node->children[0]->expr_node->type;

  if(!StructIsArithmetic(operand)){
    ReportError("Only arithmetic types allowed for unary operations.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetUnqualified(operand);

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 0);
}

void AddressExpr(){
  TreeNode* node = TreeInsertNode(tree, ADDRESS_EXPR, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  ExprNode* operand = node->children[0]->expr_node;

  if(operand->kind != LVALUE){
    ReportError("Operand of address operation must be lvalue.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructToPtr(operand->type);

  node->expr_node = expr_node;
}

void BitNegExpr(){
  TreeNode* node = TreeInsertNode(tree, BIT_NOT, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  Struct* operand = node->children[0]->expr_node->type;

  if(!StructIsArithmetic(operand)){
    ReportError("Only arithmetic types allowed for bitwise operations.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetUnqualified(operand);

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 0);
}

void LogNegExpr(){
  TreeNode* node = TreeInsertNode(tree, LOG_NOT, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  Struct* operand = node->children[0]->expr_node->type;

  if(!StructIsScalar(operand)){
    ReportError("Only scalar types allowed for bitwise operations.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructGetUnqualified(operand);

  node->expr_node = expr_node;
  
  ConvertChildToLogic(node, 0);
}

void SizeofExpr(){
  TreeNode* expression_tree = StackPop(&tree->stack);

  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  if(expression_tree->expr_node == 0) return; // error detected earlier

  Struct* type = expression_tree->expr_node->type;
  if(type == 0) return; // error detected earlier

  if(type->type != TYPE_OBJECT){
    ReportError("Cannot determine size of incomplete type.");
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
  if(type == 0) return; // error detected earlier

  if(type->type != TYPE_OBJECT){
    ReportError("Cannot determine size of uncomplete type.");
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

  if(!CheckSubexprValidity(node, 1)) return;

  if(StructIsArray(node->children[0]->expr_node->type)){
    ConvertChildToPointer(node, 0);
  }
  
  Struct* from = node->children[0]->expr_node->type;
  Struct* to = StackPop(&typename_stack);

  if(to == 0){
    ReportError("Unknown type.");
    return;
  }

  if(!StructIsScalar(from) || !StructIsScalar(to)){
    ReportError("Cast possible only between two scalar types.");
    return;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = to;

  node->expr_node = expr_node;
  
  ConvertChildToArithmetic(node, 0);
}