#include "stmt.h"

#include "decl/declarations.h"

#include "expr/expr.h"

Tree* tree = 0;
Vector* string_table = 0;

Stack function_call_stack = { 0 }; // Stack(int) - counts num of args per nested function call
Stack typename_stack = { 0 }; // for type referencing in expressions - sizeof expressions !!!
Stack comma_expr_stack = { 0 };
Stack statement_stack = { 0 };

void stmt_init(){
  tree = TreeCreateEmpty();
  string_table = VectorInit();

  StackPush(&statement_stack, 0);
}

void stmt_free(){
  TreeDrop(tree);

  for(int i = 0; i < string_table->size; i++){
    StringDrop(string_table->content[i]);
  }
  VectorDrop(string_table);
}

void BlockOpen(){
  /*if(block_level == 0){
    SymtabInsertScope(symtab, current_param_scope);
    current_param_scope = 0;
    TypeFrameClear(StackPeek(&type_stack)); // we can't recognize declaration around function definition
  }*/

  StackPush(&statement_stack, 0);

  SymtabOpenScope(symtab, SCOPE_BLOCK);
  block_level++;
}

void BlockClose(){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  TreeNode* node = TreeInsertNode(tree, COMPOUND_STMT, num_of_stmts);

  statement_stack.top->info++; // add this compound statement as a statement in enclosing block

  SymtabCloseScope(symtab);
  block_level--;
}

void FuncBodyOpen(){
  //if(block_level == 0){
  SymtabInsertScope(symtab, current_param_scope);
  current_param_scope = 0;
  TypeFrameClear(StackPeek(&type_stack)); // we can't recognize declaration around function definition
  //}

  StackPush(&statement_stack, 0);

  SymtabOpenScope(symtab, SCOPE_BLOCK);
  block_level++;
}

void FuncBodyClose(){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  TreeNode* node = TreeInsertNode(tree, FUNCTION_BODY, num_of_stmts);

  statement_stack.top->info++; // add this compound statement as a statement in enclosing block

  SymtabCloseScope(symtab);
  block_level--;
}

void ExpressionStmt(){
  TreeInsertNode(tree, EXPRESSION_STMT, 1);

  statement_stack.top->info++;
}

void EmptyStmt(){
  TreeInsertNode(tree, EMPTY_STMT, 0);

  statement_stack.top->info++;
}

void FunctionDefinition(){
  SymtabCloseScope(symtab);
  current_function_body->specifier &= DEFINITION_CLEAR;
  current_function_body->specifier |= DEFINED;
  current_function_body = 0;
  current_stack_counter = 0;
}

void NotFunctionDefinition(){
  if(current_param_scope) ScopeDrop(current_param_scope);
  current_param_scope = 0;
}

void TranslationUnit(){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  TreeNode* node = TreeInsertNode(tree, TRANSLATION_UNIT, num_of_stmts);
}