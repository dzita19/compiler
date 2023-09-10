#ifndef _IR_H_
#define _IR_H_

#include "decl/declarations.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "assembler.h"
#include "abi.h"
#include "link_flow.h"
#include "util/vector.h"

typedef enum IrOpcode{
  IR_NOP,   // NOOP
  IR_FUNCT, // uses Obj*
  IR_LABEL, // uses offset

  IR_PUSHB,
  IR_PUSHW,
  IR_PUSHL,
  IR_VPUSHB,
  IR_VPUSHW,
  IR_VPUSHL,
  IR_POP,
  IR_VPOP,   // same as pop, but cannot be optimized out
  // doesn't kill actual register content - used when register content is assigned to result of ternary operator
  IR_DUP,
  IR_REVIV,    // revives value inside a register with no need for recalculations

  IR_STORB,
  IR_STORW,
  IR_STORL,

  IR_DERFB,
  IR_DERFW,
  IR_DERFL,
  IR_FDRFB, // fetch and deref
  IR_FDRFW, // fetch and deref
  IR_FDRFL, // fetch and deref
  
  IR_ENTER, // enter the function call
  IR_EXIT,  // exit  the function call
  IR_CALL,
  IR_ALIGN,
  IR_DEALGN,
  IR_SETRET,
  IR_GETRET, // fetch abi return value [NOOP]!!!

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
  IR_IMUL,
  IR_DIV,
  IR_IDIV,
  IR_MOD,
  IR_IMOD,
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
  IR_JA,
  IR_JB,
  IR_JAE,
  IR_JBE,

  IR_LOGENT, // sentinel - marks entry of a logic domain
  IR_LOGEXT, // sentinel - marks exit of a logic domain
  IR_COND,   // sentinel - stops invalid optimizations    [NOOP]!!!

  IR_TABENT,
  IR_TABEXT,
  IR_TABLIN,

  IR_ASM,

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
  IR_OP_SWTAB,
} IrOperand;

typedef struct StackAlloc StackAlloc;

typedef struct IrInstr{
  IrOpcode  opcode;
  IrAddr    addr;
  IrOperand operand;
  Obj* obj_ref;
  int  string_ref;
  int  offset;
  int  reg_ref; // used for STACK_READ
  int  depth; // stack depth
  StackAlloc* stack_alloc;
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
extern int  InstrNumOfResults(IrOpcode); // returns whether the result of the instruction is stored in a register
extern void IrCalculateDepth(void);

extern int  InstrGetOperandDepth(int operation_index, int operand_position);
extern int  InstrFindOperand(int operation_index, int operand_position);

extern IrInstr* InsertInstr(IrOpcode, IrAddr, IrOperand, Obj* obj_ref, int string_ref, int offset, int reg_ref);
extern IrInstr* InsertInstrNoOp(IrOpcode);
extern IrInstr* InsertInstrStackPop(IrOpcode);
extern IrInstr* InsertInstrStackRead(IrOpcode, IrAddr, int reg_ref, int offset);
extern IrInstr* InsertInstrArg(IrOpcode, IrAddr addr, int offset);
extern IrInstr* InsertInstrObj(IrOpcode, IrAddr, Obj* obj_ref, int offset);
extern IrInstr* InsertInstrString(IrOpcode, IrAddr, int string_ref, int offset);
extern IrInstr* InsertInstrArithm(IrOpcode, IrAddr, int offset);
extern IrInstr* InsertInstrLabel(IrOpcode, int label_index);
extern IrInstr* InsertInstrSwitchTab(IrOpcode, int tab_index);
extern IrInstr* InsertNewFunct(Obj* obj_ref);
extern IrInstr* InsertNewLabel(int label_index);
// extern void InsertNewSwitchTab(int tab_index);

#endif