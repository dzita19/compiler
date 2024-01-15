#include "stack.h"

#include <stdlib.h>

#include "memory_safety.h"

Stack* StackCreateEmpty(void){
  Stack* stack = malloc(sizeof(Stack));
  stack->top   = 0;

  stack_alloc++;

  return stack;
}

void StackDelete(Stack* stack){
  while(stack->top){
    StackNode* old = stack->top;
    stack->top = stack->top->next;

    free(old);
  }
}

void StackDrop(Stack* stack){
  StackDelete(stack);

  free(stack);

  stack_free++;
}

void StackPush(Stack* stack, void* info){
  StackNode* node = malloc(sizeof(StackNode));
  node->info = info;
  node->next = stack->top;
  stack->top = node;
}

void* StackPop(Stack* stack){
  StackNode* old = stack->top;
  void* info = stack->top->info;

  if(stack->top == 0) return 0;
  stack->top = stack->top->next;
  
  free(old);
  return info;
}

void* StackPeek(Stack* stack){
  return stack->top->info;
}

int StackEmpty(Stack* stack){
  return stack->top == 0;
}

int StackSize (Stack* stack){
  StackNode* current = stack->top;
  int size = 0;
  while(current){
    size++;
    current = current->next;
  }

  return size;
}