#ifndef _EXPR_H_
#define _EXPR_H_

#include "stmt/stmt.h"
#include "stmt/fold.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum ExprKind{
  LVALUE,
  RVALUE,
  ADDRESS_OF,
  
  NUM_LITERAL,
  STR_LITERAL,

  BASIC_LABEL,
  CASE_LABEL,
  DEFAULT_LABEL,

  FUNC_DEFINITION,
} ExprKind;

typedef struct LogicNode LogicNode;

typedef struct ExprNode{
  ExprKind kind;
  Struct* type;
  Obj* obj_ref; // not owned - carries info about object addressed by
    // lvalue expressions (in case of identifier primary - MAYBE or address-of)
  int string_ref;
  int address;
} ExprNode;

ExprNode* ExprNodeCreateEmpty();
void ExprNodeDump(ExprNode*);
void ExprNodeDrop(ExprNode*);

int  IsNullPointer(ExprNode*);

int  CheckSubexprValidity    (TreeNode*, int count);
void InsertConstant          (int value);

void ConvertChildToArithmetic(TreeNode*, int index);
void ConvertChildToLogic     (TreeNode*, int index);
void ConvertChildToPointer   (TreeNode*, int index);

void ExprDivideByConst       (TreeNode*, Struct* type, int value);
void SubexprMultiplyByConst  (TreeNode*, int index, int value);
void SubexprImplCast         (TreeNode*, int index, Struct* type);

void VoidExpr(void);
void CommaExprOpen(void);
void CommaExpr(void);
void FullExpr(void);      // fits comma separated list into one expression (doesn't count the expression for statement stack)

#endif