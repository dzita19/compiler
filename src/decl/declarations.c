#include "declarations.h"

#include <stdint.h>
#include <stdlib.h>

Symtab* symtab                  = 0;

Stack typedef_stack             = { 0 };
Stack type_stack                = { 0 };
Stack indirection_stack         = { 0 };
Stack parameter_stack           = { 0 };
Stack name_stack                = { 0 };

uint8_t current_qualifiers      = 0;
uint8_t current_function_level  = 0;
int32_t current_enum_constant   = 0;

uint8_t block_level             = 0;
Obj*    current_function_body   = 0;
Scope*  current_param_scope     = 0;
int32_t current_stack_counter   = 0;
uint8_t fdef_counter            = 0;

Stack   const_expr_stack        = { 0 };

TypeFrame* TypeFrameCreateEmpty(){
  TypeFrame* type_frame = malloc(sizeof(TypeFrame));
  type_frame->current_type = 0;
  type_frame->storage_specifier = 0;
  type_frame->type_specifiers = 0;
  type_frame->type_qualifiers = 0;

  type_frame_alloc++;

  return type_frame;
}

void TypeFrameDrop(TypeFrame* type_frame){
  free(type_frame);

  type_frame_free++;
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
  name_frame->tag_type = TAG_NONE;

  name_frame_alloc++;

  return name_frame;
}

void NameFrameDrop(NameFrame* name_frame){
  if(name_frame->name) {
    StringDrop(name_frame->name);
  }
  free(name_frame);

  name_frame_free++;
}

void NameFrameClear(NameFrame* name_frame){
  if(name_frame->name) {
    StringDrop(name_frame->name);
  }
  name_frame->name = 0;
  name_frame->tag_type = TAG_NONE;
}

ConstExpr* ConstExprCreateEmpty(){
  ConstExpr* const_expr = malloc(sizeof(ConstExpr));
  const_expr->obj_ref = 0;
  const_expr->value = 0;
  const_expr->type = 0;

  const_expr_alloc++;

  return const_expr;
}

void ConstExprDrop(ConstExpr* const_expr){
  free(const_expr);

  const_expr_free++;
}

void declarations_init(){
  symtab = SymtabCreateEmpty();
  SymtabOpenScope(symtab, SCOPE_FILE);

  StackPush(&type_stack, TypeFrameCreateEmpty());

  StackPush(&indirection_stack, LinkedListCreateEmpty());

  StackPush(&name_stack, NameFrameCreateEmpty());
}

void declarations_free(){
  //SymtabCloseScope(symtab); - ADD IT WHEN IT MAKES SENSE

  SymtabDrop(symtab);

  TypeFrameDrop(StackPop(&type_stack));

  LinkedListDrop(StackPop(&indirection_stack));

  NameFrameDrop(StackPop(&name_stack));
}