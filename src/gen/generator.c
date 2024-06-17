#include "generator.h"

#include <string.h>
#include "decl/declarations.h"
#include "stmt/stmt.h"
#include "stmt/expr/expr.h"
#include "assembler.h"
#include "abi.h"
#include "link_flow.h"
#include "resources.h"
#include "ir_gen.h"
#include "ir_opt.h"
#include "ir_to_asm.h"

const char* default_base_text     = ".L";
const char* default_base_objs     = ".LP0";
const char* default_base_strings  = ".LP";
const char* default_base_switch   = ".LT";
const char* default_base_initloop = ".LI";

static int  data_location_counter = 0;

static void TranslateStaticVal(Obj* obj){
  // generate padding if needed
  if(data_location_counter % obj->type->align != 0){
    GenAsmSkip(obj->type->align - data_location_counter % obj->type->align);
    data_location_counter += obj->type->align - data_location_counter % obj->type->align;
  }

  if((obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE) {
    GenAsmSymbolLabel(obj->name);
  }
  LinkedList* init_vals = obj->init_vals;
  
  int offset = 0;
  for(Node* node = init_vals->first; node; node = node->next){
    InitVal* init_val = node->info;

    if(init_val->offset - offset > 0){
      GenAsmSkip(init_val->offset - offset);
    }

    if(init_val->expression->production == ADDRESS_PRIMARY
        || init_val->expression->production == COMPOUND_LITERAL){
      GenAsmDataObj(init_val->size, init_val->expression->expr_node->obj_ref, init_val->expression->expr_node->address);
    }
    else if(init_val->expression->production == CONSTANT_PRIMARY){
      GenAsmData(init_val->size, init_val->expression->expr_node->address);
    }
    else if(init_val->expression->production == STRING_PRIMARY){
      GenAsmDataString(init_val->size, init_val->expression->expr_node->string_ref, init_val->expression->expr_node->address);
    }

    offset = init_val->offset + init_val->size;

    /*StaticVal* static_val = node->info;

    // internal padding
    if(static_val->offset - offset > 0){
      GenAsmSkip(static_val->offset - offset);
    }

    if(static_val->kind == VAL_ARITHM){
      GenAsmData(static_val->size, static_val->value);
    }
    else if(static_val->kind == VAL_ADDRESS){
      GenAsmDataObj(static_val->size, static_val->obj_ref, static_val->value);
    }
    else if(static_val->kind == VAL_STRING){
      GenAsmDataString(static_val->size, static_val->string_ref, static_val->value);
    }
    offset = static_val->offset + static_val->size;*/
  }

  if(obj->type->size > offset) GenAsmSkip(obj->type->size - offset);
  data_location_counter += obj->type->size;
}

static void TranslateString(int i){
  GenAsmStringLabel(i);
  GenAsmAsciz(string_table->content[i]);
}

#define STRING_PARSE_REGULAR   0
#define STRING_PARSE_BACKSLASH 1
#define STRING_PARSE_OCT1      2
#define STRING_PARSE_OCT2      3
#define STRING_PARSE_OCT3      4
#define STRING_PARSE_HEX       5

// implement
static int GetRealStringLength(const char* str){
  int length = 1; // +1 for null terminator
  int parse_state = STRING_PARSE_REGULAR;
  for(int i = 0; i < strlen(str); i++){
    switch(parse_state){
    case STRING_PARSE_REGULAR:{
      switch(str[i]) {
      case '\\': parse_state = STRING_PARSE_BACKSLASH; break;
      default  : length++; break;
      }
    } break;

    case STRING_PARSE_BACKSLASH:{
      switch(str[i]){
      case '\\': 
      case 'a' :
      case 'b' :
      case 'f' :
      case 'n' :
      case 'r' :
      case 't' :
      case 'v' :         parse_state = STRING_PARSE_REGULAR; length++; break;
      case '0' ... '7' : parse_state = STRING_PARSE_OCT1; i--;         break;
      case 'x' :         parse_state = STRING_PARSE_HEX;               break;
      }
    } break;

    case STRING_PARSE_OCT1:{
      switch(str[i]){
      case '0' ... '7' : parse_state = STRING_PARSE_OCT2;                   break;
      default  :         parse_state = STRING_PARSE_REGULAR; i--; length++; break;
      }
    } break;

    case STRING_PARSE_OCT2:{
      switch(str[i]){
      case '0' ... '7' : parse_state = STRING_PARSE_OCT3;                   break;
      default  :         parse_state = STRING_PARSE_REGULAR; i--; length++; break;
      }
    } break;

    case STRING_PARSE_OCT3:{
      switch(str[i]){
      case '0' ... '7' : parse_state = STRING_PARSE_REGULAR;      length++; break;
      default  :         parse_state = STRING_PARSE_REGULAR; i--; length++; break;
      }
    } break;

    case STRING_PARSE_HEX:{
      switch(str[i]){
      case '0' ... '9':
      case 'a' ... 'f': 
      case 'A' ... 'F': break;
      default  : parse_state = STRING_PARSE_REGULAR; length++; i--; break;
      }
    } break;
    }
  }

  return length;
}

static void GenerateMetaData(void){
  int generated = 0;
  for(Node* node = global_name_list.first; node; node = node->next){
    char* name = node->info;
    GenAsmGlobal(name);
    generated = 1;
  }

  if(generated) GenAsmNewline();
  generated = 0;

  for(Node* node = extern_name_list.first; node; node = node->next){
    char* name = node->info;
    GenAsmExtern(name);
    generated = 1;
  }

  if(generated) GenAsmNewline();
}

static void GenerateStaticData(void){

  int static_no_linkage = 0;
  if(static_obj_list.first){
    GenAsmSection(".data");

    // with linkage
    for(Node* node = static_obj_list.first; node; node = node->next){
      Obj* obj = node->info;
      if((obj->specifier & LINKAGE_FETCH) == LINKAGE_NONE) {
        static_no_linkage = 1;
        continue;
      }
      TranslateStaticVal(obj);
    }

    // align before generating static data with no linkage
    if(data_location_counter % POINTER_SIZE != 0){
      GenAsmSkip(POINTER_SIZE - data_location_counter % POINTER_SIZE);
      data_location_counter += POINTER_SIZE - data_location_counter % POINTER_SIZE;
    }
    GenAsmNewline();
  }

  if(static_no_linkage) {
    GenAsmSymbolLabel(default_base_objs);

    // with no linkage
    for(Node* node = static_obj_list.first; node; node = node->next){
      Obj* obj = node->info;
      if((obj->specifier & LINKAGE_FETCH) != LINKAGE_NONE) continue;
      TranslateStaticVal(obj);
    }
    if(data_location_counter % POINTER_SIZE != 0){
      GenAsmSkip(POINTER_SIZE - data_location_counter % POINTER_SIZE);
      data_location_counter += POINTER_SIZE - data_location_counter % POINTER_SIZE;
    }

    GenAsmNewline();
  }

  if(string_table->size > 1){
    GenAsmSection(".rodata");

    int rodata_length = 0;
    // strings
    for(int i = 1; i < string_table->size; i++){  // first entry is reserved for static objects with no linkage
      TranslateString(i);
      rodata_length += GetRealStringLength(VectorGet(string_table, i));
    }
    if(rodata_length % POINTER_SIZE != 0){
      GenAsmSkip(POINTER_SIZE - rodata_length % POINTER_SIZE);
      rodata_length += POINTER_SIZE - rodata_length % POINTER_SIZE;
    }
    GenAsmNewline();
  }

}

static void GenerateText(){
  IrInit();
  GenerateIntermediate(StackPeek(&tree->stack));
  IrCalculateDepth(); PrintIntermediate();
  IrOptimize();       PrintIntermediate();
  GenerateAssembly();

  GenAsmEnd();

  IrFree();
}

void GenerateOutputFile(void){
  LinkFlowControl(StackPeek(&tree->stack), 0);
  GenerateMetaData();
  GenerateStaticData();
  GenerateText();
}