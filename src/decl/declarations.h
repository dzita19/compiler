#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_

#include "symtab/symtab.h"
#include "symtab/scope.h"
#include "symtab/obj.h"
#include "symtab/struct.h"

#include "util/memory_safety.h"
#include "util/linked_list.h"
#include "util/stack.h"
#include "util/queue.h"
#include "util/logger.h"

#include "gen/abi.h"

extern Symtab* symtab;
extern uint8_t semantic_errors;

extern Stack typedef_stack;
// stack(Obj*)
  // open:  tag def open, function param open
  // close: tag def close,  function param close
  // owner: symtab

extern Stack type_stack;
// stack(TypeFrame*)
  // open:   initial, function param open
  // close:           function param close
  // update:          storage spec's, type spec's, type qual's
  // clean:           declaration, param declaration
  // owner: declarations

extern Stack indirection_stack;
// stack(list(Indirection))
  // open:  initial, function param open
  // close:          function param close
  // add:            ptr, type qual's, direct (abstract) declarators
  // clean:          full declarator, param declaration
  // owner: declarations

extern Stack parameter_stack;
// stack(list(Struct*))
  // open:   function param open
  // close:  function param close
  // remove: declarator (in accordance with indirection stack)
  // add:    param declaration (?) - maybe it's deducible from typedef stack
  // owner:  declarations

extern Stack name_stack;
// stack(NameFrame)
  // open:   initial, function param open,  tag def open
  // close:           function param close, tag def close
  // update:          identifiers
  // owner: declarations


extern Stack initializer_stack; // Stack(InitFrame*)

extern Stack const_expr_stack; // Stack(ConstExpr*)

extern LinkedList static_obj_list; // LinkedList(Obj*)

extern ArgPass declaration_arg_pass; // to allocate memory for function parameters

extern uint8_t ellipsis;
extern uint8_t full_decl_specifiers; // 0 if not, 1 if is. when 0, qualifiers are added to type frame, else to indirections
extern uint8_t current_qualifiers;
extern uint8_t current_function_level;
extern int32_t current_enum_constant;

extern uint8_t block_level;
extern Obj*    current_function_body;
extern int32_t fdef_counter;  // used to know when to open a param scope
extern uint8_t param_scope_open;
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
} TypeFrame;

TypeFrame*  TypeFrameCreateEmpty();
void        TypeFrameDrop (TypeFrame*);
void        TypeFrameClear(TypeFrame*);

typedef struct NameFrame{
  char* name;
  int   tag_type;
} NameFrame;

NameFrame*  NameFrameCreateEmpty();
void        NameFrameDrop (NameFrame*);
void        NameFrameClear(NameFrame*);

typedef enum ConstExprType{
  CONST_EXPR_ARITHMETIC = 1 << 0,
  CONST_EXPR_ADDRESS    = 1 << 1,
  CONST_EXPR_STRING     = 1 << 2,
} ConstExprType;

typedef struct ConstExpr{
  Obj* obj_ref;    // if targets address of an obj
  int string_ref; // if targets address of a string
  int value;
  ConstExprType type;
} ConstExpr;

ConstExpr* ConstExprCreateEmpty();
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
  int offset;
  int parent_offset;
} InitFrame;

InitFrame* InitFrameCreateEmpty(void);
void       InitFrameDrop(InitFrame*);

void StaticObjListDump(void);

void declarations_init(void);
void declarations_free(void);

extern Queue identifier_queue; // communication between lexer and parser
void identifier(const char*);

#endif