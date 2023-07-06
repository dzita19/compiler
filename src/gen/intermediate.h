#ifndef _IR_H_
#define _IR_H_

#include "decl/declarations.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "assembler.h"
#include "abi.h"
#include "link_flow.h"
#include "resources.h"
#include "util/vector.h"

typedef enum IrOpcode{
  IR_NOP,   // NOOP
  IR_FUNCT, // uses Obj*
  IR_LABEL, // uses offset

  IR_PUSHB,
  IR_PUSHW,
  IR_PUSHL,
  IR_POP,
  IR_DUP,

  IR_STORB,
  IR_STORW,
  IR_STORL,

  IR_DERFB,
  IR_DERFW,
  IR_DERFL,
  
  IR_ENTER, // enter the function call
  IR_EXIT,  // exit  the function call
  IR_CALL,
  IR_ALIGN,
  IR_ABIRET, // fetch abi return value [NOOP]!!!

  IR_INC,
  IR_DEC,
  IR_NEG,
  IR_NOT,

  IR_SXBW,
  IR_SXBL,
  IR_SXWL,
  IR_ZXBW,
  IR_ZXBL,
  IR_ZXWL,

  IR_MUL,
  IR_DIV,
  IR_MOD,
  IR_ADD,
  IR_SUB,

  IR_LSL,
  IR_LSR,
  IR_ASL,
  IR_ASR,

  IR_AND,
  IR_XOR,
  IR_OR,

  IR_CMP,

  IR_JMP,
  IR_JEQ,
  IR_JNQ,
  IR_JGT,
  IR_JGE,
  IR_JLT,
  IR_JLE,

  IR_LOGENT, // sentinel - marks entry of a logic domain
  IR_LOGEXT, // sentinel - marks exit of a logic domain
  IR_COND,   // sentinel - stops invalid optimizations    [NOOP]!!!

} IrOpcode; // every instr has at most one operand

extern const char* ir_opcode_names[];

typedef enum IrAddr{
  IR_ADDR_DIRECT,
  IR_ADDR_INDIRECT,
} IrAddr;

typedef enum IrOperand{
  IR_OP_NO_OPERAND,
  IR_OP_STACK_POP,
  IR_OP_STACK_READ,
  IR_OP_ARG,
  IR_OP_OBJ,
  IR_OP_ARITHM,
  IR_OP_STRING,
  IR_OP_LABEL,
} IrOperand;

typedef struct IrInstr{
  IrOpcode  opcode;
  IrAddr    addr;
  IrOperand operand;
  Obj* obj_ref;
  int  string_ref;
  int  offset;
  int  depth; // stack depth
} IrInstr;

extern FILE* irout;

extern IrInstr* IrInstrCreateEmpty(void);
extern void IrInstrDump(IrInstr*);
extern void IrInstrDrop(IrInstr*);

extern Vector* curr_sequence;
extern Vector* ir_sequence;
extern Vector* postinc_sequence;

extern void IrInit(void);
extern void IrFree(void);
extern void SwitchSequence(Vector* sequence);

extern int  InstrGetDepth(IrInstr*);
extern void CalculateDepth(void);

extern void InsertInstr(IrOpcode, IrAddr, IrOperand, Obj* obj_ref, int string_ref, int offset);
extern void InsertInstrNoOp(IrOpcode);
extern void InsertInstrStackPop(IrOpcode);
extern void InsertInstrStackRead(IrOpcode, IrAddr, int offset);
extern void InsertInstrArg(IrOpcode, int offset);
extern void InsertInstrObj(IrOpcode, IrAddr, Obj* obj_ref, int offset);
extern void InsertInstrString(IrOpcode, IrAddr, int string_ref, int offset);
extern void InsertInstrArithm(IrOpcode, IrAddr, int offset);
extern void InsertInstrLabel(IrOpcode, int label_index);
extern void InsertNewFunct(Obj* obj_ref);
extern void InsertNewLabel(int label_index);

extern int IsGeneratingResult(IrOpcode); // returns whether the result of the instruction is stored in a register

#endif