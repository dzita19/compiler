#ifndef _INDIRECTIONS_H_
#define _INDIRECTIONS_H_

#include "declarations.h"

void NestedDeclarator();
void ArrayLengthDeclarator();
void ArrayVariableDeclarator();
void FunctionDeclarator();

void PointerOpen();
void PointerQualifierOpen();
void Pointer();
void PointerQualifier();

void FunctionParamsOpen();
void FunctionParamsClose();

void Ellipsis(); // empty

#endif