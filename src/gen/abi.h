#ifndef _ABI_H_
#define _ABI_H_

#include "generator.h"
#include "symtab/symtab.h"

/*
SCALAR ARGUMENT are passed through registers, but they also have memory locations reserved inside callee stack frame
there is a maximum of REG_NUM registers, other arguments go to the stack
STRUCT ARGUMENTS are passed to the stack (always)
SCALAR RETURN values are returned through %reg0
STRUCT RETURN values are returned through stack (space allocated by caller)
STRUCT RETURN address is passed through register, as the first argument, it is later returned in %reg0

Upon entering a function, base pointer is aligned to 8
All general purpose registers are volatile (except stack pointer, base pointer and instruction pointer)
*/

#define PARAM_REGS_COUNT 0

#define FRAME_ALIGNMENT 8

#define ARG_TO_REG    0
#define ARG_TO_STACK  1

extern int regs_for_params[PARAM_REGS_COUNT];

typedef struct ArgAlloc{
  int addr; // reg index or stack position
  int mode; // ARG_TO_REG or ARG_TO_STACK
} ArgAlloc;

typedef struct CallFrame {
  int regs;
  int stack;
} CallFrame; // current function call

extern ArgAlloc* ArgAllocCreateEmpty(void);
extern void ArgAllocDrop(ArgAlloc*);
extern void ArgAllocClear(ArgAlloc*);

extern CallFrame* CallFrameCreateEmpty(void);
extern void CallFrameDrop(CallFrame*);
extern void CallFrameClear(CallFrame*);

extern ArgAlloc* GetArgAllocation(CallFrame*, Struct* str);
extern ArgAlloc* GetReturnAddressAllocation(CallFrame*); // doesn't check if type is scalar - check before calling
extern int  CallFrameAllocAddr(CallFrame*, Struct* str);
extern int  CallFrameAllocReturnAddr(CallFrame*); // doesn't check if type is scalar - check before calling

#endif