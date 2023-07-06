#ifndef _POSTFIX_H_
#define _POSTFIX_H_

#include "expr.h"

void ArrayRefExpr();
void FunctionCallExpr(); // WARNING!!!!!!!!
void FieldRefExpr();
void PtrRefExpr();
void IncDecExpr(Production production);

void FunctionArgsOpen();
void FunctionArgsClose();
void FunctionArg();

#endif