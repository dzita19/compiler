#ifndef _POSTFIX_H_
#define _POSTFIX_H_

#include "expr.h"

void ArrayRefExpr(void);
void FunctionCallExpr(void); // WARNING!!!!!!!!
void FieldRefExpr(void);
void PtrRefExpr(void);
void IncDecExpr(Production production);

void FunctionArgsOpen(void);
void FunctionArgsClose(void);
void FunctionArg(void);

void CompoundLiteral(void);

#endif