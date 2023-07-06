#include "resources.h"

#include "stmt/expr/expr.h"
#include "assembler.h"

StackAlloc* StackAllocCreateEmpty(void){
  StackAlloc* stack_alloc = malloc(sizeof(StackAlloc));
  stack_alloc->tree_node  = 0;
  stack_alloc->offset     = 0;
  stack_alloc->size       = 0;

  stack_alloc_alloc++;

  return stack_alloc;
}

void StackAllocDump(StackAlloc* stack_alloc){

}

void StackAllocDrop(StackAlloc* stack_alloc){
  free(stack_alloc);

  stack_alloc_free++;
}

MemAlloc* MemAllocCreateEmpty(void){
  MemAlloc* mem_alloc     = malloc(sizeof(MemAlloc));
  mem_alloc->kind         = MEM_ALLOC_TO_ERROR;
  mem_alloc->obj_ref      = 0;
  mem_alloc->string_ref   = 0;
  mem_alloc->offset       = 0;
  mem_alloc->address_node = 0;

  mem_alloc_alloc++;

  return mem_alloc;
}

void MemAllocDump(MemAlloc* mem_alloc){

}

void MemAllocDrop(MemAlloc* mem_alloc){
  free(mem_alloc);
  mem_alloc_free++;
}

MemAlloc* MemAllocCopy(MemAlloc* mem_alloc){
  MemAlloc* new_mem_alloc = MemAllocCreateEmpty();
  new_mem_alloc->kind         = mem_alloc->kind;
  new_mem_alloc->obj_ref      = mem_alloc->obj_ref;
  new_mem_alloc->string_ref   = mem_alloc->string_ref;
  new_mem_alloc->offset       = mem_alloc->offset;
  new_mem_alloc->address_node = mem_alloc->address_node;

  return new_mem_alloc;
}

AllocNode* AllocNodeCreateEmpty(void){
  AllocNode* alloc_node    = malloc(sizeof(AllocNode));
  alloc_node->depth        = 0;
  alloc_node->obj_ref      = 0;
  alloc_node->offset       = 0;
  alloc_node->reg_index    = REG_UNALLOCATED;
  alloc_node->stack_alloc  = 0;
  alloc_node->mem_alloc    = 0;

  alloc_node_alloc++;

  return alloc_node;
}

void AllocNodeDump(AllocNode* alloc_node){

}

void AllocNodeDrop(AllocNode* alloc_node){
  if(alloc_node->mem_alloc) MemAllocDrop(alloc_node->mem_alloc);
  free(alloc_node);
  alloc_node_free++;
}

AllocNode* AllocNodeCopy(AllocNode* alloc_node){
  AllocNode* new_alloc_node = AllocNodeCreateEmpty();
  new_alloc_node->depth        = alloc_node->depth;
  new_alloc_node->obj_ref      = alloc_node->obj_ref;
  new_alloc_node->offset       = alloc_node->offset;
  new_alloc_node->reg_index    = alloc_node->reg_index;
  new_alloc_node->stack_alloc  = alloc_node->stack_alloc;
  new_alloc_node->mem_alloc    = alloc_node->mem_alloc;

  return new_alloc_node;
}

TreeNode*  reg_bank[REGS_COUNT] = { [0 ... REGS_COUNT - 1] = 0 };
LinkedList stack_bank = (LinkedList){ 0, 0 };
int stack_frame_size = 0;
int temp_zone_size = 0;

StackAlloc* AllocateTempZone(Struct* type){
  StackAlloc* last_alloc = stack_bank.last ? stack_bank.last->info : 0;
  int last_offset = last_alloc ? last_alloc->offset : 0;

  StackAlloc* stack_alloc = StackAllocCreateEmpty();
  stack_alloc->offset = (last_offset + type->align - 1) / type->align * type->align + type->size;
  stack_alloc->size = type->size;

  Node* node = NodeCreateEmpty();
  node->info = stack_alloc;
  LinkedListInsertLast(&stack_bank, node);

  int temp_zone_eff_size = stack_alloc->offset;
  if(temp_zone_eff_size > temp_zone_size){
    int increment = (temp_zone_eff_size - temp_zone_size + TEMP_FRAME_SIZE - 1) / TEMP_FRAME_SIZE * TEMP_FRAME_SIZE;
    temp_zone_size += increment;
    GenAsmInstrTwoop(ASM_SUB, ADDR_IMMED, 0, increment, REG_SP, REG_TO_REG);
  }

  return stack_alloc;
}

void FreeTempZone(StackAlloc* stack_alloc){
  for(Node* node = stack_bank.first; node; node = node->next){
    if(node->info == stack_alloc) {
      StackAllocDrop(stack_alloc);
      LinkedListRemoveFrom(&stack_bank, node);
    }
  }

  StackAlloc* last_alloc = stack_bank.first ? stack_bank.first->info : 0;
  int temp_zone_eff_size = last_alloc ? last_alloc->offset : 0;

  if(temp_zone_size - temp_zone_eff_size >= TEMP_FRAME_SIZE){
    int increment = (temp_zone_size - temp_zone_eff_size) / TEMP_FRAME_SIZE * TEMP_FRAME_SIZE;
    temp_zone_size -= increment;
    GenAsmInstrTwoop(ASM_ADD, ADDR_IMMED, 0, increment, REG_SP, REG_TO_REG);
  }
}

// static void GenSpillInstr(int reg_index, StackAlloc* stack_alloc){
//   int instr = 0;
//   if(stack_alloc->size == 1) instr = ASM_MOVB;
//   if(stack_alloc->size == 2) instr = ASM_MOVW;
//   if(stack_alloc->size == 4) instr = ASM_MOVL;

//   GenAsmInstrTwoop(instr, ADDR_REGIND, REG_BP, -(stack_frame_size + stack_alloc->offset), reg_index, REG_TO_MEM);
// }

// static void GenReloadInstr(int reg_index, StackAlloc* stack_alloc){
//   int instr = 0;
//   if(stack_alloc->size == 1) instr = ASM_MOVB;
//   if(stack_alloc->size == 2) instr = ASM_MOVW;
//   if(stack_alloc->size == 4) instr = ASM_MOVL;

//   GenAsmInstrTwoop(instr, ADDR_REGIND, REG_BP, -(stack_frame_size + stack_alloc->offset), reg_index, MEM_TO_REG);
// }

void SpillRegister(int reg_index){
  // if(reg_bank[reg_index] == 0) return;

  // TreeNode* tree_node = reg_bank[reg_index];

  // StackAlloc* stack_alloc = AllocateTempZone(tree_node->expr_node->type);
  // GenSpillInstr(reg_index, stack_alloc);

  // stack_alloc->tree_node = tree_node;
  // tree_node->alloc_node->stack_alloc = stack_alloc;
  // reg_bank[reg_index] = 0;
}

void LoadRegister(TreeNode* tree_node, int reg_index){
  // if(reg_bank[reg_index] == tree_node) return;

  // if(reg_bank[reg_index] != 0){
  //   SpillRegister(reg_index);
  // }

  // StackAlloc* stack_alloc = tree_node->alloc_node->stack_alloc;
  // GenReloadInstr(reg_index, stack_alloc);

  // stack_alloc->tree_node = 0;
  // tree_node->alloc_node->stack_alloc = 0;
  // reg_bank[reg_index] = tree_node;

  // FreeTempZone(stack_alloc);
}

void AllocateRegister(TreeNode* tree_node, int reg_index){
  reg_bank[reg_index] = tree_node;
}

void FreeRegister(int reg_index){
  reg_bank[reg_index] = 0;
}