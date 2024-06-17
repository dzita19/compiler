#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

#include "util/stack.h"
#include "expr/expr.h"
#include "gen/link_flow.h"
#include "gen/resources.h"

const char* production_names[] = {
  [VOID_EXPR]             = "Void expression",

  [ADDRESS_PRIMARY]       = "Address of",
  [CONSTANT_PRIMARY]      = "Constant",
  [STRING_PRIMARY]        = "String",

  [FIELD_REF_EXPR]        = "Field ref",
  [FUNCTION_CALL_EXPR]    = "Function call",
  [POST_INC_EXPR]         = "Postfix inc",
  [POST_DEC_EXPR]         = "Postfix dec",
  [COMPOUND_LITERAL]      = "Compound literal",

  [PRE_INC_EXPR]          = "Prefix inc",
  [PRE_DEC_EXPR]          = "Prefix dec",
  [DEREF_EXPR]            = "Deref pointer",
  [UNARY_PLUS_EXPR]       = "Unary plus",
  [UNARY_MINUS_EXPR]      = "Unary minus",
  [BIT_NOT_EXPR]          = "Bitwise not",
  [LOG_NOT_EXPR]          = "Logic not",

  [CAST_EXPR]             = "Cast",

  [MUL_EXPR]              = "Multiplication",
  [DIV_EXPR]              = "Division",
  [MOD_EXPR]              = "Modulo",

  [ADD_EXPR]              = "Addition",
  [SUB_EXPR]              = "Subtraction",

  [BIT_LEFT_EXPR]         = "Left shift",
  [BIT_RIGHT_EXPR]        = "Right shift",

  [RELA_GT_EXPR]          = "Greater than",
  [RELA_LT_EXPR]          = "Less than",
  [RELA_GE_EXPR]          = "Greater equal",
  [RELA_LE_EXPR]          = "Less equal",

  [RELA_EQ_EXPR]          = "Equals",
  [RELA_NQ_EXPR]          = "Not equals",

  [BIT_AND_EXPR]          = "Bitwise and",
  [BIT_XOR_EXPR]          = "Bitwise xor",
  [BIT_OR_EXPR]           = "Bitwise or",

  [LOG_AND_EXPR]          = "Logic and",
  [LOG_OR_EXPR]           = "Logic or",

  [COND_EXPR]             = "Ternary",

  [ASSIGN_EXPR]           = "Assign",
  [MUL_ASSIGN_EXPR]       = "Mul assign",
  [DIV_ASSIGN_EXPR]       = "Div assign",
  [MOD_ASSIGN_EXPR]       = "Mod assign",
  [ADD_ASSIGN_EXPR]       = "Add assign",
  [SUB_ASSIGN_EXPR]       = "Sub assign",

  [BIT_LEFT_ASSIGN_EXPR]  = "Left assign",
  [BIT_RIGHT_ASSIGN_EXPR] = "Rigth assign",
  [BIT_AND_ASSIGN_EXPR]   = "And assign", 
  [BIT_XOR_ASSIGN_EXPR]   = "Xor assign", 
  [BIT_OR_ASSIGN_EXPR]    = "Or assign",

  [COMMA_EXPR]            = "Comma list",

  [FOR_DECL]              = "For declarators",
  [INITIALIZATION]        = "Initialization",
  [COMPOUND_STMT]         = "Compound statement",

  [INITIALIZER_LOOP]      = "Initializer loop",

  [LABEL_STMT]            = "Label",
  [CASE_STMT]             = "Case label",
  [DEFAULT_STMT]          = "Default label",

  [EXPRESSION_STMT]       = "Expression statement",
  [EMPTY_STMT]            = "Empty statement",

  [IF_STMT]               = "If statement",
  [IF_ELSE_STMT]          = "If-else statement",
  [SWITCH_STMT]           = "Switch statement",
  
  [WHILE_STMT]            = "While statement",
  [DO_WHILE_STMT]         = "Do-while statement",
  [FOR_STMT]              = "For statement",

  [GOTO_STMT]             = "Goto statement",
  [CONTINUE_STMT]         = "Continue statement",
  [BREAK_STMT]            = "Break statement",
  [RETURN_STMT]           = "Return statement",
  [RETURN_EXPR_STMT]      = "Return expr statement",

  [INLINE_ASM_STMT]       = "Inline assembler",

  [FUNC_PROLOGUE]         = "Function prologue",
  [FUNC_EPILOGUE]         = "Function epilogue",

  [FUNCTION_BODY]         = "Function body",
  [TRANSLATION_UNIT]      = "Translation unit",
};

const int production_kind[] = {
  [VOID_EXPR          ... COMMA_EXPR]       = PRODUCTION_EXPR,
  [LABEL_STMT         ... DEFAULT_STMT]     = PRODUCTION_STMT,
  [INITIALIZATION     ... TRANSLATION_UNIT] = PRODUCTION_STMT,
};

TreeNode* TreeNodeCreateEmpty(){
  static int tree_node_curr_id = 0;

  TreeNode* tree_node = malloc(sizeof(TreeNode));
  tree_node->id = ++tree_node_curr_id;
  tree_node->label           = 0;
  tree_node->production      = 0;
  tree_node->num_of_children = 0;
  tree_node->parent          = 0;
  tree_node->children        = 0;
  tree_node->expr_node       = 0;
  tree_node->logic_node      = 0;
  tree_node->mem_alloc       = 0;

  tree_node_alloc++;

  return tree_node;
}

void TreeNodeDrop(TreeNode* node){
  for(int i = 0; i < node->num_of_children; i++){
    if(node->children[i]) TreeNodeDrop(node->children[i]);
  }
  free(node->children);
  if(node->expr_node)  ExprNodeDrop(node->expr_node);
  if(node->logic_node) LogicNodeDrop(node->logic_node);
  if(node->mem_alloc)  MemAllocDrop(node->mem_alloc);
  free(node);

  tree_node_free++;
}

int tree_indent = 0;

void print_tree_indent(){
  for(int i = 0; i < tree_indent; i++) printf("-");
}

void TreeNodeDump(TreeNode* node){
  print_tree_indent();
  printf("%s ::", production_names[node->production]);
  if(node->label != 0) printf(" %d", node->id);
  if(node->expr_node){
    printf(" ");
    ExprNodeDump(node->expr_node);
  }
  if(node->logic_node){
    printf(" ");
    LogicNodeDump(node->logic_node);
  }
  if(node->parent == 0 && node->production != TRANSLATION_UNIT){
    printf(" ERROR");
  }
  printf("\n");
  
  tree_indent++;
  for(int i = 0; i < node->num_of_children; i++){
    TreeNodeDump(node->children[i]);
  }
  tree_indent--;
}

Tree* TreeCreateEmpty(){
  Tree* tree = malloc(sizeof(Tree));
  tree->stack = (Stack){ 0 };

  tree_alloc++;

  return tree;
}

void TreeDrop(Tree* tree){
  while(!StackEmpty(&tree->stack)){ // root is on top of the stack (no need to explicitly free it)
    TreeNode* node = StackPop(&tree->stack);
    TreeNodeDrop(node);
  }

  free(tree);

  tree_free++;
}

void TreeDump(Tree* tree){
  StackNode* current = tree->stack.top;
  while(current){
    TreeNodeDump(current->info);
    current = current->next;
  }
}

TreeNode* TreeInsertNode(Tree* tree, Production production, int num_of_children){
  TreeNode* node = TreeNodeCreateEmpty();

  node->production = production;
  node->num_of_children = num_of_children;
  if(num_of_children)
    node->children = malloc(sizeof(TreeNode*) * num_of_children);
  else node->children = 0;

  for(int i = num_of_children - 1; i >= 0; i--){
    node->children[i] = StackPop(&tree->stack);
    node->children[i]->parent = node;
  }

  StackPush(&tree->stack, node);

  return node;
}

// preorder
void TreeNodePrint(TreeNode* root){
  Stack preorder_stack = { 0 };
  StackPush(&preorder_stack, root);

  int indent = 0;
  while(preorder_stack.top){
    root = StackPop(&preorder_stack);

    if(!root) continue;
    if(root == (void*)-1) { indent++; continue; }
    if(root == (void*)-2) { indent--; continue; }

    StackPush(&preorder_stack, (void*)-2);
    for(int i = root->num_of_children - 1; i >= 0; i--){
      StackPush(&preorder_stack, root->children[i]);
    }  
    StackPush(&preorder_stack, (void*)-1);
  }
}