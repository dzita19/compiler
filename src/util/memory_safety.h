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
extern int string_alloc;
extern int string_free;
extern int vector_alloc;
extern int vector_free;

// declarations
extern int type_frame_alloc;
extern int type_frame_free;
extern int name_frame_alloc;
extern int name_frame_free;
extern int const_expr_alloc;
extern int const_expr_free;

// statements
extern int tree_node_alloc;
extern int tree_node_free;
extern int tree_alloc;
extern int tree_free;
extern int numlit_alloc;
extern int numlit_free;
extern int expr_node_alloc;
extern int expr_node_free;
extern int logic_node_alloc;
extern int logic_node_free;

extern char* StringDuplicate();
extern char* StringAllocate(int size);
extern void  StringDrop(const char*);

extern void memory_safety_report();

#endif