#ifndef _MEMORY_SAFETY_
#define _MEMORY_SAFETY_

// symtab
extern int obj_alloc;
extern int obj_free;
extern int scope_alloc;
extern int scope_free;
extern int struct_alloc;
extern int struct_free;
extern int symtab_alloc;
extern int symtab_free;

// util
extern int linked_list_alloc;
extern int linked_list_free;
extern int node_alloc;
extern int node_free;
extern int stack_alloc;
extern int stack_free;
extern int queue_alloc;
extern int queue_free;

extern void memory_safety_report();

#endif