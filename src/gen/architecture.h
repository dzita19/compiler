#ifndef _ARCHITECTURE_H_
#define _ARCHITECTURE_H_

typedef enum AsmInstr{
  ASM_HLT,
  ASM_RET,
  ASM_IRET,
  ASM_PUSHF,
  ASM_POPF,

  ASM_SXBW,
  ASM_SXBL,
  ASM_SXWL,
  ASM_ZXBW,
  ASM_ZXBL,
  ASM_ZXWL,

  ASM_NEG,
  ASM_INC,
  ASM_DEC,
  ASM_NOT,
  AST_TST,
  ASM_PUSHB,
  ASM_PUSHW,
  ASM_PUSHL,
  ASM_POPB,
  ASM_POPW,
  ASM_POPL,

  ASM_MOVB,
  ASM_MOVW,
  ASM_MOVL,
  
  ASM_ADD,
  ASM_SUB,
  ASM_MUL,
  ASM_DIV,
  ASM_MOD,
  ASM_CMP,
  ASM_AND,
  ASM_OR,
  ASM_XOR,
  ASM_ASL,
  ASM_ASR,
  ASM_LSL,
  ASM_LSR,

  ASM_JMP,
  ASM_JEQ,
  ASM_JNQ,
  ASM_JGT,
  ASM_JLT,
  ASM_JGE,
  ASM_JLE,
  ASM_JA,
  ASM_JB,
  ASM_JAE,
  ASM_JBE,
  ASM_CALL,
} AsmInstr;

typedef enum AsmInstrType{
  ASM_NOOP,   // nullary
  ASM_ONEOP,  // unary  - reg only
  ASM_TWOOP,  // binary - operand and reg
  ASM_BRANCH, // branch - reg or simple operand
} AsmInstrType;

typedef enum AsmAddress{
  ADDR_REGDIR,  // %reg, $4(%reg), $obj(%reg), $obj+4(%reg)
  ADDR_REGIND,  // (%reg), 4(%reg), obj(%reg), obj+4(%reg)
  ADDR_IMMED,   // $4, $obj, $obj+4
  ADDR_MEMDIR,  // 4, obj, obj+4,
} AsmAddress;

typedef enum AsmReg{
  REG_GP_COUNT = 8,
  REG_IP = REG_GP_COUNT,
  REG_SP,
  REG_BP,
} AsmReg;

#define REG_TO_REG 0
#define MEM_TO_REG 0
#define REG_TO_MEM 1

extern const char*  instr_names[];
extern AsmInstrType instr_types[];
extern const char*  reg_names[];

#endif