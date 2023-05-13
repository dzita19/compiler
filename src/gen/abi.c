#include "abi.h"

#include <stdlib.h>

#include "util/memory_safety.h"
#include "decl/declarations.h"

const int REG_NUM = 4;

ArgPass* ArgPassCreateEmpty(void){
  ArgPass* arg_pass = malloc(sizeof(arg_pass));
  arg_pass->regs  = 0;
  arg_pass->stack = 0;

  arg_pass_alloc++;

  return arg_pass;
}

void ArgPassDrop(ArgPass* arg_pass){
  free(arg_pass);

  arg_pass_free++;
}

void ArgPassClear(ArgPass* arg_pass){
  arg_pass->regs  = 0;
  arg_pass->stack = -2 * POINTER_SIZE;
}

int ArgPassAllocAddr(ArgPass* arg_pass, Struct* str){
  // arg is passed through a register, address is allocated inside the callee stack frame
  if(StructIsScalar(str) && (arg_pass->regs < REG_NUM)){
    arg_pass->regs++;

    int current_stack_counter = (int)(long)stack_frame_stack.top->info;

    int addr = (current_stack_counter + str->align - 1) / str->align * str->align + str->size;
    current_stack_counter = addr; // + str->size;

    stack_frame_stack.top->info = (void*)(long)current_stack_counter;
    return addr; // + str->size;
  }
  // arg is passed through stack, address is allocated inside the caller stack frame
  else{
    int addr = (arg_pass->stack - str->align + 1) / str->align * str->align;
    arg_pass->stack = addr - str->size;

    return addr;
  }
}