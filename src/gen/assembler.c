#include "assembler.h"

#include "generator.h"
#include "symtab/static_val.h"

#define TAB_WIDTH 4
#define PRIMARY_WIDTH 12
#define SECONDARY_WIDTH (PRIMARY_WIDTH - TAB_WIDTH)

FILE* ccout = 0;

const char* dir_names[] = {
  [DIR_SECTION] = ".section",
  [DIR_BYTE]    = ".byte",
  [DIR_WORD]    = ".word",
  [DIR_LONG]    = ".long",
  [DIR_ZERO]    = ".zero",
  [DIR_SKIP]    = ".skip",
  [DIR_GLOBL]   = ".globl",
  [DIR_EXTRN]   = ".extrn",
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
  fprintf(ccout, "%s%04X:\n", base, i);
}

void GenAsmStringLabel(int string_ref){
  fprintf(ccout, "%s%04X:\n", default_base_strings, string_ref);
}

void GenAsmSection(const char* name){
  GenAsmTxt(dir_names[DIR_SECTION], PRIMARY_WIDTH);
  fprintf(ccout, "%s", name);
  fprintf(ccout, "\n");
}

void GenAsmData(int length, int data){
  int directive;
  if(length == 1)      directive = DIR_BYTE;
  else if(length == 2) directive = DIR_WORD;
  else if(length == 4) directive = DIR_LONG;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[directive], SECONDARY_WIDTH);
  fprintf(ccout, "0x%02X\n", data);
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

  if(offset != 0) fprintf(ccout, "0x%02X\n", offset);
  else fprintf(ccout, "\n");
}

void GenAsmDataString(int length, int string_ref, int offset){
  int directive;
  if(length == 1)      directive = DIR_BYTE;
  else if(length == 2) directive = DIR_WORD;
  else if(length == 4) directive = DIR_LONG;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(dir_names[directive], SECONDARY_WIDTH);

  fprintf(ccout, "%s%04X", default_base_strings, string_ref);

  if(offset > 0){
    fprintf(ccout, "+");
  }
  else if(offset < 0) {
    fprintf(ccout, "-");
    offset = -offset;
  }

  if(offset != 0) fprintf(ccout, "0x%02X\n", offset);
  else fprintf(ccout, "\n");
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

static void GenAsmOperand(AsmAddress addr_mode, StaticValKind target_mode, int reg, Obj* obj, int string_ref, int offset){
  if(target_mode == VAL_ARITHM){
    if(addr_mode == ADDR_IMMED) fprintf(ccout, "$");
    if(addr_mode == ADDR_REGDIR && offset != 0) fprintf(ccout, "$(");
    if(addr_mode == ADDR_REGIND) fprintf(ccout, "(");
    
    if(addr_mode == ADDR_REGDIR || addr_mode == ADDR_REGIND) {
      fprintf(ccout, "%s", reg_names[reg]);
      if(offset != 0) fprintf(ccout, ",");
    }
    else if(offset == 0) fprintf(ccout, "0x%02X", offset);

    // print offset
    if(offset > 0){
      fprintf(ccout, "0x%02X", offset);
    }
    else if(offset < 0){
      offset = -offset;
      fprintf(ccout, "-0x%02X", offset);
    }

    if(addr_mode == ADDR_REGDIR && offset != 0) fprintf(ccout, ")");
    if(addr_mode == ADDR_REGIND) fprintf(ccout, ")");
  }
  else if(target_mode == VAL_ADDRESS){
    if((obj->specifier & STORAGE_FETCH) == STORAGE_STATIC
        && (obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE){
      if(addr_mode == ADDR_IMMED) fprintf(ccout, "$");
      fprintf(ccout, "%s", obj->name);
      if(offset > 0){
        fprintf(ccout, "+0x%02X", +offset);
      }
      else if(offset < 0){
        fprintf(ccout, "-0x%02X", -offset);
      }
    }
    else if((obj->specifier & STORAGE_FETCH) == STORAGE_STATIC
        && (obj->specifier & LINKAGE_FETCH) == LINKAGE_NONE){
      offset += obj->address;

      if(addr_mode == ADDR_IMMED) fprintf(ccout, "$");
      fprintf(ccout, "%s", default_base_objs);
      if(offset > 0){
        fprintf(ccout, "+0x%02X", +offset);
      }
      else if(offset < 0){
        fprintf(ccout, "-0x%02X", -offset);
      }
    }
    else if((obj->specifier & STORAGE_FETCH) == STORAGE_AUTO){
      offset -= obj->address;
      if(addr_mode == ADDR_IMMED && offset != 0) fprintf(ccout, "$(");
      if(addr_mode == ADDR_MEMDIR) fprintf(ccout, "(");

      fprintf(ccout, "%s", reg_names[REG_BP]);
      if(offset != 0) fprintf(ccout, ",");
      if(offset > 0){
        fprintf(ccout, "0x%02X", +offset);
      }
      else if(offset < 0){
        fprintf(ccout, "-0x%02X", -offset);
      }

      if(addr_mode == ADDR_IMMED && offset != 0) fprintf(ccout, ")");
      if(addr_mode == ADDR_MEMDIR) fprintf(ccout, ")");
    }
  }
  else if(target_mode == VAL_STRING){
    if(addr_mode != ADDR_IMMED && addr_mode != ADDR_MEMDIR) return;
    if(addr_mode == ADDR_IMMED) fprintf(ccout, "$");
    
    // print symbol
    fprintf(ccout, "%s%04X", default_base_strings, string_ref);
    
    // print offset
    if(offset > 0){
      fprintf(ccout, "+0x%02X", +offset);
    }
    else if(offset < 0){
      fprintf(ccout, "-0x%02X", -offset);
    }
  }
}

void GenAsmInstrTwoop(AsmInstr instr, AsmAddress address_mode, 
    int src_reg, int src_offset, int dst_reg, int direction){

  if(instr_types[instr] != ASM_TWOOP) return;
  if(direction == REG_TO_MEM && 
    (instr != ASM_MOVB && instr != ASM_MOVL && instr != ASM_MOVW)) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  if(direction == REG_TO_MEM){ // dst and source are reversed
    fprintf(ccout, "%s, ", reg_names[dst_reg]);
  }
  
  GenAsmOperand(address_mode, VAL_ARITHM, src_reg, 0, 0, src_offset);

  if(direction == MEM_TO_REG){ // dst and source are NOT reversed
    fprintf(ccout, ", %s", reg_names[dst_reg]);
  }

  fprintf(ccout, "\n");
}

void GenAsmInstrTwoopObj(AsmInstr instr, AsmAddress address_mode, 
    Obj* src_obj, int src_offset, int dst_reg, int direction){

  if(instr_types[instr] != ASM_TWOOP) return;
  if(direction == REG_TO_MEM && 
    (instr != ASM_MOVB && instr != ASM_MOVL && instr != ASM_MOVW)) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  if(direction == REG_TO_MEM){ // dst and source are reversed
    fprintf(ccout, "%s, ", reg_names[dst_reg]);
  }
  
  GenAsmOperand(address_mode, VAL_ADDRESS, 0, src_obj, 0, src_offset);

  if(direction == MEM_TO_REG){ // dst and source are NOT reversed
    fprintf(ccout, ", %s", reg_names[dst_reg]);
  }

  fprintf(ccout, "\n");
}

void GenAsmInstrTwoopString(AsmInstr instr, AsmAddress address_mode, 
    int string_ref, int src_offset, int dst_reg, int direction){
      
  if(instr_types[instr] != ASM_TWOOP) return;
  if(direction == REG_TO_MEM && 
    (instr != ASM_MOVB && instr != ASM_MOVL && instr != ASM_MOVW)) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);
  if(direction == REG_TO_MEM){ // dst and source are reversed
    fprintf(ccout, "%s, ", reg_names[dst_reg]);
  }
  
  GenAsmOperand(address_mode, VAL_STRING, 0, 0, string_ref, src_offset);

  if(direction == MEM_TO_REG){ // dst and source are NOT reversed
    fprintf(ccout, ", %s", reg_names[dst_reg]);
  }

  fprintf(ccout, "\n");
}

void GenAsmInstrBranchLabel(AsmInstr instr, int label_index){
  if(instr_types[instr] != ASM_BRANCH) return;

  GenAsmTab(TAB_WIDTH);
  GenAsmTxt(instr_names[instr], SECONDARY_WIDTH);

  fprintf(ccout, "%s%04X\n", default_base_text, label_index);
}

void GenAsmMoveStackFrameToReg(int size, int src_offset, int dst_reg){
  AsmInstr instr = 0;
  if(size == 1) instr = ASM_MOVB;
  if(size == 2) instr = ASM_MOVW;
  if(size == 4) instr = ASM_MOVL;

  GenAsmInstrTwoop(instr, ADDR_REGIND, REG_BP, -src_offset, dst_reg, MEM_TO_REG);
}

void GenAsmMoveRegToStackFrame(int size, int dst_offset, int src_reg){
  AsmInstr instr = 0;
  if(size == 1) instr = ASM_MOVB;
  if(size == 2) instr = ASM_MOVW;
  if(size == 4) instr = ASM_MOVL;

  GenAsmInstrTwoop(instr, ADDR_REGIND, REG_BP, -dst_offset, src_reg, REG_TO_MEM);
}


void GenAsmLoadReg(AsmInstr instr, int src_reg, int dst_reg){
  GenAsmInstrTwoop(instr, ADDR_REGDIR, src_reg, 0, dst_reg, REG_TO_REG);
}

void GenAsmLoadAddress(AsmInstr instr, Obj* src_obj, int src_offset, int dst_reg){
  GenAsmInstrTwoopObj(instr, ADDR_IMMED, src_obj, src_offset, dst_reg, REG_TO_REG);
}

void GenAsmLoadConst(AsmInstr instr, int src_const, int dst_reg){
  GenAsmInstrTwoop(instr, ADDR_IMMED, 0, src_const, dst_reg, REG_TO_REG);
}

void GenAsmLoadString(AsmInstr instr, int src_string_ref, int src_offset, int dst_reg){
  GenAsmInstrTwoopString(instr, ADDR_IMMED, src_string_ref, src_offset, dst_reg, REG_TO_REG);
}


void GenAsmLoadDerefAddress(AsmInstr instr, Obj* src_obj, int src_offset, int dst_reg){
  GenAsmInstrTwoopObj(instr, ADDR_MEMDIR, src_obj, src_offset, dst_reg, MEM_TO_REG);
}

void GenAsmLoadDerefConst(AsmInstr instr, int src_const, int dst_reg){
  GenAsmInstrTwoop(instr, ADDR_MEMDIR, 0, src_const, dst_reg, MEM_TO_REG);
}

void GenAsmLoadDerefString(AsmInstr instr, int src_string_ref, int src_offset, int dst_reg){
  GenAsmInstrTwoopString(instr, ADDR_MEMDIR, src_string_ref, src_offset, dst_reg, MEM_TO_REG);
}


void GenAsmStoreDerefAddress(AsmInstr instr, Obj* src_obj, int src_offset, int dst_reg){
  GenAsmInstrTwoopObj(instr, ADDR_MEMDIR, src_obj, src_offset, dst_reg, REG_TO_MEM);
}

void GenAsmStoreDerefConst(AsmInstr instr, int src_const, int dst_reg){
  GenAsmInstrTwoop(instr, ADDR_MEMDIR, 0, src_const, dst_reg, REG_TO_MEM);
}

void GenAsmStoreDerefString(AsmInstr instr, int src_string_ref, int src_offset, int dst_reg){
  GenAsmInstrTwoopString(instr, ADDR_MEMDIR, src_string_ref, src_offset, dst_reg, REG_TO_MEM);
}