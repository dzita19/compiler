#ifndef _JUMP_H_
#define _JUMP_H_

#include "../stmt.h"

void Label(void);

void GotoStmt(void);
void ContinueStmt(void);
void BreakStmt(void);
void ReturnStmt(void);
void ReturnExprStmt(void);

#endif