#include "declarations.h"

#include <stdint.h>
#include <stdlib.h>

Symtab* symtab                  = 0;
int     semantic_errors         = 0;

Stack   typedef_stack           = (Stack){ 0 }; 
Stack   type_stack              = (Stack){ 0 };
Stack   indirection_stack       = (Stack){ 0 };
Stack   parameter_stack         = (Stack){ 0 };
Stack   name_stack              = (Stack){ 0 };

Stack   initializer_stack       = (Stack){ 0 };
Stack   const_expr_stack        = (Stack){ 0 };

LinkedList static_obj_list      = (LinkedList){ 0, 0 };
LinkedList label_name_list      = (LinkedList){ 0, 0 };
LinkedList global_name_list     = (LinkedList){ 0, 0 };
LinkedList extern_name_list     = (LinkedList){ 0, 0 };

CallFrame param_frame           = (CallFrame){ 0, -2 * POINTER_SIZE };

uint8_t ellipsis                = 0;
uint8_t current_qualifiers      = 0;
uint8_t current_function_level  = 0;
int32_t current_enum_constant   = 0;
int32_t initializer_expression  = 0;

uint8_t block_level             = 0;
Obj*    latest_function_decl    = 0;
Obj*    current_function_body   = 0;
Stack   param_scope_stack       = (Stack){ 0 };
Scope*  func_prototype_scope    = 0;
uint8_t nonprototype_redecl     = 0;

Obj*    current_obj_definition  = 0;
int32_t current_static_counter  = 0;
Stack   stack_frame_stack       = (Stack){ 0 };


TypeFrame* TypeFrameCreateEmpty(void){
  TypeFrame* type_frame = malloc(sizeof(TypeFrame));
  type_frame->current_type         = 0;
  type_frame->storage_specifier    = 0;
  type_frame->type_specifiers      = 0;
  type_frame->type_qualifiers      = 0;
  type_frame->full_decl_specifiers = 0;
  type_frame->identifier_expected  = 0;

  type_frame_alloc++;

  return type_frame;
}

void TypeFrameDrop(TypeFrame* type_frame){
  free(type_frame);

  type_frame_free++;
}

void TypeFrameClear(TypeFrame* type_frame){
  type_frame->current_type         = 0;
  type_frame->storage_specifier    = 0;
  type_frame->type_specifiers      = 0;
  type_frame->type_qualifiers      = 0;
  type_frame->full_decl_specifiers = 0;
  type_frame->identifier_expected  = 0;
}

NameFrame* NameFrameCreateEmpty(){
  NameFrame* name_frame = malloc(sizeof(NameFrame));
  name_frame->name      = 0;
  name_frame->tag_type  = TAG_NONE;

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
  name_frame->name     = 0;
  name_frame->tag_type = TAG_NONE;
}

InitFrame* InitFrameCreateEmpty(void){
  InitFrame* init_frame = malloc(sizeof(InitFrame));
  init_frame->kind   = INIT_ERROR;
  init_frame->type   = 0;
  init_frame->field  = 0;
  init_frame->index  = 0;
  // init_frame->offset = 0;
  // init_frame->parent_offset = 0;

  init_frame_alloc++;

  return init_frame;
}

void InitFrameDrop(InitFrame* init_frame){
  free(init_frame);

  init_frame_free++;
}

ConstExpr* ConstExprCreateEmpty(void){
  ConstExpr* const_expr = malloc(sizeof(ConstExpr));
  const_expr->obj_ref     = 0;
  const_expr->string_ref  = 0;
  const_expr->value       = 0;
  const_expr->kind        = VAL_ERROR;
  const_expr->type        = 0;

  const_expr_alloc++;

  return const_expr;
}

void ConstExprDrop(ConstExpr* const_expr){
  free(const_expr);

  const_expr_free++;
}

#include <stdio.h>
#include "../symtab/static_val.h"

void StaticObjListDump(void){
  printf("Static objects list: [\n");
  for(Node* node = static_obj_list.first; node; node = node->next){
    Obj* obj = node->info;
    // with linkage
    if((obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE){
      printf(" Obj name: %s [\n", obj->name);
    }
    // with no linkage
    else{
      printf(" Obj offset: %d [\n", obj->address);
    }
    for(Node* val = obj->init_vals->first; val; val = val->next){
      printf(" -");
      StaticValDump(val->info);
      printf("\n");
    }
    printf(" ]\n");
  }
  printf("]\n");
}

void LabelNameListDump(void){
  printf("Label names list: [\n");
  for(Node* node = label_name_list.first; node; node = node->next){
    char* name = node->info;
    printf(" Obj name: %s\n", name);
  }
  printf("]\n");
}

void GlobalNameListDump(void){
  printf("Global names list: [\n");
  for(Node* node = global_name_list.first; node; node = node->next){
    char* name = node->info;
    printf(" Obj name: %s\n", name);
  }
  printf("]\n");
}

void ExternNameListDump(void){
  printf("Extern names list: [\n");
  for(Node* node = extern_name_list.first; node; node = node->next){
    char* name = node->info;
    printf(" Obj name: %s\n", name);
  }
  printf("]\n");
}

void declarations_init(void){
  symtab = SymtabCreateEmpty();
  SymtabOpenScope(symtab, SCOPE_FILE);

  StackPush(&type_stack, TypeFrameCreateEmpty());

  StackPush(&indirection_stack, LinkedListCreateEmpty());

  StackPush(&name_stack, NameFrameCreateEmpty());

  StackPush(&stack_frame_stack, 0);
}

void declarations_free(void){
  //SymtabCloseScope(symtab); - ADD IT WHEN IT MAKES SENSE

  SymtabDrop(symtab);

  TypeFrameDrop(StackPop(&type_stack));

  LinkedListDrop(StackPop(&indirection_stack));

  NameFrameDrop(StackPop(&name_stack));

  StackPop(&stack_frame_stack);

  LinkedListDelete(&static_obj_list);
  
  for(Node* node = label_name_list.first; node; node = node->next){
    StringDrop((char*)node->info);
  }
  LinkedListDelete(&label_name_list);

  for(Node* node = global_name_list.first; node; node = node->next){
    StringDrop((char*)node->info);
  }
  LinkedListDelete(&global_name_list);

  for(Node* node = extern_name_list.first; node; node = node->next){
    StringDrop((char*)node->info);
  }
  LinkedListDelete(&extern_name_list);
}

Queue identifier_queue = { 0, 0 };

void identifier(const char* name){
  QueueInsert(&identifier_queue, StringDuplicate(name));
}