#ifndef _TREE_H_
#define _TREE_H_

#include "util/memory_safety.h"
#include "util/stack.h"

typedef enum Production{
  VOID_EXPR,

  // VALUE_PRIMARY,
  ADDRESS_PRIMARY,
  CONSTANT_PRIMARY,
  STRING_PRIMARY,

  FIELD_REF_EXPR,
  FUNCTION_CALL_EXPR,
  POST_INC_EXPR,
  POST_DEC_EXPR,
  COMPOUND_LITERAL,

  PRE_INC_EXPR,
  PRE_DEC_EXPR,
  DEREF_EXPR,
  UNARY_PLUS_EXPR,
  UNARY_MINUS_EXPR,
  BIT_NOT_EXPR,
  LOG_NOT_EXPR,

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
  RELA_NQ_EXPR,

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

  LABEL_STMT,
  CASE_STMT,
  DEFAULT_STMT,

  INITIALIZATION,
  FOR_DECL,
  COMPOUND_STMT,

  INITIALIZER_LOOP,

  EXPRESSION_STMT,
  EMPTY_STMT,

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

  INLINE_ASM_STMT,

  FUNC_PROLOGUE,
  FUNC_EPILOGUE,

  FUNCTION_BODY,
  TRANSLATION_UNIT,

} Production;

#define PRODUCTION_EXPR     0
#define PRODUCTION_STMT     1

extern const char* production_names[];
extern const int   production_kind[];

typedef struct ExprNode  ExprNode;
typedef struct LogicNode LogicNode;
typedef struct MemAlloc  MemAlloc;

typedef struct TreeNode{
  int id;
  int label; // initialized to 0; set to -1 if node is a branch target; later set real value;
  Production production;
  int num_of_children;
  struct TreeNode* parent;
  struct TreeNode** children;
  ExprNode* expr_node;
  LogicNode* logic_node;
  MemAlloc* mem_alloc;
} TreeNode;

typedef struct Tree{
  Stack stack;
} Tree;

extern TreeNode* TreeNodeCreateEmpty();
extern void TreeNodeDrop(TreeNode*);
extern void TreeNodeDump(TreeNode*);

extern Tree* TreeCreateEmpty();
extern void TreeDrop(Tree*);
extern void TreeDump(Tree*);

extern TreeNode* TreeInsertNode(Tree* tree, Production production, int num_of_children);

#endif