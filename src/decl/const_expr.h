#ifndef _CONST_EXPR_H_
#define _CONST_EXPR_H_

#include "declarations.h"

#include "stmt/stmt.h"
#include "stmt/expr/expr.h"

void      ConstExpression();
long      ConstArithmeticExprProcessor(TreeNode* node);
ConstExpr ConstAddressExprProcessor(TreeNode* node);

#endif