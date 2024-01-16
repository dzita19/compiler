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
Stack   const_expr_stack        = (Stack){ 0 };

Stack   initializer_stack       = (Stack){ 0 };
Stack   init_attrib_stack       = (Stack){ 0 };
Stack   init_frame_stack        = (Stack){ 0 };
Stack   init_error_stack        = (Stack){ 0 };
Stack   init_size_stack         = (Stack){ 0 };
Stack   obj_definiton_stack     = (Stack){ 0 };

LinkedList static_obj_list      = (LinkedList){ 0, 0 };
LinkedList label_name_list      = (LinkedList){ 0, 0 };
LinkedList global_name_list     = (LinkedList){ 0, 0 };
LinkedList extern_name_list     = (LinkedList){ 0, 0 };

CallFrame param_frame           = (CallFrame){ 0, -2 * POINTER_SIZE };

uint8_t ellipsis                = 0;
uint8_t current_qualifiers      = 0;
uint8_t current_function_level  = 0;
int32_t current_enum_constant   = 0;

uint8_t block_level             = 0;
Obj*    latest_function_decl    = 0;
Obj*    current_function_body   = 0;
Stack   param_scope_stack       = (Stack){ 0 };
Scope*  func_prototype_scope    = 0;
uint8_t nonprototype_redecl     = 0;

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
  init_frame->type   = 0;
  init_frame->field  = 0;
  init_frame->index  = 0;
  init_frame->xopen  = 0;
  // init_frame->offset = 0;
  // init_frame->parent_offset = 0;

  init_frame_alloc++;

  return init_frame;
}

void InitFrameDrop(InitFrame* init_frame){
  free(init_frame);

  init_frame_free++;
}

void InitFrameInitializeWithType(InitFrame* init_frame, Struct* type, int first){
  if(type == 0) return;

  type = StructGetUnqualified(type);

  if(type->type == TYPE_INCOMPLETE) return;
  if(StructIsFunction(type)) return;

  if(StructIsArray(type)){
    init_frame->type  = type;
    init_frame->index = 0;
    init_frame->xopen = first ? INIT_FRAME_FIRST_ACTIVE : INIT_FRAME_ACTIVE;
  }
  else if(StructIsStruct(type)){
    init_frame->type  = type;
    init_frame->field = type->obj->members.first;
    init_frame->xopen = first ? INIT_FRAME_FIRST_ACTIVE : INIT_FRAME_ACTIVE;
  }
  else if(StructIsUnion(type)){
    init_frame->type  = type;
    init_frame->field = type->obj->members.first;
    init_frame->xopen = first ? INIT_FRAME_FIRST_ACTIVE : INIT_FRAME_ACTIVE;
  }
  else if(StructIsScalar(type)){
    init_frame->type  = type;
    init_frame->xopen = first ? INIT_FRAME_FIRST_ACTIVE : INIT_FRAME_ACTIVE;
  }
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

#include "stmt/tree.h"

InitVal* InitValCreateEmpty(){
  InitVal* val = malloc(sizeof(InitVal));
  val->size       = 0;
  val->offset     = 0;
  val->expression = NULL;

  init_val_alloc++;

  return val;
}

void InitValDrop(InitVal* val){
  if(val->expression) TreeNodeDrop(val->expression);
  free(val);

  init_val_free++;
}

extern int dump_indent;

extern void print_indent();

#include "util/vector.h"

#include "stmt/expr/expr.h"

void InitValDump(InitVal* val){
  extern Vector* string_table;

  printf("Offset: %d; Size: %d; ", val->offset, val->size);
  if(val->expression->production == ADDRESS_PRIMARY
      || val->expression->production == COMPOUND_LITERAL){
    Obj* obj_ref = val->expression->expr_node->obj_ref; 
    if((obj_ref->specifier & LINKAGE_FETCH) == LINKAGE_NONE)
      printf("Address of: $unnamed + %d; ", obj_ref->address);
    else
      printf("Address of: %s; ", obj_ref->name);
  }
  else if(val->expression->production == CONSTANT_PRIMARY){
    int value = val->expression->expr_node->address;
    if(value >= 0) printf("Value: %d; ",  +value);
    else           printf("Value: -%d; ", -value);
  }
  else if(val->expression->production == STRING_PRIMARY){
    printf("String: \"%s\"; ", (char*)VectorGet(string_table, val->expression->expr_node->string_ref));
  }
  else printf("Non-constant");
}

void InitValAddToList(InitVal* init_val, LinkedList* list){
  Node* node = list->first;
  while(node){
    InitVal* current_val = node->info;

    int a0 = init_val->offset;
    int a1 = init_val->offset + init_val->size;

    int b0 = current_val->offset;
    int b1 = current_val->offset + current_val->size;

    if((a0 <= b0 && a1 > b0) || (a1 >= b1 && a0 < b0)){
      Node* old = node;
      node = node->next;
      InitValDrop(current_val);
      NodeDrop(LinkedListRemoveFrom(list, old));
    }
    else if(a0 >= b1) node = node->next;
    else if(a1 <= b0) break; 
  }

  Node* new_node = NodeCreateEmpty();
  new_node->info = init_val;

  if(node) LinkedListInsertBefore(list, node, new_node);
  else     LinkedListInsertLast(list, new_node);
}

#include <stdio.h>

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
      InitValDump(val->info);
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