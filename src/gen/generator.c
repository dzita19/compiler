#include "generator.h"

#include "decl/declarations.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "assembler.h"
#include "abi.h"
#include "link_flow.h"
#include "resources.h"
#include "gen_ir.h"

const char* default_base_text     = ".L";
const char* default_base_objs     = ".LP0000";
const char* default_base_strings  = ".LP";

static int  data_location_counter = 0;

static void TranslateStaticVal(Obj* obj){
  // generate padding if needed
  if(data_location_counter % obj->type->align != 0){
    GenAsmSkip(obj->type->align - data_location_counter % obj->type->align);
    data_location_counter += obj->type->align - data_location_counter % obj->type->align;
  }

  if((obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE) 
    GenAsmSymbolLabel(obj->name);
  LinkedList* init_vals = obj->init_vals;
  
  int offset = 0;
  for(Node* node = init_vals->first; node; node = node->next){
    StaticVal* static_val = node->info;
    if(static_val->kind == VAL_ARITHM){
      GenAsmData(static_val->size, static_val->value);
    }
    else if(static_val->kind == VAL_ADDRESS){
      GenAsmDataObj(static_val->size, static_val->obj_ref, static_val->value);
    }
    else if(static_val->kind == VAL_STRING){
      GenAsmDataString(static_val->size, static_val->string_ref, static_val->value);
    }
    offset = static_val->offset + static_val->size;
  }

  if(obj->type->size > offset) GenAsmSkip(obj->type->size - offset);
  data_location_counter += obj->type->size;
}

static void TranslateString(int i){
  GenAsmStringLabel(i);
  GenAsmAsciz(string_table->content[i]);
}

static void GenerateStaticData(void){

  if(static_obj_list.first){
    GenAsmSection(".data");
    // with linkage
    for(Node* node = static_obj_list.first; node; node = node->next){
      Obj* obj = node->info;
      if((obj->specifier & LINKAGE_FETCH) == LINKAGE_NONE) continue;
      TranslateStaticVal(obj);
    }
    GenAsmNewline();

    GenAsmSymbolLabel(default_base_objs);
    // with no linkage
    for(Node* node = static_obj_list.first; node; node = node->next){
      Obj* obj = node->info;
      if((obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE) continue;
      TranslateStaticVal(obj);
    }
    GenAsmNewline();
  }

  if(string_table->size > 1){
    GenAsmSection(".rodata");
    // strings
    for(int i = 1; i < string_table->size; i++){  // first entry is reserved for static objects with no linkage
      TranslateString(i);
    }
  }

}

static void GenerateText(){
  GenAsmSection(".text");

  IrInit();
  GenerateIntermediate(tree->stack.top->info);
  CalculateDepth();
  PrintIntermediate();

  IrFree();
}

void GenerateOutputFile(void){
  LinkFlowControl(tree->stack.top->info, 0);

  GenerateStaticData();
  GenerateText();
}