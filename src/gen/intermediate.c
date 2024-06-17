#include "intermediate.h"

#include "util/memory_safety.h"

const char* ir_opcode_names[] = {
  [IR_NOP]    = "NOP",
  [IR_FUNCT]  = "FUNCT",
  [IR_LABEL]  = "LABEL",
  [IR_INITLOOP] = "INITLOOP",

  [IR_PUSHB]  = "PUSHB",
  [IR_PUSHW]  = "PUSHW",
  [IR_PUSHL]  = "PUSHL",
  [IR_VPUSHB] = "VPUSHB",
  [IR_VPUSHW] = "VPUSHW",
  [IR_VPUSHL] = "VPUSHL",
  [IR_POP]    = "POP",
  [IR_VPOP]   = "VPOP",
  [IR_DUP]    = "DUP",
  [IR_REVIV]  = "REVIV",

  [IR_STORB]  = "STORB",
  [IR_STORW]  = "STORW",
  [IR_STORL]  = "STORL",

  [IR_DERFB]  = "DERFB",
  [IR_DERFW]  = "DERFW",
  [IR_DERFL]  = "DERFL",

  [IR_FDRFB]  = "FDRFB",
  [IR_FDRFW]  = "FDRFW",
  [IR_FDRFL]  = "FDRFL",
  
  [IR_ENTER]  = "ENTER",
  [IR_EXIT]   = "EXIT",
  [IR_CALL]   = "CALL",
  [IR_ALIGN]  = "ALIGN",
  [IR_DEALGN] = "DEALGN",
  [IR_SETRET] = "SETRET",
  [IR_GETRET] = "GETRET",

  [IR_INC]    = "INC",
  [IR_DEC]    = "DEC",
  [IR_NEG]    = "NEG",
  [IR_NOT]    = "NOT",

  [IR_SXBW]   = "SXBW",
  [IR_SXBL]   = "SXBL",
  [IR_SXWL]   = "SXWL",
  [IR_ZXBW]   = "ZXBW",
  [IR_ZXBL]   = "ZXBL",
  [IR_ZXWL]   = "ZXWL",

  [IR_MUL]    = "MUL",
  [IR_IMUL]   = "IMUL",
  [IR_DIV]    = "DIV",
  [IR_IDIV]   = "IDIV",
  [IR_MOD]    = "MOD",
  [IR_IMOD]   = "IMOD",
  [IR_ADD]    = "ADD",
  [IR_SUB]    = "SUB",

  [IR_LSL]    = "LSL",
  [IR_LSR]    = "LSR",
  [IR_ASL]    = "ASL",
  [IR_ASR]    = "ASR",

  [IR_AND]    = "AND",
  [IR_XOR]    = "XOR",
  [IR_OR]     = "OR",

  [IR_CMP]    = "CMP",

  [IR_JMP]    = "JMP",
  [IR_JEQ]    = "JEQ",
  [IR_JNQ]    = "JNQ",
  [IR_JGT]    = "JGT",
  [IR_JGE]    = "JGE",
  [IR_JLT]    = "JLT",
  [IR_JLE]    = "JLE",
  [IR_JA]     = "JA",
  [IR_JB]     = "JB",
  [IR_JAE]    = "JAE",
  [IR_JBE]    = "JBE",

  [IR_COND]   = "COND",
  [IR_LOGENT] = "LOGENT",
  [IR_LOGEXT] = "LOGEXT",

  [IR_TABENT] = "TABENT",
  [IR_TABEXT] = "TABEXT",
  [IR_TABLIN] = "TABLIN",

  [IR_ASM]    = "ASM",
};

FILE* irout = 0;

IrInstr* IrInstrCreateEmpty(void){
  IrInstr* ir_instr     = malloc(sizeof(IrInstr));
  ir_instr->opcode      = IR_NOP;
  ir_instr->addr        = IR_ADDR_DIRECT;
  ir_instr->operand     = IR_OP_NO_OPERAND;
  ir_instr->obj_ref     = 0;
  ir_instr->string_ref  = 0;
  ir_instr->offset      = 0;
  ir_instr->reg_ref     = 0;
  ir_instr->depth       = 0;
  ir_instr->stack_alloc = 0;

  ir_instr_alloc++;

  return ir_instr;
}

void IrInstrDump(IrInstr* ir_instr){
  if(ir_instr->opcode == IR_FUNCT){
    fprintf(irout, "%s:", ir_instr->obj_ref->name);
  }
  else if(ir_instr->opcode == IR_LABEL){
    fprintf(irout, "%s%d:", default_base_text, ir_instr->offset);
  }
  else if(ir_instr->opcode == IR_INITLOOP){
    fprintf(irout, "%s%d:", default_base_initloop, ir_instr->offset);
  }
  else {
    if(InstrNumOfResults(ir_instr->opcode)) fprintf(irout, "   + ");
    else fprintf(irout, "     ");
    fprintf(irout, "%-2d %-6s", ir_instr->depth, ir_opcode_names[ir_instr->opcode]);
  }

  switch(ir_instr->operand){
  case IR_OP_NO_OPERAND: fprintf(irout, " "); break;
  case IR_OP_STACK_POP:  fprintf(irout, " "); break;
  case IR_OP_STACK_READ:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    fprintf(irout, "#%u,", ir_instr->depth - ir_instr->reg_ref - InstrGetDepth(ir_instr));
    if(ir_instr->offset >= 0) fprintf(irout, "+%d", +ir_instr->offset);
    else                      fprintf(irout, "-%d", -ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  case IR_OP_ARG:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    if(ir_instr->offset >= 0) fprintf(irout, "SP+%d", +ir_instr->offset);
    else                      fprintf(irout, "SP-%d", -ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  case IR_OP_OBJ:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    fprintf(irout, "&%s", ir_instr->obj_ref->name);
    if(ir_instr->offset < 0) fprintf(irout, "-%d", -ir_instr->offset);
    if(ir_instr->offset > 0) fprintf(irout, "+%d", +ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  case IR_OP_STRING:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    fprintf(irout, "%s%d", default_base_strings, ir_instr->string_ref);
    if(ir_instr->offset < 0) fprintf(irout, "-%d", -ir_instr->offset);
    if(ir_instr->offset > 0) fprintf(irout, "+%d", +ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  case IR_OP_ARITHM:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    fprintf(irout, "%d", ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  case IR_OP_LABEL:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    fprintf(irout, "%s%d", default_base_text, ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  case IR_OP_SWTAB:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    fprintf(irout, "%s%d", default_base_switch, ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  case IR_OP_INITLOOP:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    fprintf(irout, "%s%d", default_base_initloop, ir_instr->offset);
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "]");
  } break;
  }
}

void IrInstrDrop(IrInstr* ir_instr){
  free(ir_instr);
  ir_instr_free++;
}



Vector* curr_sequence    = 0;
Vector* ir_sequence      = 0;
Vector* postinc_sequence = 0;

void IrInit(void){
  irout = fopen("test/output.ir", "w");

  ir_sequence      = VectorInit();
  postinc_sequence = VectorInit();
  curr_sequence    = ir_sequence;
}

void IrFree(void){
  for(int i = 0; i < ir_sequence->size; i++)      IrInstrDrop(VectorGet(ir_sequence, i));
  for(int i = 0; i < postinc_sequence->size; i++) IrInstrDrop(VectorGet(postinc_sequence, i));

  VectorDrop(ir_sequence);
  VectorDrop(postinc_sequence);
  ir_sequence      = 0;
  postinc_sequence = 0;
  curr_sequence    = 0;

  fclose(irout);
}

void SwitchSequence(Vector* sequnce){
  curr_sequence = sequnce;
}


int InstrGetDepth(IrInstr* ir_instr){
  switch(ir_instr->opcode){
  case IR_NOP:
  case IR_FUNCT:
  case IR_LABEL:
  case IR_INITLOOP:
    return 0;

  case IR_PUSHB:
  case IR_PUSHW:
  case IR_PUSHL:
  case IR_VPUSHB:
  case IR_VPUSHW:
  case IR_VPUSHL:
    return +1;

  case IR_POP:
    return -1;
  case IR_VPOP:
    return -1;
  case IR_DUP:
    return +1;
  case IR_REVIV:
    return +1;

  case IR_STORB:
  case IR_STORW:
  case IR_STORL:
    return ir_instr->operand == IR_OP_STACK_POP ? -2 : -1;

  case IR_DERFB:
  case IR_DERFW:
  case IR_DERFL:
    return 0;

  case IR_FDRFB:
  case IR_FDRFW:
  case IR_FDRFL:
    return +1;

  case IR_ENTER:
  case IR_EXIT:
    return 0;
  case IR_CALL:
    return ir_instr->operand == IR_OP_STACK_POP ? -1 : 0;
  case IR_ALIGN:
  case IR_DEALGN:
    return 0;
  case IR_SETRET:
    return -1;
  case IR_GETRET:
    return +1;

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
    return 0;

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
    return ir_instr->operand == IR_OP_STACK_POP ? -1 : 0;

  case IR_CMP:
    return ir_instr->operand == IR_OP_STACK_POP ? -2 : -1;
  
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
    return ir_instr->operand == IR_OP_STACK_POP ? -1 : 0;

  case IR_LOGENT:
  case IR_LOGEXT:
    return 0;
  case IR_COND:
    return +1;

  case IR_TABENT:
  case IR_TABEXT:
  case IR_TABLIN:
    return 0;

  case IR_ASM:
    return 0;
  }

  return 0;
}

int InstrNumOfResults(IrOpcode opcode){
  switch(opcode){
  case IR_NOP:
  case IR_FUNCT:
  case IR_LABEL:
  case IR_INITLOOP:
    return 0;

  case IR_PUSHB:
  case IR_PUSHW:
  case IR_PUSHL:  
  case IR_VPUSHB:
  case IR_VPUSHW:
  case IR_VPUSHL:
    return 1;
  case IR_POP:
    return 0;
  case IR_VPOP:
    return 0;
  case IR_DUP:
    return 1;
  case IR_REVIV:
    return 1;
    
  case IR_STORB:
  case IR_STORW:
  case IR_STORL:
    return 0;

  case IR_DERFB:
  case IR_DERFW:
  case IR_DERFL:
    return 1;

  case IR_FDRFB:
  case IR_FDRFW:
  case IR_FDRFL:
    return 1;
  
  case IR_ENTER:
  case IR_EXIT:
  case IR_CALL:
  case IR_ALIGN:
  case IR_DEALGN:
    return 0;
  case IR_SETRET:
    return 0;
  case IR_GETRET:
    return 1;

  case IR_INC:
  case IR_DEC:
  case IR_NEG:
  case IR_NOT:
    return 1;

  case IR_SXBW:
  case IR_SXBL:
  case IR_SXWL:
  case IR_ZXBW:
  case IR_ZXBL:
  case IR_ZXWL:
    return 1;

  case IR_MUL:
  case IR_IMUL:
  case IR_DIV:
  case IR_IDIV:
  case IR_MOD:
  case IR_IMOD:
  case IR_ADD:
  case IR_SUB:
    return 1;

  case IR_LSL:
  case IR_LSR:
  case IR_ASL:
  case IR_ASR:
    return 1;

  case IR_AND:
  case IR_XOR:
  case IR_OR:
    return 1;

  case IR_CMP:
    return 0;

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
    return 0;

  case IR_LOGENT:
  case IR_LOGEXT:
    return 0;
  case IR_COND:
    return 1;

  case IR_TABENT:
  case IR_TABEXT:
  case IR_TABLIN:
    return 0;

  case IR_ASM:
    return 0;
  }

  return 0;
}

void IrCalculateDepth(void){
  IrInstr* ir_instr      = VectorGet(ir_sequence, 0);
  IrInstr* prev_ir_instr = 0;

  if(ir_instr == 0) return; // no instructions in this file

  ir_instr->depth = InstrGetDepth(ir_instr);

  for(int i = 1; i < ir_sequence->size; i++){
    ir_instr      = VectorGet(ir_sequence, i);
    prev_ir_instr = VectorGet(ir_sequence, i - 1);
    ir_instr->depth = prev_ir_instr->depth + InstrGetDepth(ir_instr);
  }
}

int InstrGetOperandDepth(int operation_index, int operand_position){
  IrInstr* operation = VectorGet(ir_sequence, operation_index);
  return operation->depth - operand_position - InstrGetDepth(operation);
}

int InstrFindOperand(int operation_index, int operand_position){
  IrInstr* operation = VectorGet(ir_sequence, operation_index);
  int target_depth = operation->depth - operand_position - InstrGetDepth(operation);
  
  int i = operation_index - 1;
  IrInstr* operand = 0;
  while(1){
    operand = VectorGet(ir_sequence, i);
    // if(InstrNumOfResults(operand->opcode) && operand->depth == target_depth) break;
    // if((operand->opcode == IR_FDRFB || operand->opcode == IR_FDRFW || operand->opcode == IR_FDRFL)
    //   && operand->depth - 1 == target_depth) break;
    if(operand->depth >= target_depth && operand->depth - InstrNumOfResults(operand->opcode) < target_depth) break;
    else i--;
  }

  return i;
}


IrInstr* InsertInstr(IrOpcode opcode, IrAddr addr, IrOperand operand, Obj* obj_ref, int string_ref, int offset, int reg_ref){
  IrInstr* ir_instr = IrInstrCreateEmpty();
  ir_instr->opcode     = opcode;
  ir_instr->addr       = addr;
  ir_instr->operand    = operand;
  ir_instr->obj_ref    = obj_ref;
  ir_instr->string_ref = string_ref;
  ir_instr->offset     = offset;
  ir_instr->reg_ref    = reg_ref;

  VectorPush(ir_sequence, ir_instr);

  return ir_instr;
}
IrInstr* InsertInstrNoOp(IrOpcode opcode){
  return InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, 0, 0, 0, 0);
}

IrInstr* InsertInstrStackPop(IrOpcode opcode){
  return InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_STACK_POP, 0, 0, 0, 0);
}

IrInstr* InsertInstrStackRead(IrOpcode opcode, IrAddr addr, int reg_ref, int offset){
  return InsertInstr(opcode, addr, IR_OP_STACK_READ, 0, 0, offset, reg_ref);
}

IrInstr* InsertInstrArg(IrOpcode opcode, IrAddr addr, int offset){
  return InsertInstr(opcode, addr, IR_OP_ARG, 0, 0, offset, 0);
}

IrInstr* InsertInstrObj(IrOpcode opcode, IrAddr addr, Obj* obj_ref, int offset){
  return InsertInstr(opcode, addr, IR_OP_OBJ, obj_ref, 0, offset, 0);
}

IrInstr* InsertInstrString(IrOpcode opcode, IrAddr addr, int string_ref, int offset){
  return InsertInstr(opcode, addr, IR_OP_STRING, 0, string_ref, offset, 0);
}

IrInstr* InsertInstrArithm(IrOpcode opcode, IrAddr addr, int offset){
  return InsertInstr(opcode, addr, IR_OP_ARITHM, 0, 0, offset, 0);
}

IrInstr* InsertInstrLabel(IrOpcode opcode, int label_index){
  return InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_LABEL, 0, 0, label_index, 0);
}

IrInstr* InsertInstrSwitchTab(IrOpcode opcode, int tab_index){
  return InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_SWTAB, 0, 0, tab_index, 0);
}

IrInstr* InsertInstrInitLoop(IrOpcode opcode, int label_index){
  return InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_INITLOOP, 0, 0, label_index, 0);
}

IrInstr* InsertNewFunct(Obj* obj_ref){
  return InsertInstr(IR_FUNCT, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, obj_ref, 0, 0, 0);
}

IrInstr* InsertNewLabel(int label_index){
  return InsertInstr(IR_LABEL, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, 0, 0, label_index, 0);
}

IrInstr* InsertNewInitLoop(int label_index){
  return InsertInstr(IR_INITLOOP, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, 0, 0, label_index, 0);
}

// void InsertNewSwitchTab(int tab_index){
//   InsertInstr(IR_TABENT, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, 0, 0, tab_index, 0);
// }
