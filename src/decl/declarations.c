#include "declarations.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "util/stack.h"
#include "util/linked_list.h"

#include "symtab/symtab.h"

Symtab* symtab = 0;

Stack typedef_stack = { 0 };
Stack type_stack = { 0 };
Stack indirection_stack = { 0 };
Stack parameter_stack = { 0 };
Stack name_stack = { 0 };

uint8_t current_qualifiers = 0;
uint8_t current_function_level = 0;
int32_t current_enum_constant = 0;

TypeFrame* TypeFrameCreateEmpty(){
  TypeFrame* type_frame = malloc(sizeof(TypeFrame));
  type_frame->current_type = 0;
  type_frame->storage_specifier = 0;
  type_frame->type_specifiers = 0;
  type_frame->type_qualifiers = 0;

  return type_frame;
}

void TypeFrameClear(TypeFrame* type_frame){
  type_frame->current_type = 0;
  type_frame->storage_specifier = 0;
  type_frame->type_specifiers = 0;
  type_frame->type_qualifiers = 0;
}

NameFrame* NameFrameCreateEmpty(){
  NameFrame* name_frame = malloc(sizeof(NameFrame));
  name_frame->name = 0;
  name_frame->type = TAG_NONE;

  return name_frame;
}

void NameFrameClear(NameFrame* name_frame){
  name_frame->name = 0;
  name_frame->type = TAG_NONE;
}

void declarations_init(){
  symtab = SymtabCreateEmpty();
  SymtabOpenScope(symtab, SCOPE_FILE);

  StackPush(&type_stack, TypeFrameCreateEmpty());

  StackPush(&indirection_stack, LinkedListCreateEmpty());

  StackPush(&name_stack, NameFrameCreateEmpty());
}