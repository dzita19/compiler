#include "expr.h"

#include "stmt/expr/arithm.h"
#include "stmt/expr/logic.h"
#include "stmt/expr/prefix.h"

#include "gen/resources.h"

ExprNode* ExprNodeCreateEmpty(){
  ExprNode* expr_node   = malloc(sizeof(ExprNode));
  expr_node->type       = 0;
  expr_node->obj_ref    = 0;
  expr_node->string_ref = 0;
  expr_node->address    = 0;

  expr_node_alloc++;

  return expr_node;
}

void ExprNodeDump(ExprNode* node){

  static const char* expr_kind_print[] = {
    [LVALUE]          = "LVAL",
    [RVALUE]          = "RVAL",
    [ADDRESS_OF]      = "ADDR",
    [NUM_LITERAL]     = "NUMLIT",
    [STR_LITERAL]     = "STRLIT",
    [BASIC_LABEL]     = "LABEL",
    [CASE_LABEL]      = "CASE",
    [DEFAULT_LABEL]   = "DEFAULT",
    [FUNC_DEFINITION] = "FDEF",
  };

  printf("[%s] ", expr_kind_print[node->kind]);
  // printf("[%s] + ", expr_kind_print[node->kind]);

  switch(node->kind){
  case LVALUE:
    if(node->obj_ref) printf("Name: %s; ", node->obj_ref->name);
    if(node->address >= 0) printf("Address: %d; ",  +node->address);
    else                   printf("Address: -%d; ", -node->address);
    printf("Type: ");
    StructDump(node->type);
    printf(";");
    break;

  case RVALUE:
    printf("Type: ");
    StructDump(node->type);
    printf("; ");
    if(node->address >= 0) printf("Address: %d;",  +node->address);
    else                   printf("Address: -%d;", -node->address);
    break;

  case ADDRESS_OF:
    if(node->obj_ref) printf("Name: %s; ", node->obj_ref->name);
    printf("Address: %d; ", node->address);
    printf("Type: ");
    StructDump(node->type);
    printf(";");
    break;
    
  case NUM_LITERAL:
    printf("Type: ");
    StructDump(node->type);
    printf("; Value: %d;", node->address);
    break;

  case STR_LITERAL:
    printf("Value: %s", (const char*)string_table->content[node->string_ref]);
    printf("; Type: ");
    StructDump(node->type);
    break;

  case CASE_LABEL:
    printf("Value: %d;", node->address);
    break;

  case BASIC_LABEL:
    printf("Name: %s;", node->obj_ref->name);
    break;

  case FUNC_DEFINITION:
    printf("Name: %s;", node->obj_ref->name);
    break;

  default: break;
  }

}

void ExprNodeDrop(ExprNode* node){
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

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->type = predefined_types_struct + INT32_T;
  node->expr_node->kind = NUM_LITERAL;
  node->expr_node->address = value;
}

static int SubexprIsLogic(TreeNode*);

static int SubexprIsArithmetic(TreeNode* node){
  return !SubexprIsLogic(node);
}

static int SubexprIsLogic(TreeNode* node){
  Production production = node->production;
  return (production >= RELA_GT_EXPR && production <= RELA_NQ_EXPR)
    || (production >= LOG_AND_EXPR && production <= LOG_OR_EXPR)
    || production == LOG_NOT_EXPR
    || (production == COMMA_EXPR && SubexprIsLogic(node->children[node->num_of_children - 1]));
}

void ConvertChildToArithmetic(TreeNode* node, int index){
  if(SubexprIsArithmetic(node->children[index])) return;

  StackPush(&tree->stack, node->children[index]);
  InsertConstant(1);
  InsertConstant(0);

  CondExpr();

  node->children[index] = StackPop(&tree->stack);
  node->children[index]->parent = node;
}

void ConvertChildToLogic(TreeNode* node, int index){
  if(SubexprIsLogic(node->children[index])) return;

  StackPush(&tree->stack, node->children[index]);
  InsertConstant(0);
  
  EqualityExpr(RELA_NQ_EXPR);

  node->children[index] = StackPop(&tree->stack);
  node->children[index]->parent = node;
}

void ConvertChildToPointer(TreeNode* node, int index){
  TreeNode* child = node->children[index];
  TreeNode* ptr_node = child->children[0];
  ptr_node->expr_node->type = StructIsArray(child->expr_node->type) 
    ? StructArrayToPtr(child->expr_node->type)
    : StructFunctionToPtr(child->expr_node->type);

  ptr_node->parent = node;
  node->children[index] = ptr_node;
  child->parent = 0;
  child->children[0] = 0;

  TreeNodeDrop(child);
}

void ExprDivideByConst (TreeNode* node, Struct* type, int value){
  if(value == 0 || value == 1) return;

  // node is already on top of the stack!!!
  InsertConstant(value);
  MulExpr(DIV_EXPR);

  // divided is on top of the stack, its children are node and constant
}

void SubexprMultiplyByConst(TreeNode* node, int index, int value){
  if(value == 0 || value == 1) return;

  StackPush(&tree->stack, node->children[index]);
  InsertConstant(value);

  MulExpr(MUL_EXPR);

  node->children[index] = StackPop(&tree->stack);
  node->children[index]->parent = node;
}

void SubexprImplCast(TreeNode* node, int index, Struct* type){
  if(!StructIsScalar(type) || !StructIsScalar(node->children[index]->expr_node->type)) return;

  if(StructIsPointer(type)) type = predefined_types_struct + UINT32_T; // important - pointers are treated as unsigned int

  Struct* child_type = node->children[index]->expr_node->type;
  if(StructIsPointer(child_type)) child_type = predefined_types_struct + UINT32_T;

  if(type == child_type) return;

  StackPush(&typename_stack, type);
  StackPush(&tree->stack, node->children[index]);
  CastExpr();

  node->children[index] = StackPop(&tree->stack);
  node->children[index]->parent = node;
}

void VoidExpr(void){
  TreeInsertNode(tree, VOID_EXPR, 0);
}

void CommaExprOpen(void){
  StackPush(&comma_expr_stack, 0);
}

void CommaExpr(void){
  comma_expr_stack.top->info++;
}

void FullExpr(void){
  int comma_list_len = (int)(long)StackPop(&comma_expr_stack);

  if(comma_list_len == 0) return;

  TreeNode* node = TreeInsertNode(tree, COMMA_EXPR, comma_list_len + 1);

  if(!CheckSubexprValidity(node, comma_list_len + 1));
  
  for(int i = 0; i < node->num_of_children; i++){
    if(StructIsArray(node->children[i]->expr_node->type)
        || StructIsFunction(node->children[i]->expr_node->type)){
      ConvertChildToPointer(node, i);
    }
  }

  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = RVALUE;
  node->expr_node->type = node->children[comma_list_len]->expr_node->type;
}