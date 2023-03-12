#include "indirections.h"

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
  static int array_length = 0;

  array_length++; // TEST

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
  //SymtabOpenScope(symtab, SCOPE_FUNC_PROTOTYPE);

  StackPush(&typedef_stack, 0);
  StackPush(&type_stack, TypeFrameCreateEmpty());
  StackPush(&indirection_stack, LinkedListCreateEmpty());
  StackPush(&parameter_stack, LinkedListCreateEmpty());
  StackPush(&name_stack, NameFrameCreateEmpty());
}

void FunctionParamsClose(){
  StackPop(&typedef_stack);
  free(StackPop(&type_stack));
  free(StackPop(&indirection_stack));
  free(StackPop(&name_stack));
}

void Ellipsis(){

}