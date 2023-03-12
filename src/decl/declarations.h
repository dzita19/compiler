#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_

#include "symtab/symtab.h"
#include "symtab/scope.h"
#include "symtab/obj.h"
#include "symtab/struct.h"

extern Symtab* symtab;

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

extern uint8_t current_qualifiers;
extern uint8_t current_function_level;
extern int32_t current_enum_constant;

typedef struct TypeFrame{
  Obj* current_type;
  int type_specifiers;
  int storage_specifier;
  int type_qualifiers;
} TypeFrame;

TypeFrame* TypeFrameCreateEmpty();
void TypeFrameClear(TypeFrame* type_frame);

typedef struct NameFrame{
  char* name;
  TagType type;
} NameFrame;

NameFrame* NameFrameCreateEmpty();
void NameFrameClear(NameFrame* name_frame);

#endif