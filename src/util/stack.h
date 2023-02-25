#ifndef _STACK_H_
#define _STACK_H_

typedef struct stacknode {
  void* info;
  struct stacknode* next;
} StackNode;

typedef struct{
  StackNode* top;
} Stack; 

extern void  StackPush(Stack* stack, void* info);
extern void* StackPop (Stack* stack);

#endif