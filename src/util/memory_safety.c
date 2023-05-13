#include "memory_safety.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAB_LENGTH 12
#define PRINT_REPORT(symbol_name, symbol_alloc, symbol_free)\
  printf("--" #symbol_name); \
  for(int i = 0; i < 16 - strlen(#symbol_name); i++) printf(" "); \
  printf("allocated = %4d, freed = %4d;", symbol_alloc, symbol_free);\
  if(symbol_alloc > symbol_free) { \
    printf(" <-- WARNING\n");\
  } \
  else printf("\n")

// symtab
int symtab_alloc      = 0;
int symtab_free       = 0;
int scope_alloc       = 0;
int scope_free        = 0;
int obj_alloc         = 0;
int obj_free          = 0;
int struct_alloc      = 0;
int struct_free       = 0;
int static_val_alloc  = 0;
int static_val_free   = 0;

// util
int linked_list_alloc = 0;
int linked_list_free  = 0;
int node_alloc        = 0;
int node_free         = 0;
int string_alloc      = 0;
int string_free       = 0;
int vector_alloc      = 0;
int vector_free       = 0;

// declarations
int type_frame_alloc  = 0;
int type_frame_free   = 0;
int name_frame_alloc  = 0;
int name_frame_free   = 0;
int const_expr_alloc  = 0;
int const_expr_free   = 0;
int init_frame_alloc  = 0;
int init_frame_free   = 0;

// statements
int tree_node_alloc   = 0;
int tree_node_free    = 0;
int tree_alloc        = 0;
int tree_free         = 0;
int numlit_alloc      = 0;
int numlit_free       = 0;
int expr_node_alloc   = 0;
int expr_node_free    = 0;
int logic_node_alloc  = 0;
int logic_node_free   = 0;

// generating
int arg_pass_alloc    = 0;
int arg_pass_free     = 0;

char* StringDuplicate(const char* str){
  char* string = strdup(str); 
  string_alloc++;

  return string;
}

char* StringAllocate(int size){
  char* string = malloc(sizeof(char) * size);
  string_alloc++;

  return string;
}

void StringDrop(const char* string){
  free((void*)string);
  string_free++;
}

void memory_safety_report(){
  printf("Memory safety report: [\n");
  printf("-Symtab: [\n");
  PRINT_REPORT(Symtab,      symtab_alloc,       symtab_free);
  PRINT_REPORT(Scope,       scope_alloc,        scope_free);
  PRINT_REPORT(Obj,         obj_alloc,          obj_free);
  PRINT_REPORT(Struct,      struct_alloc,       struct_free);
  PRINT_REPORT(StaticVal,   static_val_alloc,   static_val_free);
  printf("-]\n");
  printf("-Utility: [\n");
  PRINT_REPORT(LinkedList,  linked_list_alloc,  linked_list_free);
  PRINT_REPORT(Node,        node_alloc,         node_free);
  PRINT_REPORT(String,      string_alloc,       string_free);
  printf("-]\n");
  printf("-Declarations: [\n");
  PRINT_REPORT(TypeFrame,   type_frame_alloc,   type_frame_free);
  PRINT_REPORT(NameFrame,   name_frame_alloc,   name_frame_free);
  PRINT_REPORT(InitFrame,   init_frame_alloc,   init_frame_free);
  PRINT_REPORT(ConstExpr,   const_expr_alloc,   const_expr_free);
  printf("-]\n");
  printf("-Statements: [\n");
  PRINT_REPORT(TreeNode,    tree_node_alloc,    tree_node_free);
  PRINT_REPORT(Tree,        tree_alloc,         tree_free);
  PRINT_REPORT(Numlit,      numlit_alloc,       numlit_free);
  PRINT_REPORT(ExprNode,    expr_node_alloc,    expr_node_free);
  PRINT_REPORT(LogicNode,   logic_node_alloc,   logic_node_free);
  printf("-]\n");
  printf("-Generating: [\n");
  PRINT_REPORT(ArgPass,     arg_pass_alloc,     arg_pass_free);
  printf("-]\n");
  printf("]\n");
}