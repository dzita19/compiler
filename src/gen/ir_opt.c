#include "ir_opt.h"


static void RecalculateDepth(int start_index, int end_index){
  IrInstr* curr_instr = VectorGet(ir_sequence, start_index);
  IrInstr* prev_instr = 0;
  if(start_index > 0) {
    prev_instr = VectorGet(ir_sequence, start_index - 1);

    if(curr_instr->operand == IR_OP_STACK_READ){
      int target_depth    = curr_instr->depth - curr_instr->reg_ref - InstrGetDepth(curr_instr);
      curr_instr->depth   = prev_instr->depth + InstrGetDepth(curr_instr);
      curr_instr->reg_ref = curr_instr->depth - target_depth - InstrGetDepth(curr_instr);
    }
    else{
      curr_instr->depth = prev_instr->depth + InstrGetDepth(curr_instr);
    }
  }
  else curr_instr->depth = 0;


  for(int i = start_index + 1; i < end_index; i++){
    prev_instr = curr_instr;
    curr_instr = VectorGet(ir_sequence, i);
    
    if(curr_instr->operand == IR_OP_STACK_READ){
      int target_depth    = curr_instr->depth - curr_instr->reg_ref - InstrGetDepth(curr_instr);
      curr_instr->depth   = prev_instr->depth + InstrGetDepth(curr_instr);
      curr_instr->reg_ref = curr_instr->depth - target_depth - InstrGetDepth(curr_instr);
    }
    else{
      curr_instr->depth = prev_instr->depth + InstrGetDepth(curr_instr);
    }
  }
}

static int PushDupOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // dup

  if(operation->opcode  != IR_DUP)          return 0;
  if(operation->operand != IR_OP_STACK_POP) return 0;
  if(operation->addr    != IR_ADDR_DIRECT)  return 0;
  
  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHB
    && operand->opcode != IR_PUSHW
    && operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  // if(operand->addr != IR_ADDR_DIRECT) return 0;

  // optimize
  operation->opcode     = operand->opcode;
  operation->addr       = operand->addr;
  operation->operand    = operand->operand;
  operation->obj_ref    = operand->obj_ref;
  operation->string_ref = operand->string_ref;
  operation->offset     = operand->offset;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}

static int PushDerefOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode != IR_DERFB 
    && operation->opcode != IR_DERFW 
    && operation->opcode != IR_DERFL) return 0;

  if(operation->operand != IR_OP_STACK_POP) return 0;
  if(operation->addr    != IR_ADDR_DIRECT)  return 0;

  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  if(operand->addr != IR_ADDR_DIRECT) return 0;

  // optimize
  operation->opcode     = IR_PUSHB + (operation->opcode - IR_DERFB);
  operation->addr       = IR_ADDR_INDIRECT;
  operation->operand    = operand->operand;
  operation->obj_ref    = operand->obj_ref;
  operation->string_ref = operand->string_ref;
  operation->offset     = operand->offset;

  // clear operand
  operand->opcode       = IR_NOP;
  operand->addr         = IR_ADDR_DIRECT;
  operand->operand      = IR_OP_NO_OPERAND;
  operand->obj_ref      = 0;
  operand->string_ref   = 0;
  operand->offset       = 0;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}

static int PushFderfOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode != IR_FDRFB 
    && operation->opcode != IR_FDRFW 
    && operation->opcode != IR_FDRFL) return 0;

  if(operation->operand != IR_OP_STACK_POP) return 0;
  if(operation->addr    != IR_ADDR_DIRECT)  return 0;

  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  if(operand->addr == IR_ADDR_DIRECT) {
    // operand
    operand->opcode       = IR_VPUSHB + (operation->opcode - IR_FDRFB);
    operand->addr         = IR_ADDR_INDIRECT;
    operand->operand      = operand->operand;
    operand->obj_ref      = operand->obj_ref;
    operand->string_ref   = operand->string_ref;
    operand->offset       = operand->offset;

    // operation
    operation->opcode     = IR_PUSHL;
    operation->addr       = IR_ADDR_DIRECT;
    operation->operand    = operand->operand;
    operation->obj_ref    = operand->obj_ref;
    operation->string_ref = operand->string_ref;
    operation->offset     = operand->offset;

    RecalculateDepth(operand_index, current_instr);
  }
  else{
    // operand becomes VPUSH - it's a push that cannot be optimized out!!!
    operand->opcode       = IR_VPUSHB + (operation->opcode - IR_FDRFB);
    operand->addr         = operand->addr;
    operand->operand      = operand->operand;
    operand->obj_ref      = operand->obj_ref;
    operand->string_ref   = operand->string_ref;
    operand->offset       = operand->offset;

    RecalculateDepth(operand_index, current_instr);
  }

  return 1;
}

static int PushArithmOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode < IR_MUL || operation->opcode > IR_CMP) return 0;
  if(operation->operand != IR_OP_STACK_POP) return 0;
  if(operation->addr    != IR_ADDR_DIRECT) return 0;

  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHB
    && operand->opcode != IR_PUSHW
    && operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  // optimize
  operation->addr       = operand->addr;
  operation->operand    = operand->operand;
  operation->obj_ref    = operand->obj_ref;
  operation->string_ref = operand->string_ref;
  operation->offset     = operand->offset;

  // clear operand
  operand->opcode       = IR_NOP;
  operand->addr         = IR_ADDR_DIRECT;
  operand->operand      = IR_OP_NO_OPERAND;
  operand->obj_ref      = 0;
  operand->string_ref   = 0;
  operand->offset       = 0;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}

static int PushAddOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode  != IR_ADD) return 0;
  if(operation->operand != IR_OP_ARITHM) return 0;
  if(operation->addr    != IR_ADDR_DIRECT) return 0;

  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  if(operand->addr != IR_ADDR_DIRECT) return 0;

  // optimize operand
  operand->offset      += operation->offset;

  // clear operation
  operation->opcode     = IR_NOP;
  operation->addr       = IR_ADDR_DIRECT;
  operation->operand    = IR_OP_NO_OPERAND;
  operation->obj_ref    = 0;
  operation->string_ref = 0;
  operation->offset     = 0;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}

static int PushStoreOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode != IR_STORB 
    && operation->opcode != IR_STORW 
    && operation->opcode != IR_STORL) return 0;

  if(operation->operand != IR_OP_STACK_POP) return 0;

  int operand_index = InstrFindOperand(current_instr, 1); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  if(operand->addr != IR_ADDR_DIRECT) return 0;

  // optimize
  operation->addr       = IR_ADDR_INDIRECT;
  operation->operand    = operand->operand;
  operation->obj_ref    = operand->obj_ref;
  operation->string_ref = operand->string_ref;
  operation->offset     = operand->offset;

  // clear operand
  operand->opcode       = IR_NOP;
  operand->addr         = IR_ADDR_DIRECT;
  operand->operand      = IR_OP_NO_OPERAND;
  operand->obj_ref      = 0;
  operand->string_ref   = 0;
  operand->offset       = 0;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}

static int PushRegOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode != IR_PUSHB 
    && operation->opcode != IR_PUSHW 
    && operation->opcode != IR_PUSHL) return 0;

  if(operation->operand != IR_OP_STACK_READ) return 0;
  if(operation->addr    != IR_ADDR_INDIRECT) return 0;

  int operand_index = InstrFindOperand(current_instr, operation->reg_ref); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  if(operand->addr == IR_ADDR_DIRECT) {
    // optimize
    operation->addr       = IR_ADDR_INDIRECT;
    operation->operand    = operand->operand;
    operation->obj_ref    = operand->obj_ref;
    operation->string_ref = operand->string_ref;
    operation->offset     = operation->offset + operand->offset;

    // don't clear operand

    RecalculateDepth(operand_index, current_instr);
  }
  else{
    // make operand volatile
    operand->opcode     = IR_VPUSHL;
    operand->addr       = operand->addr;
    operand->operand    = operand->operand;
    operand->obj_ref    = operand->obj_ref;
    operand->string_ref = operand->string_ref;
    operand->offset     = operand->offset;

    RecalculateDepth(operand_index, current_instr);
  }

  return 1;
}

static int StoreRegOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode != IR_STORB 
    && operation->opcode != IR_STORW 
    && operation->opcode != IR_STORL) return 0;

  if(operation->operand != IR_OP_STACK_READ) return 0;
  if(operation->addr    != IR_ADDR_INDIRECT) return 0;

  int operand_index = InstrFindOperand(current_instr, operation->reg_ref); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  if(operand->addr == IR_ADDR_DIRECT){
    // optimize
    operation->addr       = IR_ADDR_INDIRECT;
    operation->operand    = operand->operand;
    operation->obj_ref    = operand->obj_ref;
    operation->string_ref = operand->string_ref;
    operation->offset     = operation->offset + operand->offset;

    // don't clear operand

    RecalculateDepth(operand_index, current_instr);
  }
  else{
    // make operand volatile
    operand->opcode     = IR_VPUSHL;
    operand->addr       = operand->addr;
    operand->operand    = operand->operand;
    operand->obj_ref    = operand->obj_ref;
    operand->string_ref = operand->string_ref;
    operand->offset     = operand->offset;

    RecalculateDepth(operand_index, current_instr);
  }

  return 1;
}

static int PushPopOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode  != IR_POP) return 0;
  if(operation->operand != IR_OP_STACK_POP) return 0;
  if(operation->addr    != IR_ADDR_DIRECT) return 0;

  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHB
    && operand->opcode != IR_PUSHW
    && operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  // if(operand->addr != IR_ADDR_DIRECT) return 0;

  // optimize
  operation->opcode     = IR_NOP;
  operation->addr       = IR_ADDR_DIRECT;
  operation->operand    = IR_OP_NO_OPERAND;
  operation->obj_ref    = 0;
  operation->string_ref = 0;
  operation->offset     = 0;

  // don't clear operand
  operand->opcode       = IR_NOP;
  operand->addr         = IR_ADDR_DIRECT;
  operand->operand      = IR_OP_NO_OPERAND;
  operand->obj_ref      = 0;
  operand->string_ref   = 0;
  operand->offset       = 0;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}

static int PushCastPopOpt(int current_instr){
  IrInstr* pop_instr = VectorGet(ir_sequence, current_instr); // arithm

  if(pop_instr->opcode  != IR_POP) return 0;
  if(pop_instr->operand != IR_OP_STACK_POP) return 0;
  if(pop_instr->addr    != IR_ADDR_DIRECT) return 0;

  int cast_instr_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* cast_instr  = VectorGet(ir_sequence, cast_instr_index);

  if(cast_instr->opcode != IR_SXBW
    && cast_instr->opcode != IR_SXBL
    && cast_instr->opcode != IR_SXWL
    && cast_instr->opcode != IR_ZXBW
    && cast_instr->opcode != IR_ZXBL
    && cast_instr->opcode != IR_ZXWL) return 0;

  if(cast_instr->operand != IR_OP_STACK_POP) return 0;
  if(cast_instr->addr    != IR_ADDR_DIRECT)  return 0;

  int push_instr_index = InstrFindOperand(cast_instr_index, 0);
  IrInstr* push_instr  = VectorGet(ir_sequence, push_instr_index);

  if(push_instr->opcode != IR_PUSHB
    && push_instr->opcode != IR_PUSHW
    && push_instr->opcode != IR_PUSHL) return 0;

  if(push_instr->operand != IR_OP_OBJ
    && push_instr->operand != IR_OP_STRING
    && push_instr->operand != IR_OP_ARITHM) return 0;

  // if(push_instr->addr != IR_ADDR_DIRECT) return 0;

  // clear all
  pop_instr->opcode      = IR_NOP;
  pop_instr->addr        = IR_ADDR_DIRECT;
  pop_instr->operand     = IR_OP_NO_OPERAND;
  pop_instr->obj_ref     = 0;
  pop_instr->string_ref  = 0;
  pop_instr->offset      = 0;

  cast_instr->opcode     = IR_NOP;
  cast_instr->addr       = IR_ADDR_DIRECT;
  cast_instr->operand    = IR_OP_NO_OPERAND;
  cast_instr->obj_ref    = 0;
  cast_instr->string_ref = 0;
  cast_instr->offset     = 0;

  push_instr->opcode     = IR_NOP;
  push_instr->addr       = IR_ADDR_DIRECT;
  push_instr->operand    = IR_OP_NO_OPERAND;
  push_instr->obj_ref    = 0;
  push_instr->string_ref = 0;
  push_instr->offset     = 0;

  RecalculateDepth(push_instr_index, current_instr);

  return 1;
}

static int PushDerefPopOpt(int current_instr){
  IrInstr* pop_instr = VectorGet(ir_sequence, current_instr); // arithm

  if(pop_instr->opcode  != IR_POP) return 0;
  if(pop_instr->operand != IR_OP_STACK_POP) return 0;
  if(pop_instr->addr    != IR_ADDR_DIRECT) return 0;

  int deref_instr_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* deref_instr  = VectorGet(ir_sequence, deref_instr_index);

  if(deref_instr->opcode != IR_DERFB
    && deref_instr->opcode != IR_DERFW
    && deref_instr->opcode != IR_DERFL) return 0;

  if(deref_instr->operand != IR_OP_STACK_POP) return 0;
  if(deref_instr->addr    != IR_ADDR_DIRECT)  return 0;

  int push_instr_index = InstrFindOperand(deref_instr_index, 0);
  IrInstr* push_instr  = VectorGet(ir_sequence, push_instr_index);

  if(push_instr->opcode != IR_PUSHB
    && push_instr->opcode != IR_PUSHW
    && push_instr->opcode != IR_PUSHL) return 0;

  if(push_instr->operand != IR_OP_OBJ
    && push_instr->operand != IR_OP_STRING
    && push_instr->operand != IR_OP_ARITHM) return 0;

  // if(push_instr->addr != IR_ADDR_DIRECT) return 0;

  // clear all
  pop_instr->opcode      = IR_NOP;
  pop_instr->addr        = IR_ADDR_DIRECT;
  pop_instr->operand     = IR_OP_NO_OPERAND;
  pop_instr->obj_ref     = 0;
  pop_instr->string_ref  = 0;
  pop_instr->offset      = 0;

  deref_instr->opcode     = IR_NOP;
  deref_instr->addr       = IR_ADDR_DIRECT;
  deref_instr->operand    = IR_OP_NO_OPERAND;
  deref_instr->obj_ref    = 0;
  deref_instr->string_ref = 0;
  deref_instr->offset     = 0;

  push_instr->opcode      = IR_NOP;
  push_instr->addr        = IR_ADDR_DIRECT;
  push_instr->operand     = IR_OP_NO_OPERAND;
  push_instr->obj_ref     = 0;
  push_instr->string_ref  = 0;
  push_instr->offset      = 0;

  RecalculateDepth(push_instr_index, current_instr);

  return 1;
}

static int RetPopOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode  != IR_POP) return 0;
  if(operation->operand != IR_OP_STACK_POP) return 0;
  if(operation->addr    != IR_ADDR_DIRECT) return 0;

  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_GETRET) return 0;

  // optimize
  operation->opcode     = IR_NOP;
  operation->addr       = IR_ADDR_DIRECT;
  operation->operand    = IR_OP_NO_OPERAND;
  operation->obj_ref    = 0;
  operation->string_ref = 0;
  operation->offset     = 0;

  // don't clear operand
  operand->opcode       = IR_NOP;
  operand->addr         = IR_ADDR_DIRECT;
  operand->operand      = IR_OP_NO_OPERAND;
  operand->obj_ref      = 0;
  operand->string_ref   = 0;
  operand->offset       = 0;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}

static int PushCallOpt(int current_instr){
  IrInstr* operation = VectorGet(ir_sequence, current_instr); // arithm

  if(operation->opcode  != IR_CALL)         return 0;
  if(operation->operand != IR_OP_STACK_POP) return 0;
  if(operation->addr    != IR_ADDR_DIRECT)  return 0;

  int operand_index = InstrFindOperand(current_instr, 0); // push
  IrInstr* operand  = VectorGet(ir_sequence, operand_index);

  if(operand->opcode != IR_PUSHL) return 0;

  if(operand->operand != IR_OP_OBJ
    && operand->operand != IR_OP_STRING
    && operand->operand != IR_OP_ARITHM) return 0;

  if(operand->addr != IR_ADDR_DIRECT) return 0;

  // optimize
  operation->addr       = IR_ADDR_DIRECT;
  operation->operand    = operand->operand;
  operation->obj_ref    = operand->obj_ref;
  operation->string_ref = operand->string_ref;
  operation->offset     = operand->offset;

  // clear operand
  operand->opcode       = IR_NOP;
  operand->addr         = IR_ADDR_DIRECT;
  operand->operand      = IR_OP_NO_OPERAND;
  operand->obj_ref      = 0;
  operand->string_ref   = 0;
  operand->offset       = 0;

  RecalculateDepth(operand_index, current_instr);

  return 1;
}


static int TryOptimization(int current_instr){
  if     (PushDupOpt(current_instr))      return 1;
  else if(PushDerefOpt(current_instr))    return 1;
  else if(PushFderfOpt(current_instr))    return 1;
  else if(PushArithmOpt(current_instr))   return 1;
  else if(PushAddOpt(current_instr))      return 1;
  else if(PushStoreOpt(current_instr))    return 1;
  else if(PushRegOpt(current_instr))      return 1;
  else if(StoreRegOpt(current_instr))     return 1;
  else if(PushPopOpt(current_instr))      return 1;
  else if(PushCastPopOpt(current_instr))  return 1;
  else if(PushDerefPopOpt(current_instr)) return 1;
  else if(PushCallOpt(current_instr))     return 1;
  else if(RetPopOpt(current_instr))       return 1;

  return 0;
}

void IrOptimize(void){
  static int current_instr = 0;
  while(current_instr < ir_sequence->size){
    if(!TryOptimization(current_instr)) current_instr++;
  }
}