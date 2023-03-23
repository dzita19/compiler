#ifndef _PREFIX_H_
#define _PREFIX_H_

#include "expr.h"

void DerefExpr();
void UnaryExpr(Production production);
void AddressExpr();
void BitNegExpr();
void LogNegExpr();
void SizeofExpr();
void SizeofTypeExpr();

void CastExpr();

#endif