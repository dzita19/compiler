#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "stmt/stmt.h"
#include "intermediate.h"

#define REGS_COUNT 3
#define TEMP_FRAME_SIZE 16

typedef struct StackAlloc{
  IrInstr* instr;
  int size;
  int offset;
} StackAlloc;

StackAlloc* StackAllocCreateEmpty(void);
void StackAllocDump(StackAlloc*);
void StackAllocDrop(StackAlloc*);

typedef enum MemAllocKind{
  MEM_ALLOC_TO_ERROR,
  MEM_ALLOC_TO_ASSIGN, // uses address_node and offset
  MEM_ALLOC_TO_ARGS, // uses offset, %rsp relative
} MemAllocKind;

typedef struct MemAlloc{
  MemAllocKind kind;
  int offset;
} MemAlloc;

MemAlloc* MemAllocCreateEmpty(void);
void MemAllocDump(MemAlloc*);
void MemAllocDrop(MemAlloc*);

extern int stack_frame_size;
extern int temp_zone_size;

extern IrInstr*   reg_bank[REGS_COUNT];
extern LinkedList stack_bank;

#define REGISTER_SIZE 4
#define REGOF(instr) ((instr->depth - 1) % REGS_COUNT)

extern StackAlloc* AllocateTempZone(void);
extern void FreeTempZone(StackAlloc* stack_alloc);

extern void SpillRegister(int reg_index); // spill register content into the stack
extern void LoadToRegister(IrInstr* instr); // load content into register

extern void AllocateToRegister(IrInstr* instr); // allocates to every register that is modified by instruction
extern void FreeFromRegister(IrInstr* instr);   // frees from a specific register

extern void AllocateStackMemory(int size); // for function entry (callee-perspective)
extern void FreeAllStackMemory(void);      // for function exit  (callee-perspective) - prefered if alloca is used
extern void FreeStackMemory(int size);     // for function exit  (callee-perspective)

extern void AllocateTempMemory(int size);  // before function call (caller-perspective)
extern void FreeTempMemory(int size);      // after  function call (caller-perspective)

#endif