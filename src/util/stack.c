#include "stack.h"

#include <stdlib.h>

void StackPush(Stack* stack, void* info){
  StackNode* node = malloc(sizeof(StackNode));
  node->info = info;
  node->next = stack->top;
  stack->top = node;
}

void* StackPop(Stack* stack){
  StackNode* top = stack->top;
  if(stack->top == 0) return 0;

  stack->top = stack->top->next;
  return top->info;
}