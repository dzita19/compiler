#include "expr.h"

LogicNode* LogicNodeCreateEmpty(){
  LogicNode* node = malloc(sizeof(LogicNode));

  logic_node_alloc++;
}

void LogicNodeDump(ExprNode* node){
  
}

void LogicNodeDrop(LogicNode* node){
  free(node);

  logic_node_free++;
}

ExprNode* ExprNodeCreateEmpty(){
  ExprNode* expr_node = malloc(sizeof(ExprNode));
  expr_node->type = 0;
  expr_node->obj_ref = 0;
  expr_node->address = 0;
  expr_node->logic = 0;

  expr_node_alloc++;

  return expr_node;
}

void ExprNodeDump(ExprNode* node){

  static const char* expr_kind_print[] = {
    [LVALUE]          = "LVAL",
    [FUNC_DESIGNATOR] = "FDES",
    [RVALUE]          = "RVAL",
    [NUM_LITERAL]     = "NUMLIT",
    [STR_LITERAL]     = "STRLIT",
    [CASE_LABEL]      = "CASE",
  };

  printf("[%s] + ", expr_kind_print[node->kind]);

  switch(node->kind){
  case LVALUE:
    if(node->obj_ref) printf("Name: %s; ", node->obj_ref->name);
    printf("Address: 0x%04X; ", node->address);
    printf("Type: ");
    StructDump(node->type);
    printf(";");
    break;

  case FUNC_DESIGNATOR:
    printf("Name: %s; ", node->obj_ref->name);
    printf("Type: ");
    StructDump(node->type);
    printf(";");
    break;

  case RVALUE:
    printf("Type: ");
    StructDump(node->type);
    printf(";");
    break;

  case NUM_LITERAL:
    printf("Type: ");
    StructDump(node->type);
    printf("; Value: 0x%04X;", node->address);
    break;

  case STR_LITERAL:
    printf("Type: ");
    StructDump(node->type);
    printf("; Value: %s;", (const char*)string_table->content[node->address]);
    break;

  case CASE_LABEL:
    printf("Value: 0x%04X;", node->address);
  }

}

void ExprNodeDrop(ExprNode* node){
  if(node->logic) LogicNodeDrop(node->logic);
  free(node);

  expr_node_free++;
}

int IsNullPointer(ExprNode* expr_node){
  if(expr_node->kind == NUM_LITERAL && expr_node->address == 0) return 1;
  else return 0;
}

int CheckSubexprValidity(TreeNode* node, int count){
  for(int i = 0; i < count; i++){
    if(node->children[i]->expr_node == 0) return 0;
  }
  return 1;
}

void InsertConstant(int value){
  TreeNode* node = TreeInsertNode(tree, CONSTANT_PRIMARY, 0);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->type = predefined_types_struct + INT32_T;
  expr_node->kind = NUM_LITERAL;
  expr_node->address = value;

  node->expr_node = expr_node;
}

static int SubexprIsLogic(TreeNode*);

static int SubexprIsArithmetic(TreeNode* node){
  return !SubexprIsLogic(node);
}

static int SubexprIsLogic(TreeNode* node){
  Production production = node->production;
  return production >= RELA_GT_EXPR && production <= RELA_NE_EXPR
    || production >= LOG_AND_EXPR && production <= LOG_OR_EXPR
    || production == LOG_NOT;
}

void ConvertChildToArithmetic(TreeNode* node, int index){
  if(SubexprIsArithmetic(node->children[index])) return;

  StackPush(&tree->stack, node->children[index]);
  InsertConstant(1);
  InsertConstant(0);

  TreeInsertNode(tree, COND_EXPR, 3);
  TreeNode* arithmetic_conversion = StackPop(&tree->stack);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = predefined_types_struct + INT32_T;

  arithmetic_conversion->expr_node = expr_node;

  arithmetic_conversion->parent = node;
  node->children[index] = arithmetic_conversion;
}

void ConvertChildToLogic(TreeNode* node, int index){
  if(SubexprIsLogic(node->children[index])) return;

  StackPush(&tree->stack, node->children[index]);
  InsertConstant(0);

  TreeInsertNode(tree, RELA_NE_EXPR, 2);
  TreeNode* logic_conversion = StackPop(&tree->stack);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = predefined_types_struct + INT32_T;

  logic_conversion->expr_node = expr_node;

  logic_conversion->parent = node;
  node->children[index] = logic_conversion;
}

void ConvertChildToPointer(TreeNode* node, int index){
  
  StackPush(&tree->stack, node->children[index]);

  TreeInsertNode(tree, ADDRESS_EXPR, 1);
  TreeNode* address_of = StackPop(&tree->stack);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructIsArray(node->children[index]->expr_node->type)
    ? StructArrayToPtr(node->children[index]->expr_node->type)
    : StructFunctionToPtr(node->children[index]->expr_node->type);

  address_of->expr_node = expr_node;

  address_of->parent = node;
  node->children[index] = address_of;
}

void SubexprMultiplyByConst(TreeNode* node, int index, int value){
  if(value == 1) return;

  StackPush(&tree->stack, node->children[index]);
  InsertConstant(value);

  TreeInsertNode(tree, MUL_EXPR, 2);
  TreeNode* multiplied = StackPop(&tree->stack);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = node->children[index]->expr_node->type;

  multiplied->expr_node = expr_node;

  multiplied->parent = node;
  node->children[index] = multiplied;
}

void ExprDivideByConst (TreeNode* node, int value){
  if(value == 0 || value == 1) return;

  // node is already on top of the stack!!!
  InsertConstant(value);

  TreeNode* divided = TreeInsertNode(tree, DIV_EXPR, 2);
  
  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = node->expr_node->type;

  divided->expr_node = expr_node;

  // divided is on top of the stack, its children are node and constant
}

TreeNode* ExprToPointer(TreeNode* node){
  StackPush(&tree->stack, node);
  TreeInsertNode(tree, ADDRESS_EXPR, 1);
  TreeNode* address_of = StackPop(&tree->stack);
  
  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = StructIsArray(node->expr_node->type)
    ? StructArrayToPtr(node->expr_node->type)
    : StructFunctionToPtr(node->expr_node->type);

  address_of->expr_node = expr_node;

  node = address_of;

  return node;
}

void SubexprImplCast(TreeNode* node, int index, Struct* type){
  if(!StructIsScalar(type) || !StructIsScalar(node->children[index]->expr_node->type)) return;

  if(StructIsPointer(type)) type = predefined_types_struct + INT32_T;

  Struct* child_type = node->children[index]->expr_node->type;
  if(StructIsPointer(child_type)) child_type = predefined_types_struct + INT32_T;

  int father_rank = (type       - (predefined_types_struct + INT8_T)) >> 1;
  int child_rank  = (child_type - (predefined_types_struct + INT8_T)) >> 1;

  if(father_rank == child_rank) return;

  StackPush(&tree->stack, node->children[index]);
  TreeInsertNode(tree, CAST_EXPR, 1);
  TreeNode* implcast = StackPop(&tree->stack);

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = type;

  implcast->expr_node = expr_node;

  implcast->parent = node;
  node->children[index] = implcast;
}


void CommaExprOpen(){
  StackPush(&comma_expr_stack, 0);

  TreeNode* node = StackPop(&tree->stack);

  if(node->expr_node == 0){
    StackPush(&tree->stack, node);
    return;
  }

  if(StructIsArray(node->expr_node->type)
      || StructIsFunction(node->expr_node->type)){
    node = ExprToPointer(node);
  }

  StackPush(&tree->stack, node);
}

void CommaExpr(){
  comma_expr_stack.top->info++;

  TreeNode* node = StackPop(&tree->stack);

  if(node->expr_node == 0){
    StackPush(&tree->stack, node);
    return;
  }

  if(StructIsArray(node->expr_node->type)
      || StructIsFunction(node->expr_node->type)){
    node = ExprToPointer(node);
  }

  StackPush(&tree->stack, node);
}

void FullExpr(){
  int comma_list_len = (int)(long)StackPop(&comma_expr_stack);
  if(comma_list_len == 0) return;

  TreeNode* node = TreeInsertNode(tree, COMMA_EXPR, 1 + comma_list_len);
  for(int i = 0; i < comma_list_len; i++){
    node->children[0]->expr_node->type = predefined_types_struct + VOID_T;
  }

  ExprNode* expr_node = ExprNodeCreateEmpty();
  expr_node->kind = RVALUE;
  expr_node->type = node->children[comma_list_len]->expr_node->type;

  node->expr_node = expr_node;
}