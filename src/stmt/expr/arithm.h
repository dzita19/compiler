#ifndef _ARITHM_H_
#define _ARITHM_H_

#include "expr.h"

void MulExpr(Production);
void AddExpr();
void SubExpr();

void SimpleAssignExpr(int initializer);
void MulAssignExpr(Production);
void AddAssignExpr();
void SubAssignExpr();

#endif