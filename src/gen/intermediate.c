#include "intermediate.h"

#include "util/memory_safety.h"

const char* ir_opcode_names[] = {
  [IR_NOP]    = "NOP",
  [IR_FUNCT]  = "FUNCT",
  [IR_LABEL]  = "LABEL",

  [IR_PUSHB]  = "PUSHB",
  [IR_PUSHW]  = "PUSHW",
  [IR_PUSHL]  = "PUSHL",
  [IR_POP]    = "POP",
  [IR_DUP]    = "DUP",

  [IR_STORB]  = "STORB",
  [IR_STORW]  = "STORW",
  [IR_STORL]  = "STORL",

  [IR_DERFB]  = "DERFB",
  [IR_DERFW]  = "DERFW",
  [IR_DERFL]  = "DERFL",
  
  [IR_ENTER]  = "ENTER",
  [IR_EXIT]   = "EXIT",
  [IR_CALL]   = "CALL",
  [IR_ALIGN]  = "ALIGN",
  [IR_ABIRET] = "ABIRET",

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
  [IR_DIV]    = "DIV",
  [IR_MOD]    = "MOD",
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

  [IR_COND]   = "COND",
  [IR_LOGENT] = "LOGENT",
  [IR_LOGEXT] = "LOGEXT",
};

FILE* irout = 0;

IrInstr* IrInstrCreateEmpty(void){
  IrInstr* ir_instr = malloc(sizeof(IrInstr));
  ir_instr->opcode     = IR_NOP;
  ir_instr->addr       = IR_ADDR_DIRECT;
  ir_instr->operand    = IR_OP_NO_OPERAND;
  ir_instr->obj_ref    = 0;
  ir_instr->string_ref = 0;
  ir_instr->offset     = 0;
  ir_instr->depth      = 0;

  ir_instr_alloc++;

  return ir_instr;
}

void IrInstrDump(IrInstr* ir_instr){
  if(ir_instr->opcode == IR_FUNCT){
    fprintf(irout, "%s", ir_instr->obj_ref->name);
  }
  else if(ir_instr->opcode == IR_LABEL){
    fprintf(irout, "%s%d", default_base_strings, ir_instr->offset);
  }
  else {
    if(IsGeneratingResult(ir_instr->opcode)) fprintf(irout, "   + ");
    else fprintf(irout, "     ");
    fprintf(irout, "%-2d %-6s", ir_instr->depth, ir_opcode_names[ir_instr->opcode]);
  }

  switch(ir_instr->operand){
  case IR_OP_NO_OPERAND: fprintf(irout, " "); break;
  case IR_OP_STACK_POP:  fprintf(irout, " "); break;
  case IR_OP_STACK_READ:{
    fprintf(irout, " ");
    if(ir_instr->addr == IR_ADDR_INDIRECT) fprintf(irout, "[");
    // for(int i = 0; i < ir_instr->offset + 1; i++) fprintf(irout, "#");
    fprintf(irout, "#%u", ir_instr->depth - ir_instr->offset - InstrGetDepth(ir_instr));
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
    fprintf(irout, "%s%d", default_base_strings, ir_instr->offset);
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
    return 0;

  case IR_PUSHB:
  case IR_PUSHW:
  case IR_PUSHL:
    return +1;

  case IR_POP:
    return -1;
  case IR_DUP:
    return +1;

  case IR_STORB:
  case IR_STORW:
  case IR_STORL:
    return ir_instr->operand == IR_OP_STACK_POP ? -2 : -1;

  case IR_DERFB:
  case IR_DERFW:
  case IR_DERFL:
    return 0;

  case IR_ENTER:
  case IR_EXIT:
    return 0;
  case IR_CALL:
    return ir_instr->operand == IR_OP_STACK_POP ? -1 : 0;
  case IR_ALIGN:
    return 0;
  case IR_ABIRET:
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
  case IR_DIV:
  case IR_MOD:
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
    return 0;

  case IR_LOGENT:
  case IR_LOGEXT:
    return 0;
  case IR_COND:
    return +1;
  }

  return 0;
}

void CalculateDepth(void){
  IrInstr* ir_instr      = VectorGet(ir_sequence, 0);
  IrInstr* prev_ir_instr = 0;
  ir_instr->depth = InstrGetDepth(ir_instr);

  for(int i = 1; i < ir_sequence->size; i++){
    ir_instr      = VectorGet(ir_sequence, i);
    prev_ir_instr = VectorGet(ir_sequence, i - 1);
    ir_instr->depth = prev_ir_instr->depth + InstrGetDepth(ir_instr);
  }
}


void InsertInstr(IrOpcode opcode, IrAddr addr, IrOperand operand, Obj* obj_ref, int string_ref, int offset){
  IrInstr* ir_instr = IrInstrCreateEmpty();
  ir_instr->opcode     = opcode;
  ir_instr->addr       = addr;
  ir_instr->operand    = operand;
  ir_instr->obj_ref    = obj_ref;
  ir_instr->string_ref = string_ref;
  ir_instr->offset     = offset;

  VectorPush(ir_sequence, ir_instr);
}
void InsertInstrNoOp(IrOpcode opcode){
  InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, 0, 0, 0);
}

void InsertInstrStackPop(IrOpcode opcode){
  InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_STACK_POP, 0, 0, 0);
}

void InsertInstrStackRead(IrOpcode opcode, IrAddr addr, int offset){
  InsertInstr(opcode, addr, IR_OP_STACK_READ, 0, 0, offset);
}

void InsertInstrArg(IrOpcode opcode, int offset){
  InsertInstr(opcode, IR_ADDR_INDIRECT, IR_OP_ARG, 0, 0, offset);
}

void InsertInstrObj(IrOpcode opcode, IrAddr addr, Obj* obj_ref, int offset){
  InsertInstr(opcode, addr, IR_OP_OBJ, obj_ref, 0, offset);
}

void InsertInstrString(IrOpcode opcode, IrAddr addr, int string_ref, int offset){
  InsertInstr(opcode, addr, IR_OP_STRING, 0, string_ref, offset);
}

void InsertInstrArithm(IrOpcode opcode, IrAddr addr, int offset){
  InsertInstr(opcode, addr, IR_OP_ARITHM, 0, 0, offset);
}

void InsertInstrLabel(IrOpcode opcode, int label_index){
  InsertInstr(opcode, IR_ADDR_DIRECT, IR_OP_LABEL, 0, 0, label_index);
}

void InsertNewFunct(Obj* obj_ref){
  InsertInstr(IR_FUNCT, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, obj_ref, 0, 0);
}

void InsertNewLabel(int label_index){
  InsertInstr(IR_LABEL, IR_ADDR_DIRECT, IR_OP_NO_OPERAND, 0, 0, label_index);
}

int IsGeneratingResult(IrOpcode opcode){
  switch(opcode){
  case IR_NOP:
  case IR_FUNCT:
  case IR_LABEL:
    return 0;

  case IR_PUSHB:
  case IR_PUSHW:
  case IR_PUSHL:  
    return 1;
  case IR_POP:
    return 0;
  case IR_DUP:
    return 1;

  case IR_STORB:
  case IR_STORW:
  case IR_STORL:
    return 0;

  case IR_DERFB:
  case IR_DERFW:
  case IR_DERFL:
    return 1;
  
  case IR_ENTER:
  case IR_EXIT:
  case IR_CALL:
  case IR_ALIGN:
    return 0;
  case IR_ABIRET:
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
  case IR_DIV:
  case IR_MOD:
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
    return 0;

  case IR_LOGENT:
  case IR_LOGEXT:
    return 0;
  case IR_COND:
    return 1;
  }

  return 0;
}