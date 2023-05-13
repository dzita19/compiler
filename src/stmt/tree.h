#ifndef _TREE_H_
#define _TREE_H_

#include "util/memory_safety.h"
#include "util/stack.h"

typedef enum Production{
  IDENTIFIER_PRIMARY,
  CONSTANT_PRIMARY,
  STRING_PRIMARY,

  FUNCTION_CALL_EXPR,
  POST_INC_EXPR,
  POST_DEC_EXPR,

  FUNCTION_ARG,

  PRE_INC_EXPR,
  PRE_DEC_EXPR,
  DEREF_EXPR,
  UNARY_PLUS_EXPR,
  UNARY_MINUS_EXPR,
  ADDRESS_EXPR,
  BIT_NOT,
  LOG_NOT,

  CAST_EXPR,

  MUL_EXPR,
  DIV_EXPR,
  MOD_EXPR,

  ADD_EXPR,
  SUB_EXPR,

  BIT_LEFT_EXPR,
  BIT_RIGHT_EXPR,

  RELA_GT_EXPR,
  RELA_LT_EXPR,
  RELA_GE_EXPR,
  RELA_LE_EXPR,

  RELA_EQ_EXPR,
  RELA_NE_EXPR,

  BIT_AND_EXPR,
  BIT_XOR_EXPR,
  BIT_OR_EXPR,

  LOG_AND_EXPR,
  LOG_OR_EXPR,

  COND_EXPR,

  ASSIGN_EXPR,
  MUL_ASSIGN_EXPR,
  DIV_ASSIGN_EXPR,
  MOD_ASSIGN_EXPR,
  ADD_ASSIGN_EXPR,
  SUB_ASSIGN_EXPR,

  BIT_LEFT_ASSIGN_EXPR,
  BIT_RIGHT_ASSIGN_EXPR,
  BIT_AND_ASSIGN_EXPR, 
  BIT_XOR_ASSIGN_EXPR, 
  BIT_OR_ASSIGN_EXPR,

  COMMA_EXPR,

  INITIALIZER,
  INITIALIZER_LIST,

  COMPOUND_STMT,

  EXPRESSION_STMT,
  EMPTY_STMT,

  LABEL_STMT,
  CASE_STMT,
  DEFAULT_STMT,

  IF_STMT,
  IF_ELSE_STMT,
  SWITCH_STMT,

  WHILE_STMT,
  DO_WHILE_STMT,
  FOR_STMT,

  GOTO_STMT,
  CONTINUE_STMT,
  BREAK_STMT,
  RETURN_STMT,
  RETURN_EXPR_STMT,

  FUNC_ENTRY,
  FUNC_EXIT,

  FUNCTION_BODY,
  TRANSLATION_UNIT,

} Production;

extern const char* production_names[];

typedef struct ExprNode ExprNode;

typedef struct TreeNode{
  ExprNode* expr_node;
  Production production;
  int num_of_children;
  struct TreeNode* parent;
  struct TreeNode** children;
} TreeNode;

typedef struct Tree{
  Stack stack;
  TreeNode* root;
} Tree;

extern TreeNode* TreeNodeCreateEmpty();
extern void TreeNodeDrop(TreeNode*);
extern void TreeNodeDump(TreeNode*);

extern Tree* TreeCreateEmpty();
extern void TreeDrop(Tree*);
extern void TreeDump(Tree*);

extern TreeNode* TreeInsertNode(Tree* tree, Production production, int num_of_children);

#endif