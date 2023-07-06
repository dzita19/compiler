#include "architecture.h"

const char*  instr_names[] = {
  [ASM_HLT]   = "hlt",
  [ASM_RET]   = "ret",
  [ASM_IRET]  = "iret",
  [ASM_PUSHF] = "pushf",
  [ASM_POPF]  = "popf",

  [ASM_SXBW]  = "sxbw",
  [ASM_SXBL]  = "sxbl",
  [ASM_SXWL]  = "sxwl",
  [ASM_ZXBW]  = "zxbw",
  [ASM_ZXBL]  = "zxbl",
  [ASM_ZXWL]  = "zxwl",

  [ASM_NEG]   = "neg",
  [ASM_INC]   = "inc",
  [ASM_DEC]   = "dec",
  [ASM_NOT]   = "not",
  [AST_TST]   = "tst",
  [ASM_PUSHB]  = "pushb",
  [ASM_PUSHW]  = "pushw",
  [ASM_PUSHL]  = "pushl",
  [ASM_POPB]   = "popb",
  [ASM_POPW]   = "popw",
  [ASM_POPL]   = "popl",

  [ASM_MOVB]  = "movb",
  [ASM_MOVW]  = "movw",
  [ASM_MOVL]  = "movl",
  
  [ASM_ADD]   = "add",
  [ASM_SUB]   = "sub",
  [ASM_MUL]   = "mul",
  [ASM_DIV]   = "div",
  [ASM_MOD]   = "mod",
  [ASM_CMP]   = "cmp",
  [ASM_AND]   = "and",
  [ASM_OR]    = "or",
  [ASM_XOR]   = "xor",
  [ASM_ASL]   = "asl",
  [ASM_ASR]   = "asr",
  [ASM_LSL]   = "lsl",
  [ASM_LSR]   = "lsr",

  [ASM_JMP]   = "jmp",
  [ASM_JEQ]   = "jeq",
  [ASM_JNQ]   = "jnq",
  [ASM_JGT]   = "jgt",
  [ASM_JLT]   = "jlt",
  [ASM_JGE]   = "jge",
  [ASM_JLE]   = "jle",
  [ASM_JA]    = "ja",
  [ASM_JB]    = "jb",
  [ASM_JAE]   = "jae",
  [ASM_JBE]   = "jbe",
  [ASM_CALL]  = "call",
};

AsmInstrType instr_types[] = {
  [ASM_HLT  ... ASM_POPF]  = ASM_NOOP,
  [ASM_SXBW ... ASM_POPL]   = ASM_ONEOP,
  [ASM_MOVB ... ASM_LSR]   = ASM_TWOOP,
  [ASM_JMP  ... ASM_CALL]  = ASM_BRANCH,
};

const char*  reg_names[] = {
  [0]       = "%reg0",
  [1]       = "%reg1",
  [2]       = "%reg2",
  [3]       = "%reg3",
  [4]       = "%reg4",
  [5]       = "%reg5",
  [6]       = "%reg6",
  [7]       = "%reg7",
  [REG_IP]  = "%rip",
  [REG_BP]  = "%rbp",
  [REG_SP]  = "%rsp",
};