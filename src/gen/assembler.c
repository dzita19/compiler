#include "assembler.h"

#include "generator.h"

#define TAB_WIDTH 4
#define PRIMARY_WIDTH 12
#define SECONDARY_WIDTH (PRIMARY_WIDTH - TAB_WIDTH)

FILE* ccout = 0;

const char* dir_names[] = {
  [DIR_SECTION] = ".section",
  [DIR_END]     = ".end",
  [DIR_BYTE]    = ".byte",
  [DIR_WORD]    = ".word",
  [DIR_LONG]    = ".long",
  [DIR_ZERO]    = ".zero",
  [DIR_SKIP]    = ".skip",
  [DIR_GLOBL]   = ".global",
  [DIR_EXTRN]   = ".extern",
  [DIR_NOTYP]   = ".notyp",
  [DIR_FUNCT]   = ".funct",
  [DIR_OBJCT]   = ".objct",
  [DIR_ASCIZ]   = ".asciz",
};

// generates initial padding
static void GenAsmTab(int width){
  if(width > 8) width = 8;

  for(int i = 0; i < width; i++) fputc(' ', ccout);
}

// generates text with variable right padding
static void GenAsmTxt(const char* txt, int width){
  if(width > 16) width = 16;
  
  int i;
  for(i = 0; txt[i]; i++) fputc(txt[i], ccout);
  for(  ; i < width; i++) fputc(' ', ccout);
}

void GenAsmNewline(void){
  fprintf(ccout, "\n");
}

void GenAsmLine(const char* line){
  fprintf(ccout, "%s\n", line);
}

void GenAsmString(const char* string){
  fprintf(ccout, "%s", string);
}

// directives
void GenAsmSymbolLabel(const char* name){
  fprintf(ccout, "%s:\n", name);
}

void GenAsmTextLabel(const char* base, int i){
  fprintf(ccout, "%s%d:\n", base, i);
}

void GenAsmStringLabel(int string_ref){
  fprintf(ccout, "%s%d:\n", default_base_strings, string_ref);
}

void GenAsmSection(const char* name){
  GenAsmTxt(dir_names[DIR_SECTION], PRIMARY_WIDTH);
  fprintf(ccout, "%s", name);
  fprintf(ccout, "\n");
}

void GenAsmEnd(void){
  GenAsmTxt(dir_names[DIR_END], 0);
}

void GenAsmGlobal(const char* name){
  GenAsmTxt(dir_names[DIR_GLOBL], 0);
  fprintf(ccout, " %s\n", name);
}

void GenAsmExtern(const char* name){
  GenAsmTxt(dir_names[DIR_EXTRN], 0);
  fprintf(ccout, " %s\n", name);
}

void GenAsmData(int length, int data){
  int directive;
  if(length == 1)      directive = DIR_BYTE;
  else if(length == 2) directive = DIR_WORD;
  else if(length == 4) directive = DIR_LONG;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[directive], SECONDARY_WIDTH);
  fprintf(ccout, "%d\n", data);
}

void GenAsmDataObj(int length, Obj* obj, int offset){
  int directive;
  if(length == 1)      directive = DIR_BYTE;
  else if(length == 2) directive = DIR_WORD;
  else if(length == 4) directive = DIR_LONG;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[directive], SECONDARY_WIDTH);

  if((obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE) fprintf(ccout, "%s", obj->name);
  else {
    fprintf(ccout, "%s", default_base_objs);
    offset += obj->address;
  }

  if(offset > 0){
    fprintf(ccout, "+");
  }
  else if(offset < 0) {
    fprintf(ccout, "-");
    offset = -offset;
  }

  if(offset != 0) fprintf(ccout, "%d\n", offset);
  else fprintf(ccout, "\n");
}

void GenAsmDataString(int length, int string_ref, int offset){
  int directive;
  if(length == 1)      directive = DIR_BYTE;
  else if(length == 2) directive = DIR_WORD;
  else if(length == 4) directive = DIR_LONG;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[directive], SECONDARY_WIDTH);

  fprintf(ccout, "%s%d", default_base_strings, string_ref);

  if(offset > 0){
    fprintf(ccout, "+");
  }
  else if(offset < 0) {
    fprintf(ccout, "-");
    offset = -offset;
  }

  if(offset != 0) fprintf(ccout, "%d\n", offset);
  else fprintf(ccout, "\n");
}

void GenAsmDataLabel(int length, int label_index){
  int directive;
  if(length == 1)      directive = DIR_BYTE;
  else if(length == 2) directive = DIR_WORD;
  else if(length == 4) directive = DIR_LONG;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[directive], SECONDARY_WIDTH);

  fprintf(ccout, "%s%d\n", default_base_text, label_index);
}

void GenAsmSkip(int length){
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[DIR_ZERO], SECONDARY_WIDTH);
  fprintf(ccout, "%d\n", length);
}

void GenAsmAttrib(AsmDir attrib, const char* name){
  if(attrib < DIR_GLOBL || attrib > DIR_OBJCT) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[attrib], SECONDARY_WIDTH);
  fprintf(ccout, "%s\n", name);
}

void GenAsmAsciz(const char* asciz){
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[DIR_ASCIZ], SECONDARY_WIDTH);
  fprintf(ccout, "\"%s\"\n", asciz);
}



static void GenAsmOperandReg(int addressing, int reg_index, int offset){
  if(addressing == ASM_INDIRECT) fprintf(ccout, "[");

  fprintf(ccout, "%s", reg_names[reg_index]);

  if(offset > 0){
    fprintf(ccout, "+%d",  +offset);
  }
  else if(offset < 0){
    fprintf(ccout, "-%d", -offset);
  }

  if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
}

static void GenAsmOperandObj(int addressing, Obj* obj, int offset){
  if((obj->specifier & STORAGE_FETCH) == STORAGE_STATIC
      && (obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE){

    if(addressing == ASM_INDIRECT) fprintf(ccout, "[");
    fprintf(ccout, "%s", obj->name);
    if(offset > 0){
      fprintf(ccout, "+%d", +offset);
    }
    else if(offset < 0){
      fprintf(ccout, "-%d", -offset);
    }
    if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
  }
  else if((obj->specifier & STORAGE_FETCH) == STORAGE_STATIC
      && (obj->specifier & LINKAGE_FETCH) == LINKAGE_NONE){

    offset += obj->address;

    if(addressing == ASM_INDIRECT) fprintf(ccout, "[");
    fprintf(ccout, "%s", default_base_objs);
    if(offset > 0){
      fprintf(ccout, "+%d", +offset);
    }
    else if(offset < 0){
      fprintf(ccout, "-%d", -offset);
    }
    if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
  }
  else if((obj->specifier & STORAGE_FETCH) == STORAGE_AUTO){

    offset -= obj->address;
    if(addressing == ASM_INDIRECT) fprintf(ccout, "[");

    fprintf(ccout, "%s", reg_names[REG_BP]);
    if(offset > 0){
      fprintf(ccout, "+%d", +offset);
    }
    else if(offset < 0){
      fprintf(ccout, "-%d", -offset);
    }

    if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
  }
}

static void GenAsmOperandArithm(int addressing, int value){
  if(addressing == ASM_INDIRECT) fprintf(ccout, "[");

  // print offset
  if(value >= 0){
    fprintf(ccout, "%d",  +value);
  }
  else if(value < 0){
    fprintf(ccout, "-%d", -value);
  }

  if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
}

static void GenAsmOperandString(int addressing, int string_ref, int offset){
  if(addressing == ASM_INDIRECT) fprintf(ccout, "[");
    
  // print symbol
  fprintf(ccout, "%s%d", default_base_strings, string_ref);
  
  // print offset
  if(offset > 0){
    fprintf(ccout, "+%d", +offset);
  }
  else if(offset < 0){
    fprintf(ccout, "-%d", -offset);
  }

  if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
}

static void GenAsmOperandLabel(int addressing, int label_index, int offset){
  if(addressing == ASM_INDIRECT) fprintf(ccout, "[");

  fprintf(ccout, "%s%d", default_base_text, label_index);
  if(offset > 0){
    fprintf(ccout, "+%d", +offset);
  }
  else if(offset < 0){
    fprintf(ccout, "-%d", -offset);
  }

  if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
}

static void GenAsmOperandSwtab(int addressing, int swtab_index, int offset){
  if(addressing == ASM_INDIRECT) fprintf(ccout, "[");

  fprintf(ccout, "%s%d", default_base_switch, swtab_index);
  if(offset > 0){
    fprintf(ccout, "+%d", +offset);
  }
  else if(offset < 0){
    fprintf(ccout, "-%d", -offset);
  }

  if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
}

static void GenAsmOperandInitLoop(int addressing, int initloop_index, int offset){
  if(addressing == ASM_INDIRECT) fprintf(ccout, "[");

  fprintf(ccout, "%s%d", default_base_initloop, initloop_index);
  if(offset > 0){
    fprintf(ccout, "+%d", +offset);
  }
  else if(offset < 0){
    fprintf(ccout, "-%d", -offset);
  }

  if(addressing == ASM_INDIRECT) fprintf(ccout, "]");
}

static void GenAsmComma(void){
  fprintf(ccout, ", ");
}


void GenAsmInstrNoop(AsmInstr instr){
  if(instr_types[instr] != ASM_NOOP) return;
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  fprintf(ccout, "\n");
}

void GenAsmInstrOneop(AsmInstr instr, int reg){
  if(instr_types[instr] != ASM_ONEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  fprintf(ccout, "%s\n", reg_names[reg]);
}



void GenAsmInstrLoadReg(AsmInstr instr, int addressing, int src_reg, int src_offset, int dst_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandReg(addressing, src_reg, src_offset);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}

void GenAsmInstrLoadObj(AsmInstr instr, int addressing, Obj* src_obj, int src_offset, int dst_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandObj(addressing, src_obj, src_offset);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}

void GenAsmInstrLoadArithm(AsmInstr instr, int addressing, int src_value, int dst_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandArithm(addressing, src_value);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}

void GenAsmInstrLoadString(AsmInstr instr, int addressing, int src_string_ref, int src_offset, int dst_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandString(addressing, src_string_ref, src_offset);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}



void GenAsmInstrStoreReg(AsmInstr instr, int dst_reg, int dst_offset, int src_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandReg(ASM_DIRECT, src_reg, 0);
  GenAsmComma();
  GenAsmOperandReg(ASM_INDIRECT, dst_reg, dst_offset);
  fprintf(ccout, "\n");
}

void GenAsmInstrStoreObj(AsmInstr instr, Obj* dst_obj, int dst_offset, int src_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);  
  GenAsmOperandReg(ASM_DIRECT, src_reg, 0);
  GenAsmComma();
  GenAsmOperandObj(ASM_INDIRECT, dst_obj, dst_offset);
  fprintf(ccout, "\n");
}

void GenAsmInstrStoreArithm(AsmInstr instr, int dst_value, int src_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandReg(ASM_DIRECT, src_reg, 0);
  GenAsmComma();
  GenAsmOperandArithm(ASM_INDIRECT, dst_value);
  fprintf(ccout, "\n");
}

void GenAsmInstrStoreString(AsmInstr instr, int dst_string_ref, int dst_offset, int src_reg){
  if(instr_types[instr] != ASM_MOVEOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandReg(ASM_DIRECT, src_reg, 0);
  GenAsmComma();
  GenAsmOperandString(ASM_INDIRECT, dst_string_ref, dst_offset);
  fprintf(ccout, "\n");
}



void GenAsmInstrTwoopReg(AsmInstr instr, int addressing, int src_reg, int src_offset, int dst_reg){
  if(instr_types[instr] != ASM_TWOOP) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandReg(addressing, src_reg, src_offset);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}

void GenAsmInstrTwoopObj(AsmInstr instr, int addressing, Obj* src_obj, int src_offset, int dst_reg){
  if(instr_types[instr] != ASM_TWOOP) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandObj(addressing, src_obj, src_offset);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}

void GenAsmInstrTwoopArithm(AsmInstr instr, int addressing, int src_value, int dst_reg){
  if(instr_types[instr] != ASM_TWOOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandArithm(addressing, src_value);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}

void GenAsmInstrTwoopString(AsmInstr instr, int addressing, int src_string_ref, int src_offset, int dst_reg){
  if(instr_types[instr] != ASM_TWOOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandString(addressing, src_string_ref, src_offset);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}

void GenAsmInstrTwoopSwtab(AsmInstr instr, int src_swtab_index, int src_offset, int dst_reg){
  if(instr_types[instr] != ASM_TWOOP) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandSwtab(ASM_DIRECT, src_swtab_index, src_offset);
  GenAsmComma();
  GenAsmOperandReg(ASM_DIRECT, dst_reg, 0);
  fprintf(ccout, "\n");
}



void GenAsmInstrBranchReg(AsmInstr instr, int addressing, int dst_reg, int dst_offset){
  if(instr_types[instr] != ASM_BRANCH) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandReg(addressing, dst_reg, dst_offset);
  fprintf(ccout, "\n");
}

void GenAsmInstrBranchObj(AsmInstr instr, int addressing, Obj* dst_obj, int dst_offset){
  if(instr_types[instr] != ASM_BRANCH) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandObj(addressing, dst_obj, dst_offset);
  fprintf(ccout, "\n");
}

void GenAsmInstrBranchArithm(AsmInstr instr, int addressing, int dst_value){
  if(instr_types[instr] != ASM_BRANCH) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandArithm(addressing, dst_value);
  fprintf(ccout, "\n");
}

void GenAsmInstrBranchString(AsmInstr instr, int addressing, int dst_string_ref, int dst_offset){
  if(instr_types[instr] != ASM_BRANCH) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandString(addressing, dst_string_ref, dst_offset);
  fprintf(ccout, "\n");
}

void GenAsmInstrBranchLabel(AsmInstr instr, int addressing, int dst_label_index, int dst_offset){
  if(instr_types[instr] != ASM_BRANCH) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandLabel(addressing, dst_label_index, dst_offset);
  fprintf(ccout, "\n");
}

void GenAsmInstrBranchInitLoop(AsmInstr instr, int addressing, int dst_initloop_index, int dst_offset){
  if(instr_types[instr] != ASM_BRANCH) return;
  
  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  GenAsmOperandInitLoop(addressing, dst_initloop_index, dst_offset);
  fprintf(ccout, "\n");
}