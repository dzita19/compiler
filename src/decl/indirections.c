#include "indirections.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void NestedDeclarator(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  for(Node* node = current_indirection_frame->last; node; node = node->prev){
    if(node->info == (void*)SEPARATOR_ACTIVE){
      node->info = (void*)SEPARATOR_DISABLED;
    }
    else if(node->info == (void*)SEPARATOR_INACTIVE){
      node->info = (void*)SEPARATOR_ACTIVE;
      break;
    }
  }

}

void ArrayLengthDeclarator(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);
  
  ConstExpr* const_expr = StackPop(&const_expr_stack);
  int array_length = const_expr->value;

  if(const_expr->kind != VAL_ARITHM || !StructIsArithmetic(const_expr->type)) {
    ReportError("Array length must be constant arithmetic value.");
    array_length = 0;
  }
  ConstExprDrop(const_expr);

  Node* node = 0;
  for(node = current_indirection_frame->last; node; node = node->prev){
    if(node->info == (void*)SEPARATOR_ACTIVE) break;
  }
  if(node == 0){
    node = NodeCreateEmpty();
    node->info = (void*)SEPARATOR_ACTIVE;
    LinkedListInsertLast(current_indirection_frame, node);
  }

  Node* array = NodeCreateEmpty();
  array->info = (void*)INDIRECTION_ARRAY_VARIABLE + array_length;
  LinkedListInsertAfter(current_indirection_frame, node, array);
}

void ArrayVariableDeclarator(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  Node* node = 0;
  for(node = current_indirection_frame->last; node; node = node->prev){
    if(node->info == (void*)SEPARATOR_ACTIVE) break;
  }
  if(node == 0){
    node = NodeCreateEmpty();
    node->info = (void*)SEPARATOR_ACTIVE;
    LinkedListInsertLast(current_indirection_frame, node);
  }

  Node* array = NodeCreateEmpty();
  array->info = (void*)INDIRECTION_ARRAY_VARIABLE;
  LinkedListInsertAfter(current_indirection_frame, node, array);
}

void FunctionDeclarator(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  Node* node = 0;
  for(node = current_indirection_frame->last; node; node = node->prev){
    if(node->info == (void*)SEPARATOR_ACTIVE) break;
  }
  if(node == 0){
    node = NodeCreateEmpty();
    node->info = (void*)SEPARATOR_ACTIVE;
    LinkedListInsertLast(current_indirection_frame, node);
  }

  Node* array = NodeCreateEmpty();
  array->info = (void*)INDIRECTION_FUNCTION;
  LinkedListInsertAfter(current_indirection_frame, node, array);

}

void FuncNonprototypeDeclarator(void){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  Node* node = 0;
  for(node = current_indirection_frame->last; node; node = node->prev){
    if(node->info == (void*)SEPARATOR_ACTIVE) break;
  }
  if(node == 0){
    node = NodeCreateEmpty();
    node->info = (void*)SEPARATOR_ACTIVE;
    LinkedListInsertLast(current_indirection_frame, node);
  }

  Node* array = NodeCreateEmpty();
  array->info = (void*)INDIRECTION_NONPROTOTYPE;
  LinkedListInsertAfter(current_indirection_frame, node, array);
}

void PointerOpen(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  Node* separator = NodeCreateEmpty();
  separator->info = (void*)SEPARATOR_INACTIVE;
  LinkedListInsertLast(current_indirection_frame, separator);

  Node* pointer = NodeCreateEmpty();
  pointer->info = (void*)INDIRECTION_POINTER;
  LinkedListInsertLast(current_indirection_frame, pointer);
}

void PointerQualifierOpen(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  Node* separator = NodeCreateEmpty();
  separator->info = (void*)SEPARATOR_INACTIVE;
  LinkedListInsertLast(current_indirection_frame, separator);

  Node* pointer = NodeCreateEmpty();
  pointer->info = (void*)INDIRECTION_POINTER;
  LinkedListInsertLast(current_indirection_frame, pointer);

  Node* qualifiers = NodeCreateEmpty();
  qualifiers->info = (void*)qualifiers_to_indirection[current_qualifiers];
  LinkedListInsertLast(current_indirection_frame, qualifiers);
  current_qualifiers = 0;
}

void Pointer(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  Node* node = 0;
  for(node = current_indirection_frame->last; node; node = node->prev){
    if(node->info == (void*)SEPARATOR_INACTIVE) break;
  }

  Node* pointer = NodeCreateEmpty();
  pointer->info = (void*)INDIRECTION_POINTER;
  LinkedListInsertAfter(current_indirection_frame, node, pointer);
}

void PointerQualifier(){
  LinkedList* current_indirection_frame = StackPeek(&indirection_stack);

  Node* node = 0;
  for(node = current_indirection_frame->last; node; node = node->prev){
    if(node->info == (void*)SEPARATOR_INACTIVE) break;
  }

  Node* pointer = NodeCreateEmpty();
  pointer->info = (void*)INDIRECTION_POINTER;
  LinkedListInsertAfter(current_indirection_frame, node, pointer);

  Node* qualifiers = NodeCreateEmpty();
  qualifiers->info = (void*)qualifiers_to_indirection[current_qualifiers];
  LinkedListInsertAfter(current_indirection_frame, pointer, qualifiers);
  current_qualifiers = 0;
}

void FunctionParamsOpen(){
  Scope* param_scope = ScopeCreateEmpty();
  param_scope->type = SCOPE_FUNC_PROTOTYPE;

  StackPush(&param_scope_stack, param_scope);

  StackPush(&typedef_stack, 0);
  StackPush(&type_stack, TypeFrameCreateEmpty());
  StackPush(&indirection_stack, LinkedListCreateEmpty());
  StackPush(&parameter_stack, LinkedListCreateEmpty());
  StackPush(&name_stack, NameFrameCreateEmpty());
}

void FunctionParamsClose(){
  Scope* param_scope = StackPop(&param_scope_stack);
  if(StackEmpty(&param_scope_stack) && func_prototype_scope == 0) func_prototype_scope = param_scope;
  else ScopeDrop(param_scope);

  StackPop(&typedef_stack);
  TypeFrameDrop(StackPop(&type_stack));
  LinkedListDrop(StackPop(&indirection_stack));
  NameFrameDrop(StackPop(&name_stack));
}

void TypeOpen(){
  StackPush(&typedef_stack, (void*)-1);
  StackPush(&type_stack, TypeFrameCreateEmpty());
  StackPush(&indirection_stack, LinkedListCreateEmpty());
  StackPush(&name_stack, NameFrameCreateEmpty());
}

void TypeClose(){
  StackPop(&typedef_stack);
  TypeFrameDrop(StackPop(&type_stack));
  LinkedListDrop(StackPop(&indirection_stack));
  NameFrameDrop(StackPop(&name_stack));
}

void Ellipsis(){
  LinkedList* parameter_frame = StackPeek(&parameter_stack);

  Node* node = NodeCreateEmpty();
  node->info = 0;
  LinkedListInsertLast(parameter_frame, node);
}