#ifndef _POSTFIX_H_
#define _POSTFIX_H_

#include "expr.h"

void ArrayRefExpr();
void FunctionCallExpr();
void FieldRefExpr(const char* member_name);
void PtrRefExpr(const char* member_name);
void IncDecExpr(Production production);

void FunctionArgsOpen();
void FunctionArgsClose();
void FunctionArg();

#endif