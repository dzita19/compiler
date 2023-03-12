#include "memory_safety.h"

#include <stdio.h>

// symtab
int symtab_alloc       = 0;
int symtab_free        = 0;
int scope_alloc        = 0;
int scope_free         = 0;
int obj_alloc          = 0;
int obj_free           = 0;
int struct_alloc       = 0;
int struct_free        = 0;

// util
int linked_list_alloc  = 0;
int linked_list_free   = 0;
int node_alloc         = 0;
int node_free          = 0;
int stack_alloc        = 0;
int stack_free         = 0;
int queue_alloc        = 0;
int queue_free         = 0;

void memory_safety_report(){
  printf("Memory safety report: [");
  printf("-Symtab: [\n");
  printf("--Symtab      allocated = %4d, freed = %4d;\n", symtab_alloc, symtab_free);
  printf("--Scope       allocated = %4d, freed = %4d;\n", scope_alloc, scope_free);
  printf("--Obj         allocated = %4d, freed = %4d;\n", obj_alloc, obj_free);
  printf("--Struct      allocated = %4d, freed = %4d;\n", struct_alloc, struct_free);
  printf("-]\n");
  printf("-Utility: [\n");
  printf("--Linked list allocated = %4d, freed = %4d;\n", linked_list_alloc, linked_list_free);
  printf("--Node        allocated = %4d, freed = %4d;\n", node_alloc, node_free);
  printf("--Stack       allocated = %4d, freed = %4d;\n", stack_alloc, stack_free);
  printf("--Queue       allocated = %4d, freed = %4d;\n", queue_alloc, queue_free);
  printf("-]\n");
  printf("]\n");
}