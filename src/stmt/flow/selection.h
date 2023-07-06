#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "../stmt.h"

// control expression for selection and iteration statements
// supposed to act as a statement - statement stack remains valid
void ControlExpression(void);

void CaseLabel(void);
void DefaultLabel(void);

void IfOpen(void);
void ElseOpen(void);
void SwitchOpen(void);

void IfStmt(void);
void IfElseStmt(void);
void SwitchStmt(void);

#endif