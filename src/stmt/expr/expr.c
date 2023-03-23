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
    [LVALUE] = "LVAL",
    [FUNC_DESIGNATOR] = "FDES",
    [RVALUE] = "RVAL",
    [NUM_LITERAL] = "NUMLIT",
    [STR_LITERAL] = "STRLIT",
  };

  printf("[%s] + ", expr_kind_print[node->kind]);

  switch(node->kind){
  case LVALUE:
    if(node->obj_ref) printf("Name: %s; ", node->obj_ref->name);
    else printf("Address: 0x%04lX; ", node->address);
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
    printf("; Value: 0x%04lX;", node->address);
    break;

  case STR_LITERAL:
    printf("Type: ");
    StructDump(node->type);
    printf("; Value: %s;", (const char*)string_table->content[node->address]);
    break;
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

void CommaExprOpen(){
  StackPush(&comma_expr_stack, 0);
}

void CommaExpr(){
  comma_expr_stack.top->info++;
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