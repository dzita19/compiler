#include "stmt.h"

#include "decl/declarations.h"

#include "expr/expr.h"

#include <stdio.h>

Tree*   tree         = 0;
Vector* string_table = 0;

Stack function_call_stack = { 0 }; // Stack(int) - counts num of args per nested function call
Stack typename_stack      = { 0 }; // for type referencing in expressions - sizeof expressions !!!
Stack comma_expr_stack    = { 0 };
Stack statement_stack     = { 0 };
Stack switch_stack        = { 0 };

int   loop_count    = 0;
int   switch_count  = 0;

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

void StringTabDump(){
  printf("String table: [\n");
  for(int i = 0; i < string_table->size; i++){
    printf(" \"%s\"\n", (char*)VectorGet(string_table, i));
  }
  printf("]\n");
}

void BlockOpen(){
  StackPush(&statement_stack, 0);

  StackPush(&stack_frame_stack, stack_frame_stack.top->info);

  SymtabOpenScope(symtab, SCOPE_BLOCK);
  block_level++;
}

void BlockClose(){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  TreeNode* node = TreeInsertNode(tree, COMPOUND_STMT, num_of_stmts);

  StackPop(&stack_frame_stack);

  Statement(); // add this compound statement as a statement in enclosing block

  SymtabCloseScope(symtab);
  block_level--;
}

static void CheckFuncPrototyped(void){
  // if(current_function_body->type->attributes & NONPROTOTYPE) return;

  int named_parameters = 0;
  for(Node* node = symtab->current_scope->objs.first; node; node = node->next){
    Obj* param = node->info;
    if(param->kind == OBJ_VAR) named_parameters++;
  }

  int total_parameters = 0;
  for(Node* node = current_function_body->type->parameters.first; node; node = node->next){
    Struct* param = node->info;
    if(param->type == TYPE_INCOMPLETE) {
      ReportError("Function parameter cannot have incomplete type when body is present.");
    }
    total_parameters++;
  }

  if(total_parameters > named_parameters) {
    ReportError("Unnamed prototyped parameters not allowed when body is present.");
  }
}

static void CheckFuncNonprototype(void){
  for(Node* node = symtab->current_scope->objs.first; node; node = node->next){
    Obj* param = node->info;
    if(param->type == 0) {
      ReportError("Undefined parameter in nonprototype function.");
    }
  }
}

static void CheckFuncCorrectness(void){
  if(current_function_body->type->attributes & NONPROTOTYPE_FUNCTION) 
    CheckFuncNonprototype();
  else
    CheckFuncPrototyped();
}

void FuncBodyOpen(){
  nonprototype_redecl = 0;
  TypeFrameClear(StackPeek(&type_stack)); // we can't recognize declaration around function definition

  if(current_function_body != 0){
    CheckFuncCorrectness();
    if((current_function_body->specifier & DEFINITION_FETCH) == DEFINED){
      ReportError("Function body already defined.");
    }
  }

  StackPush(&statement_stack, 0);

  SymtabOpenScope(symtab, SCOPE_BLOCK);
  block_level++;

  TreeInsertNode(tree, FUNC_ENTRY, 0);
  Statement();
}

void FuncBodyClose(){
  TreeInsertNode(tree, FUNC_EXIT, 0);
  Statement();

  ArgPassClear(&declaration_arg_pass);

  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  TreeNode* node = TreeInsertNode(tree, FUNCTION_BODY, num_of_stmts);

  Statement(); // add this compound statement as a statement in enclosing block - TO TRANSLATION UNIT!!!

  SymtabCloseScope(symtab); // remove function body block scope
  SymtabCloseScope(symtab); // remove function prototype scope

  if(current_function_body){
    current_function_body->specifier &= DEFINITION_CLEAR;
    current_function_body->specifier |= DEFINED;
    current_function_body = 0;
  }
  // current_stack_counter = 0;
  stack_frame_stack.top->info = 0;

  block_level--;
}

void Statement(){
  statement_stack.top->info++;
}

void UnifyStatements(int num){
  statement_stack.top->info -= num;
}

void ExpressionStmt(){
  TreeNode* node = TreeInsertNode(tree, EXPRESSION_STMT, 1);

  Statement();
}

void EmptyStmt(){
  TreeInsertNode(tree, EMPTY_STMT, 0);

  Statement();
}

void TranslationUnit(){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  TreeNode* node = TreeInsertNode(tree, TRANSLATION_UNIT, num_of_stmts);
}