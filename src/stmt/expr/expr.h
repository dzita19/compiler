#ifndef _EXPR_H_
#define _EXPR_H_

#include "../stmt.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum ExprKind{
  LVALUE,
  RVALUE,
  FUNC_DESIGNATOR,
  NUM_LITERAL,
  STR_LITERAL,
  CASE_LABEL,
} ExprKind;

typedef struct LogicNode{
  int x;
} LogicNode;

typedef struct ExprNode{
  ExprKind kind;
  Struct* type;
  Obj* obj_ref; // not owned - carries info about object addressed by lvalue expressions (in case of identifier primary)
  int address;
  LogicNode* logic;
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

void SubexprMultiplyByConst  (TreeNode*, int index, int value);
void ExprDivideByConst       (TreeNode*, int value);
TreeNode* ExprToPointer      (TreeNode*);

void SubexprImplCast         (TreeNode*, int index, Struct* type);

void CommaExprOpen();
void CommaExpr();
void FullExpr();      // fits comma separated list into one expression (doesn't count the expression for statement stack)

#endif