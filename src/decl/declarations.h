#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_

#include "symtab/symtab.h"
#include "symtab/scope.h"
#include "symtab/obj.h"
#include "symtab/static_val.h"
#include "symtab/struct.h"

#include "util/memory_safety.h"
#include "util/linked_list.h"
#include "util/stack.h"
#include "util/queue.h"
#include "util/logger.h"

#include "gen/abi.h"

extern Symtab* symtab;
extern int     semantic_errors;

extern Stack typedef_stack;
extern Stack type_stack;
extern Stack indirection_stack;
extern Stack parameter_stack;
extern Stack name_stack;

extern Stack initializer_stack; // Stack(InitFrame*)
extern Stack const_expr_stack; // Stack(ConstExpr*)

extern LinkedList static_obj_list;  // LinkedList(Obj*)
extern LinkedList label_name_list;  // LinkedList(char*) - list of symbols that generate a label (also functions)
extern LinkedList global_name_list; // LinkedList(char*) - list of symbols that generate global declaration
extern LinkedList extern_name_list; // LinkedList(char*) - list of symbols that generate extern declaration

extern CallFrame param_frame; // to allocate memory for function parameters

extern uint8_t ellipsis;
// extern uint8_t full_decl_specifiers; // 0 if not, 1 if is. when 0, qualifiers are added to type frame, else to indirections
  // important - needs to be reset after typename is recognized (because it is not followed by )
extern uint8_t current_qualifiers;
extern uint8_t current_function_level;
extern int32_t current_enum_constant;

extern uint8_t block_level;
extern Obj*    current_function_body;
extern Obj*    latest_function_decl;
extern Stack   param_scope_stack;
extern Scope*  func_prototype_scope;
extern uint8_t nonprototype_redecl;
  // at beginning of full declaration, fdef and pso are both 0 (and so shall be at the end)
  // pso is set to 1 when pso is 0 and fparam open is reduced (also add new scope)
  // fdef is incremented every time pso is 1 and fparam open is reduced
  // fdef is decremented every time fparam closed is reduced
  // nonprototype redecl is 1 after completing function declarator and before function body entry

extern Obj*    current_obj_definition;
extern int32_t current_static_counter;
extern Stack   stack_frame_stack; // nested stack counter per block

typedef struct TypeFrame{
  Obj* current_type;
  int type_specifiers;
  int storage_specifier;
  int type_qualifiers;
  int full_decl_specifiers;
} TypeFrame;

TypeFrame*  TypeFrameCreateEmpty(void);
void        TypeFrameDrop (TypeFrame*);
void        TypeFrameClear(TypeFrame*);

typedef struct NameFrame{
  char* name;
  int   tag_type;
} NameFrame;

NameFrame*  NameFrameCreateEmpty(void);
void        NameFrameDrop (NameFrame*);
void        NameFrameClear(NameFrame*);

typedef struct ConstExpr{
  Obj* obj_ref;    // if targets address of an obj
  int string_ref; //  if targets address of a string
  int value;
  StaticValKind kind;
  Struct* type;
} ConstExpr;

ConstExpr* ConstExprCreateEmpty(void);
void       ConstExprDrop(ConstExpr*);

typedef enum InitKind{
  INIT_ERROR,
  INIT_SCALAR,
  INIT_ARRAY,
  INIT_FIELDS, // denotes struct and union initializer
} InitKind;

typedef struct InitFrame{
  InitKind kind;
  Struct* type;
  Node* field;       // Node(Obj*)
  int index;
  // int offset;
  // int parent_offset;
} InitFrame;

InitFrame* InitFrameCreateEmpty(void);
void       InitFrameDrop(InitFrame*);

void StaticObjListDump(void);
void LabelNameListDump(void);
void GlobalNameListDump(void);
void ExternNameListDump(void);

void declarations_init(void);
void declarations_free(void);

extern Queue identifier_queue; // communication between lexer and parser
void identifier(const char*);

#endif