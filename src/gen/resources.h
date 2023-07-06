#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "stmt/stmt.h"

#define REGS_COUNT 3
#define TEMP_FRAME_SIZE 3

typedef struct StackAlloc{
  TreeNode* tree_node;
  int size;
  int offset;
} StackAlloc;

StackAlloc* StackAllocCreateEmpty(void);
void StackAllocDump(StackAlloc*);
void StackAllocDrop(StackAlloc*);

#define REG_UNALLOCATED  -1
// for nodes that are the first expression node in a statement
#define REG_INSTR_LOADED -2
// for nodes that are loadable as an operand of instruction

typedef enum MemAllocKind{
  MEM_ALLOC_TO_ERROR,
  MEM_ALLOC_TO_OBJ, // uses obj_ref and offset
  MEM_ALLOC_TO_STRING, // uses string_index and offset
  MEM_ALLOC_TO_ARITHM, // uses offset, absolute
  MEM_ALLOC_TO_TEMP, // uses offset, %rbp relative
  MEM_ALLOC_TO_ARGS, // uses offset, %rsp relative
  MEM_ALLOC_TO_DEREF, // uses address_node and offset
} MemAllocKind;

typedef struct MemAlloc{
  MemAllocKind kind;
  Obj* obj_ref;
  int string_ref;
  int offset; // offset from obj, string; const; offset from %rbp, %rsp
  TreeNode* address_node; // subexpr to be dereffed
} MemAlloc;

MemAlloc* MemAllocCreateEmpty(void);
void MemAllocDump(MemAlloc*);
void MemAllocDrop(MemAlloc*);
MemAlloc* MemAllocCopy(MemAlloc*);

typedef struct AllocNode{
  int depth;
  Obj* obj_ref;
  int offset;
  int reg_index;
  MemAlloc* mem_alloc; // used only for nodes with compound type
  StackAlloc* stack_alloc;
} AllocNode;

AllocNode* AllocNodeCreateEmpty(void);
void AllocNodeDump(AllocNode*);
void AllocNodeDrop(AllocNode*);
AllocNode* AllocNodeCopy(AllocNode*);

extern int stack_frame_size;
extern int temp_zone_size;

extern TreeNode*  reg_bank[REGS_COUNT];
extern LinkedList stack_bank;

extern StackAlloc* AllocateTempZone(Struct* type);
extern void FreeTempZone(StackAlloc* stack_alloc);

extern void SpillRegister(int reg_index); // spill register content into the stack
extern void LoadRegister(TreeNode* tree_node, int reg_index); // load content into register

extern void AllocateRegister(TreeNode* tree_node, int reg_index);
extern void FreeRegister(int reg_index);

#endif