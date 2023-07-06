#ifndef _CODE_H_
#define _CODE_H_

#include "symtab/symtab.h"
#include "architecture.h"
#include <stdio.h>

extern FILE* ccout;

typedef enum AsmDir{
  DIR_SECTION,
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
extern void GenAsmData(int length, int data); // directive for data initialization
extern void GenAsmDataObj(int length, Obj* obj, int offset); // directive for data initialization
extern void GenAsmDataString(int length, int string_ref, int offset); // directive for data initialization
extern void GenAsmSkip(int length); // directive for location counter increment
extern void GenAsmAttrib(AsmDir attrib, const char* name); // directive for attributes
extern void GenAsmAsciz(const char* asciz);

extern void GenObjReference(Obj* obj, int offset);
// instructions
extern void GenAsmInstrNoop(AsmInstr instr);
extern void GenAsmInstrOneop(AsmInstr instr, int reg);
extern void GenAsmInstrTwoop(AsmInstr instr, AsmAddress address_mode, int src_reg, int src_offset, int dst_reg, int direction);
extern void GenAsmInstrTwoopObj(AsmInstr instr, AsmAddress address_mode, Obj* src_obj, int src_offset, int dst_reg, int direction);
extern void GenAsmInstrTwoopString(AsmInstr instr, AsmAddress address_mode, int string_ref, int src_offset, int dst_reg,  int direction);
extern void GenAsmInstrBranch(AsmInstr instr, int dst_offset);
extern void GenAsmInstrBranchObj(AsmInstr instr, Obj* obj, int dst_offset);
extern void GenAsmInstrBranchString(AsmInstr instr, int string_ref, int dst_offset);
extern void GenAsmInstrBranchLabel(AsmInstr instr, int label_index);

// load
extern void GenAsmLoadReg(AsmInstr instr, int src_reg, int dst_reg);
extern void GenAsmLoadAddress(AsmInstr instr, Obj* src_obj, int src_offset, int dst_reg);
extern void GenAsmLoadString(AsmInstr instr, int src_string_ref, int src_offset, int dst_reg);
extern void GenAsmLoadConst(AsmInstr instr, int src_const, int dst_reg);

extern void GenAsmLoadDerefAddress(AsmInstr instr, Obj* src_obj, int src_offset, int dst_reg);
extern void GenAsmLoadDerefString(AsmInstr instr, int src_string_ref, int src_offset, int dst_reg);
extern void GenAsmLoadDerefConst(AsmInstr instr, int src_const, int dst_reg);

// store
extern void GenAsmStoreDerefAddress(AsmInstr instr, Obj* src_obj, int src_offset, int dst_reg);
extern void GenAsmStoreDerefString(AsmInstr instr, int src_string_ref, int src_offset, int dst_reg);
extern void GenAsmStoreDerefConst(AsmInstr instr, int src_const, int dst_reg);

#endif