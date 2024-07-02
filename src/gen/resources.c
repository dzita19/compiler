#include "resources.h"

#include "stmt/expr/expr.h"
#include "assembler.h"

StackAlloc* StackAllocCreateEmpty(void){
  StackAlloc* stack_alloc = malloc(sizeof(StackAlloc));
  stack_alloc->instr      = 0;
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
  mem_alloc->offset       = 0;

  mem_alloc_alloc++;

  return mem_alloc;
}

void MemAllocDump(MemAlloc* mem_alloc){

}

void MemAllocDrop(MemAlloc* mem_alloc){
  free(mem_alloc);
  mem_alloc_free++;
}


IrInstr*   reg_bank[REGS_COUNT] = { [0 ... REGS_COUNT - 1] = 0 };
LinkedList stack_bank = (LinkedList){ 0, 0 };
int stack_frame_size = 0;
int temp_zone_size = 0;

StackAlloc* AllocateTempZone(void){
  StackAlloc* last_alloc = stack_bank.last ? stack_bank.last->info : 0;
  int last_offset = last_alloc ? last_alloc->offset : 0;

  StackAlloc* stack_alloc = StackAllocCreateEmpty();
  stack_alloc->offset = (last_offset + REGISTER_SIZE - 1) / REGISTER_SIZE * REGISTER_SIZE + REGISTER_SIZE;
  stack_alloc->size = REGISTER_SIZE;

  Node* node = NodeCreateEmpty();
  node->info = stack_alloc;
  LinkedListInsertLast(&stack_bank, node);

  int temp_zone_eff_size = stack_alloc->offset;
  if(temp_zone_eff_size > temp_zone_size){
    int increment = (temp_zone_eff_size - temp_zone_size + TEMP_FRAME_SIZE - 1) / TEMP_FRAME_SIZE * TEMP_FRAME_SIZE;
    temp_zone_size += increment;
    GenAsmInstrTwoopArithm(ASM_SUB, ASM_DIRECT, increment, REG_SP);
  }

  return stack_alloc;
}

void FreeTempZone(StackAlloc* stack_alloc){
  for(Node* node = stack_bank.first; node; node = node->next){
    if(node->info == stack_alloc) {
      StackAllocDrop(stack_alloc);
      NodeDrop(LinkedListRemoveFrom(&stack_bank, node));
    }
  }

  StackAlloc* last_alloc = stack_bank.first ? stack_bank.first->info : 0;
  int temp_zone_eff_size = last_alloc ? last_alloc->offset : 0;

  if(temp_zone_size - temp_zone_eff_size >= TEMP_FRAME_SIZE){
    int increment = (temp_zone_size - temp_zone_eff_size) / TEMP_FRAME_SIZE * TEMP_FRAME_SIZE;
    temp_zone_size -= increment;
    GenAsmInstrTwoopArithm(ASM_ADD, ASM_DIRECT, increment, REG_SP);
  }
}

static void GenSpillInstr(int reg_index, StackAlloc* stack_alloc){
  int instr = 0;
  if(stack_alloc->size == 1) instr = ASM_MOVB;
  if(stack_alloc->size == 2) instr = ASM_MOVW;
  if(stack_alloc->size == 4) instr = ASM_MOVL;

  GenAsmInstrStoreReg(instr, REG_BP, -(stack_frame_size + stack_alloc->offset), reg_index);
}

static void GenReloadInstr(int reg_index, StackAlloc* stack_alloc){
  int instr = 0;
  if(stack_alloc->size == 1) instr = ASM_MOVB;
  if(stack_alloc->size == 2) instr = ASM_MOVW;
  if(stack_alloc->size == 4) instr = ASM_MOVL;

  GenAsmInstrLoadReg(instr, ASM_INDIRECT, REG_BP, -(stack_frame_size + stack_alloc->offset), reg_index);
}

void SpillRegister(int reg_index){
  if(reg_bank[reg_index] == 0) return;

  IrInstr* instr = reg_bank[reg_index];

  StackAlloc* stack_alloc = AllocateTempZone();
  GenSpillInstr(reg_index, stack_alloc);

  stack_alloc->instr = instr;
  instr->stack_alloc = stack_alloc;
  reg_bank[reg_index] = 0;
}

void LoadToRegister(IrInstr* instr){
  int reg_index = REGOF(instr);
  if(reg_bank[reg_index] == instr) return;

  if(reg_bank[reg_index] != 0){
    SpillRegister(reg_index);
  }

  StackAlloc* stack_alloc = instr->stack_alloc;
  GenReloadInstr(reg_index, stack_alloc);

  stack_alloc->instr = 0;
  instr->stack_alloc = 0;
  reg_bank[reg_index] = instr;

  FreeTempZone(stack_alloc);
}

void AllocateToRegister(IrInstr* instr){
  int reg_index = REGOF(instr);
  SpillRegister(reg_index);
  reg_bank[reg_index] = instr;
}

void FreeFromRegister(IrInstr* instr){
  int reg_index = REGOF(instr);
  reg_bank[reg_index] = 0;
}

void AllocateStackMemory(int size){
  size = (size + FRAME_ALIGNMENT - 1) / FRAME_ALIGNMENT * FRAME_ALIGNMENT;
  stack_frame_size += size;
  if(size > 0) GenAsmInstrTwoopArithm(ASM_SUB, ASM_DIRECT, size, REG_SP);
}

void FreeAllStackMemory(void){
  stack_frame_size = 0;
  GenAsmInstrLoadReg(ASM_MOVL, ASM_DIRECT, REG_BP, 0, REG_SP);
}

void FreeStackMemory(int size){
  size = (size + FRAME_ALIGNMENT - 1) / FRAME_ALIGNMENT * FRAME_ALIGNMENT;
  stack_frame_size -= size;
  if(size > 0) GenAsmInstrTwoopArithm(ASM_ADD, ASM_DIRECT, size, REG_SP);
}

void AllocateTempMemory(int size){
  size = (size + TEMP_FRAME_SIZE - 1) / TEMP_FRAME_SIZE * TEMP_FRAME_SIZE;
  temp_zone_size += size;
  if(size > 0) GenAsmInstrTwoopArithm(ASM_SUB, ASM_DIRECT, size, REG_SP);
}

void FreeTempMemory(int size){
  size = (size + TEMP_FRAME_SIZE - 1) / TEMP_FRAME_SIZE * TEMP_FRAME_SIZE;
  temp_zone_size -= size;
  if(size > 0) GenAsmInstrTwoopArithm(ASM_ADD, ASM_DIRECT, size, REG_SP);
}