#include "ir_to_asm.h"

#define TRANSLATION_ERROR  GenAsmLine("ERROR INSTRUCTION");

// generates result
static void TranslatePush(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  AsmInstr instr = (AsmInstr)0;
  switch(operation->opcode){
  case IR_PUSHB:  instr = ASM_MOVB; break;
  case IR_PUSHW:  instr = ASM_MOVW; break;
  case IR_PUSHL:  instr = ASM_MOVL; break;
  case IR_VPUSHB: instr = ASM_MOVB; break;
  case IR_VPUSHW: instr = ASM_MOVW; break;
  case IR_VPUSHL: instr = ASM_MOVL; break;
  default: break;
  }

  int addressing = 0;
  if(operation->addr == IR_ADDR_DIRECT) addressing = ASM_DIRECT;
  else addressing = ASM_INDIRECT;

  if(operation->operand == IR_OP_OBJ){
    AllocateToRegister(operation);
    GenAsmInstrLoadObj(instr, addressing, operation->obj_ref, operation->offset, REGOF(operation));
  }
  else if(operation->operand == IR_OP_ARITHM){
    AllocateToRegister(operation);
    GenAsmInstrLoadArithm(instr, addressing, operation->offset, REGOF(operation));
  }
  else if(operation->operand == IR_OP_STRING){
    AllocateToRegister(operation);
    GenAsmInstrLoadString(instr, addressing, operation->string_ref, operation->offset, REGOF(operation));
  }
  else if(operation->operand == IR_OP_STACK_READ){
    int operand_index = InstrFindOperand(instr_index, operation->reg_ref);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);

    LoadToRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrLoadReg(instr, addressing, REGOF(operand), operation->offset, REGOF(operation));
  }
  else TRANSLATION_ERROR;
}

// doesn't generate result
static void TranslatePop(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  int operand_index = InstrFindOperand(instr_index, 0);
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operation->operand == IR_OP_STACK_POP){
    LoadToRegister(operand);
    FreeFromRegister(operand);
  }
  else TRANSLATION_ERROR;
}

// generates result
static void TranslateDup(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  int operand_index = InstrFindOperand(instr_index, 0);
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operation->operand == IR_OP_STACK_POP){
    LoadToRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrLoadReg(ASM_MOVL, ASM_DIRECT, REGOF(operand), operation->offset, REGOF(operation));
  }
  else TRANSLATION_ERROR;
}

// generates result
static void TranslateReviv(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->operand == IR_OP_STACK_POP){
    AllocateToRegister(operation);
  }
  else TRANSLATION_ERROR;
}

static void TranslateStore(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  AsmInstr instr = (AsmInstr)0;
  switch(operation->opcode){
  case IR_STORB: instr = ASM_MOVB; break;
  case IR_STORW: instr = ASM_MOVW; break;
  case IR_STORL: instr = ASM_MOVL; break;
  default: break;
  }

  int rval_index = InstrFindOperand(instr_index, 0);
  IrInstr* rval  = VectorGet(ir_sequence, rval_index);

  if(operation->operand == IR_OP_STACK_POP){
    if(operation->addr != IR_ADDR_DIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    int lval_index = InstrFindOperand(instr_index, 1);
    IrInstr* lval  = VectorGet(ir_sequence, lval_index);

    LoadToRegister(lval);
    LoadToRegister(rval);
    FreeFromRegister(rval); // rval
    FreeFromRegister(lval); // lval
    GenAsmInstrStoreReg(instr, REGOF(lval), operation->offset, REGOF(rval));
  }
  else if(operation->operand == IR_OP_OBJ){
    if(operation->addr != IR_ADDR_INDIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    LoadToRegister(rval);
    FreeFromRegister(rval);
    GenAsmInstrStoreObj(instr, operation->obj_ref, operation->offset, REGOF(rval));
  }
  else if(operation->operand == IR_OP_ARITHM){
    if(operation->addr != IR_ADDR_INDIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    LoadToRegister(rval);
    FreeFromRegister(rval);
    GenAsmInstrStoreArithm(instr, operation->offset, REGOF(rval));
  }
  else if(operation->operand == IR_OP_STRING){
    if(operation->addr != IR_ADDR_INDIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    LoadToRegister(rval);
    FreeFromRegister(rval);
    GenAsmInstrStoreString(instr, operation->string_ref, operation->offset, REGOF(rval));
  }
  else if(operation->operand == IR_OP_STACK_READ){
    if(operation->addr != IR_ADDR_INDIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    int lval_index = InstrFindOperand(instr_index, operation->reg_ref);
    IrInstr* lval  = VectorGet(ir_sequence, lval_index);

    LoadToRegister(lval);
    LoadToRegister(rval);
    FreeFromRegister(rval);
    GenAsmInstrStoreReg(instr, REGOF(lval), operation->offset, REGOF(rval));
  }
  else if(operation->operand == IR_OP_ARG){
    LoadToRegister(rval);
    FreeFromRegister(rval);
    GenAsmInstrStoreReg(instr, REG_SP, operation->offset, REGOF(rval));
  }
  else TRANSLATION_ERROR;
}

static void TranslateDeref(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  AsmInstr instr = (AsmInstr)0;
  switch(operation->opcode){
  case IR_DERFB: instr = ASM_MOVB; break;
  case IR_DERFW: instr = ASM_MOVW; break;
  case IR_DERFL: instr = ASM_MOVL; break;
  default: break;
  }

  int operand_index = InstrFindOperand(instr_index, 0);
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operation->addr != IR_ADDR_DIRECT) {
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_STACK_POP){
    LoadToRegister(operand);
    FreeFromRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrLoadReg(instr, ASM_INDIRECT, REGOF(operand), operation->offset, REGOF(operation));
  }
  else TRANSLATION_ERROR;
}

static void TranslateFetchDeref(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  AsmInstr instr = (AsmInstr)0;
  switch(operation->opcode){
  case IR_FDRFB: instr = ASM_MOVB; break;
  case IR_FDRFW: instr = ASM_MOVW; break;
  case IR_FDRFL: instr = ASM_MOVL; break;
  default: break;
  }

  int operand_index = InstrFindOperand(instr_index, 0);
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_STACK_POP){
    LoadToRegister(operand);
    AllocateToRegister(operation);
    // move r1 to r2
    GenAsmInstrLoadReg(ASM_MOVL, ASM_DIRECT, REGOF(operand), 0, REGOF(operation));
    GenAsmInstrLoadReg(instr, ASM_INDIRECT, REGOF(operand), 0, REGOF(operand));
  }
  else TRANSLATION_ERROR;
}

static void TranslateEnter(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT) {
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_ARITHM){
    GenAsmInstrOneop(ASM_PUSHL, REG_BP);
    GenAsmInstrLoadReg(ASM_MOVL, ASM_DIRECT, REG_SP, 0, REG_BP);
    AllocateStackMemory(operation->offset);
  }
  else TRANSLATION_ERROR;
}

static void TranslateExit(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT) {
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_ARITHM){
    // FreeStackMemory(operation->offset);
    FreeAllStackMemory();
    GenAsmInstrOneop(ASM_POPL, REG_BP);
    GenAsmInstrNoop(ASM_RET);
  }
  else TRANSLATION_ERROR;
}

static void TranslateCall(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_STACK_POP){
    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);

    LoadToRegister(operand);
    GenAsmInstrBranchReg(ASM_CALL, ASM_BRANCH_DIRECT, REGOF(operand), 0);
    FreeFromRegister(operand);
  }
  else if(operation->operand == IR_OP_OBJ){
    GenAsmInstrBranchObj(ASM_CALL, ASM_BRANCH_DIRECT, operation->obj_ref, operation->offset);
  }
  else if(operation->operand == IR_OP_ARITHM){
    GenAsmInstrBranchArithm(ASM_CALL, ASM_BRANCH_DIRECT, operation->offset);
  }
  else if(operation->operand == IR_OP_STRING){
    GenAsmInstrBranchString(ASM_CALL, ASM_BRANCH_DIRECT, operation->string_ref, operation->offset);
  }
  else TRANSLATION_ERROR;
}

static void TranslateAlign(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT) {
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_ARITHM){
    for(int i = 0; i < REGS_COUNT; i++){
      SpillRegister(i);
    }
    AllocateTempMemory(operation->offset);
  }
  else TRANSLATION_ERROR;
}

static void TranslateDealign(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT) {
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_ARITHM){
    FreeTempMemory(operation->offset);
  }
  else TRANSLATION_ERROR;
}

static void TranslateSetret(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  int operand_index = InstrFindOperand(instr_index, 0);
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_STACK_POP){
    LoadToRegister(operand);
    if(REGOF(operand) != SCALAR_RET_REG){
      GenAsmInstrLoadReg(ASM_MOVL, ASM_DIRECT, REGOF(operand), 0, SCALAR_RET_REG);
    }
    FreeFromRegister(operand);
  }
  else TRANSLATION_ERROR;
}

static void TranslateGetret(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_STACK_POP){
    AllocateToRegister(operation);
    if(REGOF(operation) != SCALAR_RET_REG){
      GenAsmInstrLoadReg(ASM_MOVL, ASM_DIRECT, SCALAR_RET_REG, 0, REGOF(operation));
    }
  }
  else TRANSLATION_ERROR;
}


static void TranslateUnary(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  AsmInstr instr = (AsmInstr)0;
  switch(operation->opcode){
  case IR_INC:  instr = ASM_INC;  break;
  case IR_DEC:  instr = ASM_DEC;  break;
  case IR_NEG:  instr = ASM_NEG;  break;
  case IR_NOT:  instr = ASM_NOT;  break;

  case IR_SXBW: instr = ASM_SXBW; break;
  case IR_SXBL: instr = ASM_SXBL; break;
  case IR_SXWL: instr = ASM_SXWL; break;
  case IR_ZXBW: instr = ASM_ZXBW; break;
  case IR_ZXBL: instr = ASM_ZXBL; break;
  case IR_ZXWL: instr = ASM_ZXWL; break;
  
  default: break;
  }

  int operand_index = InstrFindOperand(instr_index, 0);
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }
  
  if(operation->operand == IR_OP_STACK_POP){
    LoadToRegister(operand);
    FreeFromRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrOneop(instr, REGOF(operation));
  }
  else TRANSLATION_ERROR;
}

static void TranslateBinary(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  AsmInstr instr = (AsmInstr)0;
  switch(operation->opcode){
  case IR_MUL:  instr = ASM_MUL;  break;
  case IR_IMUL: instr = ASM_IMUL; break;
  case IR_DIV:  instr = ASM_DIV;  break;
  case IR_IDIV: instr = ASM_IDIV; break;
  case IR_MOD:  instr = ASM_MOD;  break;
  case IR_IMOD: instr = ASM_IMOD; break;
  case IR_ADD:  instr = ASM_ADD;  break;
  case IR_SUB:  instr = ASM_SUB;  break;

  case IR_LSL:  instr = ASM_LSL;  break;
  case IR_LSR:  instr = ASM_LSR;  break;
  case IR_ASL:  instr = ASM_ASL;  break;
  case IR_ASR:  instr = ASM_ASR;  break;

  case IR_AND:  instr = ASM_AND;  break;
  case IR_XOR:  instr = ASM_XOR;  break;
  case IR_OR:   instr = ASM_OR;   break;

  default: break;
  }

  if(operation->operand == IR_OP_STACK_POP){
    if(operation->addr != IR_ADDR_DIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    int rval_index = InstrFindOperand(instr_index, 0);
    IrInstr* rval  = VectorGet(ir_sequence, rval_index);
    int lval_index = InstrFindOperand(instr_index, 1);
    IrInstr* lval  = VectorGet(ir_sequence, lval_index);

    LoadToRegister(lval);
    LoadToRegister(rval);
    FreeFromRegister(lval);
    FreeFromRegister(rval);
    AllocateToRegister(operation);
    GenAsmInstrTwoopReg(instr, ASM_DIRECT, REGOF(rval), 0, REGOF(lval));
  }
  else if(operation->operand == IR_OP_OBJ){
    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);
    int addressing = operation->addr == IR_ADDR_DIRECT ? ASM_DIRECT : ASM_INDIRECT;

    LoadToRegister(operand);
    FreeFromRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrTwoopObj(instr, addressing, operation->obj_ref, operation->offset, REGOF(operand));
  }
  else if(operation->operand == IR_OP_ARITHM){
    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);
    int addressing = operation->addr == IR_ADDR_DIRECT ? ASM_DIRECT : ASM_INDIRECT;

    LoadToRegister(operand);
    FreeFromRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrTwoopArithm(instr, addressing, operation->offset, REGOF(operand));
  }
  else if(operation->operand == IR_OP_STRING){
    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);
    int addressing = operation->addr == IR_ADDR_DIRECT ? ASM_DIRECT : ASM_INDIRECT;

    LoadToRegister(operand);
    FreeFromRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrTwoopString(instr, addressing, operation->string_ref, operation->offset, REGOF(operand));
  }
  else if(operation->operand == IR_OP_SWTAB){
    if(operation->addr != IR_ADDR_DIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);

    LoadToRegister(operand);
    FreeFromRegister(operand);
    AllocateToRegister(operation);
    GenAsmInstrTwoopSwtab(instr, operation->offset, 0, REGOF(operation));
  }
}

static void TranslateCompare(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);
  
  if(operation->operand == IR_OP_STACK_POP){
    if(operation->addr != IR_ADDR_DIRECT) {
      TRANSLATION_ERROR;
      return;
    }

    int rval_index = InstrFindOperand(instr_index, 0);
    IrInstr* rval  = VectorGet(ir_sequence, rval_index);
    int lval_index = InstrFindOperand(instr_index, 1);
    IrInstr* lval  = VectorGet(ir_sequence, lval_index);

    LoadToRegister(lval);
    LoadToRegister(rval);
    FreeFromRegister(lval);
    FreeFromRegister(rval);
    GenAsmInstrTwoopReg(ASM_CMP, ASM_DIRECT, REGOF(rval), 0, REGOF(lval));
  }
  else if(operation->operand == IR_OP_OBJ){
    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);
    int addressing = operation->addr == IR_ADDR_DIRECT ? ASM_DIRECT : ASM_INDIRECT;

    LoadToRegister(operand);
    FreeFromRegister(operand);
    GenAsmInstrTwoopObj(ASM_CMP, addressing, operation->obj_ref, operation->offset, REGOF(operand));
  }
  else if(operation->operand == IR_OP_ARITHM){
    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);
    int addressing = operation->addr == IR_ADDR_DIRECT ? ASM_DIRECT : ASM_INDIRECT;

    LoadToRegister(operand);
    FreeFromRegister(operand);
    GenAsmInstrTwoopArithm(ASM_CMP, addressing, operation->offset, REGOF(operand));
  }
  else if(operation->operand == IR_OP_STRING){
    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);
    int addressing = operation->addr == IR_ADDR_DIRECT ? ASM_DIRECT : ASM_INDIRECT;

    LoadToRegister(operand);
    FreeFromRegister(operand);
    GenAsmInstrTwoopString(ASM_CMP, addressing, operation->string_ref, operation->offset, REGOF(operand));
  }
}

static void TranslateJump(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);
  
  AsmInstr instr = (AsmInstr)0;
  switch(operation->opcode){
  case IR_JMP: instr = ASM_JMP; break;
  case IR_JEQ: instr = ASM_JEQ; break;
  case IR_JNQ: instr = ASM_JNQ; break;
  case IR_JGT: instr = ASM_JGT; break;
  case IR_JGE: instr = ASM_JGE; break;
  case IR_JLT: instr = ASM_JLT; break;
  case IR_JLE: instr = ASM_JLE; break;
  case IR_JA:  instr = ASM_JA;  break;
  case IR_JB:  instr = ASM_JB;  break;
  case IR_JAE: instr = ASM_JAE; break;
  case IR_JBE: instr = ASM_JBE; break;
  default: break;
  }

  if(operation->operand == IR_OP_STACK_POP){
    if(operation->addr != IR_ADDR_INDIRECT){
      TRANSLATION_ERROR;
      return;
    }

    int operand_index = InstrFindOperand(instr_index, 0);
    IrInstr* operand  = VectorGet(ir_sequence, operand_index);

    LoadToRegister(operand);
    FreeFromRegister(operand);
    GenAsmInstrBranchReg(instr, ASM_INDIRECT, REGOF(operand), operation->offset);
  }
  else if(operation->operand == IR_OP_LABEL){
    if(operation->addr != IR_ADDR_DIRECT){
      TRANSLATION_ERROR;
      return;
    }

    GenAsmInstrBranchLabel(instr, ASM_DIRECT, operation->offset, 0);
  }
  else if(operation->operand == IR_OP_INITLOOP){
    if(operation->addr != IR_ADDR_DIRECT){
      TRANSLATION_ERROR;
      return;
    }

    GenAsmInstrBranchInitLoop(instr, ASM_DIRECT, operation->offset, 0);
  }
  else TRANSLATION_ERROR;
}

static void TranslateLogenter(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_NO_OPERAND){
    int min_depth = operation->depth + 1;
    int max_depth = operation->depth + 1;
    int nested = 1;
    for(int i = instr_index; i < ir_sequence->size; i++){
      IrInstr* instr = VectorGet(ir_sequence, i);
      if     (instr->opcode == IR_LOGENT) nested++;
      else if(instr->opcode == IR_LOGEXT) nested--;

      if(nested == 0) break;

      if(instr->depth > max_depth) max_depth = instr->depth;
    }

    for(int i = min_depth; i <= max_depth; i++) SpillRegister((i - 1) % REGS_COUNT);
  }
  else TRANSLATION_ERROR;
}

static void TranslateLogexit(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand != IR_OP_NO_OPERAND) TRANSLATION_ERROR;
}

static void TranslateCondition(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_STACK_POP){
    AllocateToRegister(operation);
  }
  else TRANSLATION_ERROR;
}

static void TranslateTabenter(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_SWTAB){
    GenAsmSection(".rodata");
    GenAsmTextLabel(default_base_switch, operation->offset);
  }
}

static void TranslateTabexit(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_SWTAB){
    GenAsmSection(".text");
  }
  else TRANSLATION_ERROR;
}

static void TranslateTabline(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_DIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_LABEL){
    GenAsmDataLabel(POINTER_SIZE, operation->offset);
  }
  else TRANSLATION_ERROR;
}

static void TranslateInlineAssembly(int instr_index){
  IrInstr* operation = VectorGet(ir_sequence, instr_index);

  if(operation->addr != IR_ADDR_INDIRECT){
    TRANSLATION_ERROR;
    return;
  }

  if(operation->operand == IR_OP_STRING){
    GenAsmLine(VectorGet(string_table, operation->string_ref));
  }
  else TRANSLATION_ERROR;
}



// load operands (if any)
// alloc to reg (if generates result)
void TranslateToAssembler(int instr_index){

  IrInstr* instr = VectorGet(ir_sequence, instr_index);

  switch(instr->opcode){
  case IR_NOP: break;
  case IR_FUNCT:
    GenAsmNewline();
    GenAsmSymbolLabel(instr->obj_ref->name);
    break;
  case IR_LABEL:
    GenAsmTextLabel(default_base_text, instr->offset);
    break;
  case IR_INITLOOP:
    GenAsmTextLabel(default_base_initloop, instr->offset);
    break;

  case IR_VPUSHB:
  case IR_VPUSHW:
  case IR_VPUSHL:
  case IR_PUSHB:
  case IR_PUSHW:
  case IR_PUSHL:
    TranslatePush(instr_index);
    break;

  case IR_POP:
  case IR_VPOP:
    TranslatePop(instr_index);
    break;
  case IR_DUP:
    TranslateDup(instr_index);
    break;
  case IR_REVIV:
    TranslateReviv(instr_index);
    break;

  case IR_STORB:
  case IR_STORW:
  case IR_STORL:
    TranslateStore(instr_index);
    break;

  case IR_DERFB:
  case IR_DERFW:
  case IR_DERFL:
    TranslateDeref(instr_index);
    break;

  case IR_FDRFB:
  case IR_FDRFW:
  case IR_FDRFL:
    TranslateFetchDeref(instr_index);
    break;

  case IR_ENTER:
    TranslateEnter(instr_index);
    break;
  case IR_EXIT:
    TranslateExit(instr_index);
    break;
  case IR_CALL:
    TranslateCall(instr_index);
    break;
  case IR_ALIGN:
    TranslateAlign(instr_index);
    break;
  case IR_DEALGN:
    TranslateDealign(instr_index);
    break;
  case IR_SETRET:
    TranslateSetret(instr_index);
    break;
  case IR_GETRET:
    TranslateGetret(instr_index);
    break;

  case IR_INC:
  case IR_DEC:
  case IR_NEG:
  case IR_NOT:

  case IR_SXBW:
  case IR_SXBL:
  case IR_SXWL:
  case IR_ZXBW:
  case IR_ZXBL:
  case IR_ZXWL:
    TranslateUnary(instr_index);
    break;

  case IR_MUL:
  case IR_IMUL:
  case IR_DIV:
  case IR_IDIV:
  case IR_MOD:
  case IR_IMOD:
  case IR_ADD:
  case IR_SUB:

  case IR_LSL:
  case IR_LSR:
  case IR_ASL:
  case IR_ASR:

  case IR_AND:
  case IR_XOR:
  case IR_OR:
    TranslateBinary(instr_index);
    break;

  case IR_CMP:
    TranslateCompare(instr_index);
    break;
  
  case IR_JMP:
  case IR_JEQ:
  case IR_JNQ:
  case IR_JGT:
  case IR_JGE:
  case IR_JLT:
  case IR_JLE:
  case IR_JA:
  case IR_JB:
  case IR_JAE:
  case IR_JBE:
    TranslateJump(instr_index);
    break;

  case IR_LOGENT:
    TranslateLogenter(instr_index);
    break;
  case IR_LOGEXT:
    TranslateLogexit(instr_index);
    break;
  case IR_COND:
    TranslateCondition(instr_index);
    break;

  case IR_TABENT:
    TranslateTabenter(instr_index);
    break;
  case IR_TABEXT:
    TranslateTabexit(instr_index);
    break;
  case IR_TABLIN:
    TranslateTabline(instr_index);
    break;

  case IR_ASM:
    TranslateInlineAssembly(instr_index);
    break;
  }
}

void GenerateAssembly(void){
  if(ir_sequence->size > 0) GenAsmSection(".text");
  for(int i = 0; i < ir_sequence->size; i++) TranslateToAssembler(i);
  if(ir_sequence->size > 0) GenAsmNewline();
}