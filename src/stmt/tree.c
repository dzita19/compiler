#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

#include "util/stack.h"
#include "expr/expr.h"

const char* production_names[] = {
  [IDENTIFIER_PRIMARY]    = "Identifier",
  [CONSTANT_PRIMARY]      = "Constant",
  [STRING_PRIMARY]        = "String",

  [ARRAY_REF_EXPR]        = "Array ref",
  [FUNCTION_CALL_EXPR]    = "Function call",
  [FIELD_REF_EXPR]        = "Field ref",
  [PTR_REF_EXPR]          = "Pointer ref",
  [POST_INC_EXPR]         = "Postfix inc",
  [POST_DEC_EXPR]         = "Postfix dec",

  [FUNCTION_ARG]          = "Function arg",

  [PRE_INC_EXPR]          = "Prefix inc",
  [PRE_DEC_EXPR]          = "Prefix dec",
  [DEREF_EXPR]            = "Deref pointer",
  [UNARY_PLUS_EXPR]       = "Unary plus",
  [UNARY_MINUS_EXPR]      = "Unary minus",
  [ADDRESS_EXPR]          = "Address of",
  [BIT_NOT]               = "Bitwise not",
  [LOG_NOT]               = "Logic not",

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
  [RELA_NE_EXPR]          = "Not equals",

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



  [INITIALIZER]           = "Initializer",

  [EXPRESSION_STMT]       = "Expression statement",
  [EMPTY_STMT]            = "Empty statement",

  [COMPOUND_STMT]         = "Compound statement",

  [FUNCTION_BODY]         = "Function body",
  [TRANSLATION_UNIT]      = "Translation unit",
};

TreeNode* TreeNodeCreateEmpty(){
  TreeNode* tree_node = malloc(sizeof(TreeNode));
  tree_node->production = 0;
  tree_node->num_of_children = 0;
  tree_node->parent = 0;
  tree_node->children = 0;

  tree_node_alloc++;

  return tree_node;
}

void TreeNodeDrop(TreeNode* node){
  for(int i = 0; i < node->num_of_children; i++){
    TreeNodeDrop(node->children[i]);
  }
  if(node->expr_node) ExprNodeDrop(node->expr_node);
  free(node);

  tree_node_free++;
}

int tree_indent = 0;

void print_tree_indent(){
  for(int i = 0; i < tree_indent; i++) printf("-");
}

void TreeNodeDump(TreeNode* node){
  print_tree_indent();
  printf("%s ", production_names[node->production]);
  if(node->expr_node) ExprNodeDump(node->expr_node);
  printf("\n");
  
  tree_indent++;
  for(int i = 0; i < node->num_of_children; i++){
    TreeNodeDump(node->children[i]);
  }
  tree_indent--;
}

Tree* TreeCreateEmpty(){
  Tree* tree = malloc(sizeof(Tree));
  tree->root = 0;
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
  tree->root = node;

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

    // if(production_names[root->type]){
    //   for(int i = 0; i < indent; i++) printf("  ");
    //   printf("+%s\n", production_names[root->type]);
    // }

    StackPush(&preorder_stack, (void*)-2);
    for(int i = root->num_of_children - 1; i >= 0; i--){
      StackPush(&preorder_stack, root->children[i]);
    }  
    StackPush(&preorder_stack, (void*)-1);
  }
}