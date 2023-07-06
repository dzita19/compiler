#include "abi.h"

#include <stdlib.h>

#include "util/memory_safety.h"
#include "decl/declarations.h"

int regs_for_params[PARAM_REGS_COUNT] = { };

ArgAlloc* ArgAllocCreateEmpty(void){
  ArgAlloc* arg_alloc = malloc(sizeof(ArgAlloc));
  arg_alloc->mode = 0;
  arg_alloc->addr = 0;
  
  arg_alloc_alloc++;

  return arg_alloc;
}

void ArgAllocDump(ArgAlloc* arg_alloc){

}

void ArgAllocDrop(ArgAlloc* arg_alloc){
  free(arg_alloc);
  arg_alloc_free++;
}

CallFrame* CallFrameCreateEmpty(void){
  CallFrame* call_frame = malloc(sizeof(CallFrame));
  call_frame->regs  = 0;
  call_frame->stack = 0;

  call_frame_alloc++;

  return call_frame;
}

void CallFrameDrop(CallFrame* call_frame){
  free(call_frame);

  call_frame_free++;
}

void CallFrameClear(CallFrame* call_frame){
  call_frame->regs  = 0;
  call_frame->stack = -2 * POINTER_SIZE;
}

ArgAlloc* GetArgAllocation(CallFrame* call_frame, Struct* str){
  ArgAlloc* arg_alloc = ArgAllocCreateEmpty();

  if(StructIsScalar(str) && call_frame->regs < PARAM_REGS_COUNT){
    arg_alloc->mode = ARG_TO_REG;
    arg_alloc->addr = call_frame->regs++;  
  }
  else{
    arg_alloc->mode = ARG_TO_STACK;
    arg_alloc->addr = (call_frame->stack + str->align - 1) / str->align * str->align;
    call_frame->stack = arg_alloc->addr + str->size;
  }

  return arg_alloc;
}

ArgAlloc* GetReturnAddressAllocation(CallFrame* call_frame){
  ArgAlloc* arg_alloc = ArgAllocCreateEmpty();

  if(call_frame->regs < PARAM_REGS_COUNT){
    arg_alloc->mode = ARG_TO_REG;
    arg_alloc->addr = call_frame->regs++;  
  }
  else{
    arg_alloc->mode = ARG_TO_STACK;
    arg_alloc->addr = (call_frame->stack + POINTER_SIZE - 1) / POINTER_SIZE * POINTER_SIZE;
    call_frame->stack = arg_alloc->addr + POINTER_SIZE;
  }

  return arg_alloc;
}

int CallFrameAllocAddr(CallFrame* call_frame, Struct* str){
  // arg is passed through a register, address is allocated inside the callee stack frame
  if(StructIsScalar(str) && call_frame->regs < PARAM_REGS_COUNT){
    call_frame->regs++;

    int current_stack_counter = (int)(long)stack_frame_stack.top->info;

    int addr = (current_stack_counter + str->align - 1) / str->align * str->align + str->size;
    current_stack_counter = addr; // + str->size;

    stack_frame_stack.top->info = (void*)(long)current_stack_counter;
    return addr; // + str->size;
  }
  // arg is passed through stack, address is allocated inside the caller stack frame
  else{
    int addr = (call_frame->stack - str->align + 1) / str->align * str->align;
    call_frame->stack = addr - str->size;

    return addr;
  }
}

int CallFrameAllocReturnAddr(CallFrame* call_frame){
  if(call_frame->regs < PARAM_REGS_COUNT){
    call_frame->regs++;

    int current_stack_counter = (int)(long)stack_frame_stack.top->info;

    int addr = (current_stack_counter + POINTER_SIZE - 1) / POINTER_SIZE * POINTER_SIZE + POINTER_SIZE;
    current_stack_counter = addr; // + str->size;

    stack_frame_stack.top->info = (void*)(long)current_stack_counter;
    return addr; // + str->size;
  }
  else{
    int addr = (call_frame->stack - POINTER_SIZE + 1) / POINTER_SIZE * POINTER_SIZE;
    call_frame->stack = addr - POINTER_SIZE;

    return addr;
  }
}