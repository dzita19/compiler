#include "prefix.h"

void DerefExpr(){
  TreeNode* node = TreeInsertNode(tree, DEREF_EXPR, 1);

  if(node->children[0]->expr_node == 0){
    return;
  }
  
  if(StructIsArray(node->children[0]->expr_node->type) 
      || StructIsFunction(node->children[0]->expr_node->type))
    ConvertChildToPointer(node, 0);

  TreeNode* op_node = node->children[0]; // this node is value to be dereffed

  Struct* operand = StructGetUnqualified(op_node->expr_node->type);
  if(!StructIsPointer(operand) && !IsNullPointer(op_node->expr_node)){
    ReportError("Only pointers can be dereferenced.");
    return;
  }

  if(operand->parent->type == TYPE_INCOMPLETE){
    ReportError("Incomplete type not allowed.");
    return;
  }

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = LVALUE;
  node->expr_node->type = StructGetUnqualified(operand)->parent;
}

void AddressExpr(){
  TreeNode* node = StackPeek(&tree->stack); // this node is lval - modify it to be address-of expr

  if(node->expr_node == 0){
    return;
  }

  if(node->expr_node->kind != LVALUE){
    ReportError("Operand of address operation must be lvalue.");
    return;
  }

  // if(node->production == VALUE_PRIMARY){
  //   node->production = ADDRESS_PRIMARY;
  //   node->expr_node->kind = ADDRESS_OF;
  //   node->expr_node->type = StructToPtr(node->expr_node->type);
  // }
  // else 
  if(node->production == DEREF_EXPR){
    TreeNode* primary = node->children[0];
    primary->parent = node->parent; // primary->parent = 0;
    node->children[0] = 0;
    
    TreeNodeDrop(StackPop(&tree->stack)); // node should be popped from stack
    StackPush(&tree->stack, primary);
  }
}

void UnaryExpr(Production production){
  TreeNode* node = TreeInsertNode(tree, production, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  Struct* operand = node->children[0]->expr_node->type;
  Struct* expr_type = 0;

  if(!StructIsArithmetic(operand)){
    ReportError("Only arithmetic types allowed for unary operations.");
    return;
  }

  expr_type = StructGetUnqualified(operand);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 0);

  TryFold();
}

void BitNotExpr(){
  TreeNode* node = TreeInsertNode(tree, BIT_NOT_EXPR, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  Struct* operand = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsArithmetic(operand)){
    ReportError("Only arithmetic types allowed for bitwise operations.");
    return;
  }

  expr_type = StructGetExprIntType(operand, operand);

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 0);

  SubexprImplCast(node, 0, expr_type);

  TryFold();
}

void LogNotExpr(){
  TreeNode* node = TreeInsertNode(tree, LOG_NOT_EXPR, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
    || StructIsFunction(node->children[0]->expr_node->type)) ConvertChildToPointer(node, 0);

  Struct* operand = StructGetUnqualified(node->children[0]->expr_node->type);
  Struct* expr_type = 0;

  if(!StructIsScalar(operand)){
    ReportError("Only scalar types allowed for logic operations.");
    return;
  }

  expr_type = predefined_types_struct + INT32_T;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToLogic(node, 0);

  TryFold();
}

void SizeofExpr(){
  TreeNode* expression_tree = StackPop(&tree->stack);

  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  if(expression_tree->expr_node == 0) { // error detected earlier
    TreeNodeDrop(expression_tree);
    return;
  }

  Struct* type = expression_tree->expr_node->type;
  if(type == 0) { // error detected earlier
    TreeNodeDrop(expression_tree);
    return;
  }

  Struct* expr_type = 0;

  if(type->type != TYPE_OBJECT){
    ReportError("Cannot determine size of incomplete type.");
    return;
  }

  expr_type = predefined_types_struct + INT32_T;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = NUM_LITERAL;
  node->expr_node->type = expr_type;
  node->expr_node->address = type->size;

  TreeNodeDrop(expression_tree);
}

void SizeofTypeExpr(){
  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);
  
  Struct* type = StackPop(&typename_stack);
  if(type == 0) return; // error detected earlier

  Struct* expr_type = 0;

  if(type->type != TYPE_OBJECT){
    ReportError("Cannot determine size of uncomplete type.");
    return;
  }

  expr_type = predefined_types_struct + INT32_T;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = NUM_LITERAL;
  node->expr_node->type = expr_type;
  node->expr_node->address = type->size;
}

void CastExpr(){
  TreeNode* node = TreeInsertNode(tree, CAST_EXPR, 1);

  if(!CheckSubexprValidity(node, 1)) return;

  if(StructIsArray(node->children[0]->expr_node->type)
      || StructIsFunction(node->children[0]->expr_node->type)){
    ConvertChildToPointer(node, 0);
  }
  
  Struct* from = node->children[0]->expr_node->type;
  Struct* to = StackPop(&typename_stack);
  Struct* expr_type = 0;

  if(to == 0){
    ReportError("Unknown type.");
    return;
  }

  if(!StructIsScalar(from) || !StructIsScalar(to)){
    ReportError("Cast possible only between two scalar types.");
    return;
  }

  expr_type = to;

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = expr_type;
  
  ConvertChildToArithmetic(node, 0);

  TryFold();
}