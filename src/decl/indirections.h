#ifndef _INDIRECTIONS_H_
#define _INDIRECTIONS_H_

#include "declarations.h"

void NestedDeclarator(void);
void ArrayLengthDeclarator(void);
void ArrayVariableDeclarator(void);
void FunctionDeclarator(void);
void FuncNonprototypeDeclarator(void);

void PointerOpen(void);
void PointerQualifierOpen(void);
void Pointer(void);
void PointerQualifier(void);

void FunctionParamsOpen(void);
void FunctionParamsClose(void);

void TypeOpen(void);
void TypeClose(void);

void Ellipsis(void); // empty

#endif