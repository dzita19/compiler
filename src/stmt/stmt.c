#include "stmt.h"

#include "decl/declarations.h"

#include "expr/expr.h"

#include <stdio.h>
#include <string.h>

Tree*   tree           = 0;
Vector* string_table   = 0;
Scope*  function_scope = 0;    // used for labels inside one function

Stack function_call_stack = { 0 }; // Stack(int) - counts num of args per nested function call
Stack typename_stack      = { 0 }; // for type referencing in expressions - sizeof expressions !!!
Stack comma_expr_stack    = { 0 };
Stack statement_stack     = { 0 };
Stack switch_stack        = { 0 }; // Stack(ExprNode*)

int   loop_count     = 0;
int   switch_count   = 0;

void stmt_init(void){
  tree = TreeCreateEmpty();
  string_table = VectorInit();
  VectorPush(string_table, 0); // first entry is reserved for static objects with no linkage

  StackPush(&statement_stack, 0);
}

void stmt_free(void){
  TreeDrop(tree);

  for(int i = 1; i < string_table->size; i++){  // first entry is reserved for static objects with no linkage
    StringDrop(string_table->content[i]);
  }
  VectorDrop(string_table);
}

void StringTabDump(void){
  printf("String table: [\n");
  for(int i = 1; i < string_table->size; i++){  // first entry is reserved for static objects with no linkage
    printf(" \"%s\"\n", (char*)VectorGet(string_table, i));
  }
  printf("]\n");
}

void BlockOpen(void){
  StackPush(&statement_stack, 0);

  StackPush(&stack_frame_stack, stack_frame_stack.top->info);

  SymtabOpenScope(symtab, SCOPE_BLOCK);
  block_level++;
}

void BlockClose(void){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  // TreeNode* node = 
  TreeInsertNode(tree, COMPOUND_STMT, num_of_stmts);

  if((int)(long)stack_frame_stack.top->info > current_function_body->address){
    current_function_body->address = (int)(long)stack_frame_stack.top->info;
  }
  
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

static void AllocParamsAddress(void){
  // current scope is function prototype scope??????????????
  Obj* return_addr = 0;

  // reserve stack space for return addr
  if(!StructIsScalar(current_function_body->type->parent)
      && !StructIsVoid(current_function_body->type->parent)){
    return_addr = ObjCreateEmpty();
    return_addr->kind = OBJ_VAR;
    return_addr->name = strdup("$return_addr");
    return_addr->specifier = STORAGE_AUTO | LINKAGE_NONE | DEFINED;
    return_addr->type = StructToPtr(current_function_body->type->parent);
    return_addr->address = CallFrameAllocReturnAddr(&param_frame);

    SymtabInsert(symtab, return_addr);
  }

  for(Node* curr_node = symtab->current_scope->objs.first; curr_node; curr_node = curr_node->next){
    Obj* obj_ref = curr_node->info;
    if(obj_ref->kind == OBJ_VAR && obj_ref != return_addr){
      obj_ref->address = CallFrameAllocAddr(&param_frame, obj_ref->type);
    }
  }
}

void FuncBodyOpen(void){
  nonprototype_redecl = 0;
  TypeFrameClear(StackPeek(&type_stack)); // we can't recognize declaration around function definition

  if(current_function_body != 0){
    CheckFuncCorrectness();
    AllocParamsAddress();
    if((current_function_body->specifier & DEFINITION_FETCH) == DEFINED){
      ReportError("Function body already defined.");
    }
  }

  StackPush(&statement_stack, 0);

  function_scope = ScopeCreateEmpty();

  SymtabOpenScope(symtab, SCOPE_BLOCK);
  block_level++;

  // TreeNode* node = 
  TreeInsertNode(tree, FUNC_PROLOGUE, 0);
  Statement();
}

static void CheckLabelsCorrectness(void){
  // currently open scope is function scope - labels
  for(Node* curr_node = symtab->current_scope->objs.first; curr_node; curr_node = curr_node->next){
    Obj* obj_ref = curr_node->info;
    if((obj_ref->specifier & DEFINITION_FETCH) != DEFINED){
      ReportError("Label referenced but never defined.");
    }
  }
}

void FuncBodyClose(void){
  TreeNode* node = TreeInsertNode(tree, FUNC_EPILOGUE, 0);
  Statement();

  CallFrameClear(&param_frame);

  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  node = TreeInsertNode(tree, FUNCTION_BODY, num_of_stmts);
  node->expr_node = ExprNodeCreateEmpty();
  node->expr_node->kind = FUNC_DEFINITION;
  node->expr_node->obj_ref = current_function_body;

  Statement(); // add this compound statement as a statement in enclosing block - TO TRANSLATION UNIT!!!

  SymtabCloseScope(symtab); // remove function body block scope
  SymtabInsertScope(symtab, function_scope);
  CheckLabelsCorrectness();
  SymtabCloseScope(symtab); // remove function scope
  SymtabCloseScope(symtab); // remove function prototype scope

  if(current_function_body){
    // TEST - set address for function obj - address denotes stack frame size (in bytes)
    if((int)(long)stack_frame_stack.top->info > current_function_body->address){
      current_function_body->address = (int)(long)stack_frame_stack.top->info;
    }
    
    // align to FRAME_ALIGNMENT
    current_function_body->address = (current_function_body->address + FRAME_ALIGNMENT - 1) / FRAME_ALIGNMENT * FRAME_ALIGNMENT; 

    current_function_body->specifier &= DEFINITION_CLEAR;
    current_function_body->specifier |= DEFINED;
    current_function_body = 0;
  }
  
  stack_frame_stack.top->info = 0;

  block_level--;
}

void Statement(void){
  statement_stack.top->info++;
}

void UnifyStatements(int num){
  statement_stack.top->info -= (num - 1);
}

void ExpressionStmt(void){
  TreeNode* node = TreeInsertNode(tree, EXPRESSION_STMT, 1);
  Statement();

  if(node->children[0]->expr_node) SubexprImplCast(node, 0, predefined_types_struct + INT32_T);
  if(node->children[0]->expr_node) ConvertChildToArithmetic(node, 0);
}

void EmptyStmt(void){
  // TreeNode* node = 
  TreeInsertNode(tree, EMPTY_STMT, 0);
  Statement();
}

void TranslationUnit(void){
  int num_of_stmts = (int)(long)StackPop(&statement_stack);

  // TreeNode* node = 
  TreeInsertNode(tree, TRANSLATION_UNIT, num_of_stmts);
  
  for(Node* node = symtab->current_scope->objs.first; node; node = node->next){
    Obj* obj = node->info;
    if(obj->kind == OBJ_VAR && StructIsArray(obj->type) && obj->type->attributes == 0){
      ReportError("Array of unspecified size remained undefined.");
    }
  }
}