#ifndef _CODE_H_
#define _CODE_H_

#include "symtab/symtab.h"
#include "architecture.h"
#include <stdio.h>

extern FILE* ccout;

typedef enum AsmDir{
  DIR_SECTION,
  DIR_END,
  DIR_BYTE,
  DIR_WORD,
  DIR_LONG,
  DIR_ZERO,
  DIR_SKIP,
  DIR_GLOBL,
  DIR_EXTRN,
  DIR_NOTYP,
  DIR_FUNCT,
  DIR_OBJCT,
  DIR_ASCIZ,
} AsmDir;

extern const char* dir_names[];

// general purpose
extern void GenAsmNewline(void);
extern void GenAsmLine(const char* line); // appends new line
extern void GenAsmString(const char* string); // doesn't append new line

// directives - with formating and newlines
extern void GenAsmSymbolLabel(const char* name);
extern void GenAsmTextLabel(const char* base, int label_index);
extern void GenAsmStringLabel(int i);
extern void GenAsmSection(const char* name); // directive for opening section
extern void GenAsmEnd(void);
extern void GenAsmGlobal(const char* name);
extern void GenAsmExtern(const char* name);
extern void GenAsmData(int length, int data); // directive for data initialization
extern void GenAsmDataObj(int length, Obj* obj, int offset); // directive for data initialization
extern void GenAsmDataString(int length, int string_ref, int offset); // directive for data initialization
extern void GenAsmDataLabel(int length, int label_index); // directive for data initialization
extern void GenAsmSkip(int length); // directive for location counter increment
extern void GenAsmAttrib(AsmDir attrib, const char* name); // directive for attributes
extern void GenAsmAsciz(const char* asciz);

#define ASM_DIRECT          0
#define ASM_INDIRECT        1
#define ASM_BRANCH_DIRECT   0
#define ASM_BRANCH_INDIRECT 1

// instructions
extern void GenAsmInstrNoop(AsmInstr instr);
extern void GenAsmInstrOneop(AsmInstr instr, int reg);

// load
extern void GenAsmInstrLoadReg(AsmInstr instr, int addressing, int src_reg, int src_offset, int dst_reg);
extern void GenAsmInstrLoadObj(AsmInstr instr, int addressing, Obj* src_obj, int src_offset, int dst_reg);
extern void GenAsmInstrLoadArithm(AsmInstr instr, int addressing, int src_value, int dst_reg);
extern void GenAsmInstrLoadString(AsmInstr instr, int addressing, int src_string_ref, int src_offset, int dst_reg);

// store
extern void GenAsmInstrStoreReg(AsmInstr instr, int dst_reg, int dst_offset, int src_reg);
extern void GenAsmInstrStoreObj(AsmInstr instr, Obj* dst_obj, int dst_offset, int src_reg);
extern void GenAsmInstrStoreArithm(AsmInstr instr, int dst_value, int src_reg);
extern void GenAsmInstrStoreString(AsmInstr instr, int dst_string_ref, int dst_offset, int src_reg);

// twoop general
extern void GenAsmInstrTwoopReg(AsmInstr instr, int addressing, int src_reg, int src_offset, int dst_reg);
extern void GenAsmInstrTwoopObj(AsmInstr instr, int addressing, Obj* src_obj, int src_offset, int dst_reg);
extern void GenAsmInstrTwoopArithm(AsmInstr instr, int addressing, int src_value, int dst_reg);
extern void GenAsmInstrTwoopString(AsmInstr instr, int addressing, int src_string_ref, int src_offset, int dst_reg);
extern void GenAsmInstrTwoopSwtab(AsmInstr instr, int src_swtab_index, int src_offset, int dst_reg);

// branch
extern void GenAsmInstrBranchReg(AsmInstr instr, int addressing, int dst_reg, int dst_offset);
extern void GenAsmInstrBranchObj(AsmInstr instr, int addressing, Obj* dst_obj, int dst_offset);
extern void GenAsmInstrBranchArithm(AsmInstr instr, int addressing, int dst_value);
extern void GenAsmInstrBranchString(AsmInstr instr, int addressing, int dst_string_ref, int dst_offset);
extern void GenAsmInstrBranchLabel(AsmInstr instr, int addressing, int dst_label_index, int dst_offset);
extern void GenAsmInstrBranchInitLoop(AsmInstr instr, int addressing, int dst_initloop_index, int dst_offset);

#endif