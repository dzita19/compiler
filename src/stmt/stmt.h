#ifndef _STMT_H_
#define _STMT_H_

#include "tree.h"

#include "util/stack.h"
#include "util/vector.h"

#include "symtab/symtab.h"
#include "symtab/scope.h"
#include "symtab/obj.h"
#include "symtab/struct.h"

#include "decl/declarations.h"

extern Tree*   tree;
extern Vector* string_table;

extern Stack function_call_stack; // Stack(int) - counts num of args per nested function call
extern Stack typename_stack;      // for type referencing in expressions - sizeof expressions !!!
extern Stack comma_expr_stack;    // Stack(int) - counts num of exprs per nested comma list
extern Stack statement_stack;     // Stack(int) - counts num of statements per nested block 
  // (initially open for translation unit)

extern Stack switch_stack;        // Stack(LinkedList(int)) - case expressions per nested stack

extern int   loop_count;
extern int   switch_count;

void stmt_init();
void stmt_free();

void StringTabDump();

void BlockOpen();
void BlockClose();

void FuncBodyOpen();
void FuncBodyClose();

void Statement();
void UnifyStatements(int);

void ExpressionStmt();
void EmptyStmt();

void NonprototypeRedeclaration();
void NotFunctionDefinition();
void TranslationUnit();

#endif