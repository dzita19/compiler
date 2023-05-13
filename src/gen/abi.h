#ifndef _ABI_H_
#define _ABI_H_

#include "symtab/struct.h"

extern const int REG_NUM;

typedef struct ArgPass {
  int regs;
  int stack;
} ArgPass;

extern ArgPass* ArgPassCreateEmpty(void);
extern void ArgPassDrop(ArgPass*);
extern void ArgPassClear(ArgPass*);

extern int  ArgPassAllocAddr(ArgPass*, Struct* str);

#endif