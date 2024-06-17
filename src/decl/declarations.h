#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_

#include "symtab/symtab.h"
#include "symtab/scope.h"
#include "symtab/obj.h"
#include "symtab/struct.h"

#include "util/memory_safety.h"
#include "util/linked_list.h"
#include "util/stack.h"
#include "util/queue.h"
#include "util/logger.h"

#include "gen/abi.h"

extern Symtab* symtab;
extern int     semantic_errors;

extern Stack typedef_stack;
extern Stack type_stack;
extern Stack indirection_stack;
extern Stack parameter_stack;
extern Stack name_stack;
extern Stack const_expr_stack;    // Stack(ConstExpr*)

extern Stack initializer_stack;   // Stack(LinkedList(InitVal*)) - no need to maintain the correct order until full initializer
extern Stack init_attrib_stack;   // Stack(int) - designates whether initializer is static or not
extern Stack init_frame_stack;    // Stack(Stack(InitFrame*))
extern Stack init_error_stack;    // Stack(int) - error in current initializer
extern Stack init_size_stack;     // Stack(int) - counts number of main initializers for unspecified length array
extern Stack obj_definiton_stack; // Stack(Obj*);
// extern Obj*    current_obj_definition;

extern LinkedList static_obj_list;  // LinkedList(Obj*)
extern LinkedList label_name_list;  // LinkedList(char*) - list of symbols that generate a label (also functions)
extern LinkedList global_name_list; // LinkedList(char*) - list of symbols that generate global declaration
extern LinkedList extern_name_list; // LinkedList(char*) - list of symbols that generate extern declaration

extern CallFrame param_frame; // to allocate memory for function parameters

extern uint8_t ellipsis;
// extern uint8_t full_decl_specifiers; // 0 if not, 1 if is. when 0, qualifiers are added to type frame, else to indirections
  // important - needs to be reset after typename is recognized (because it is not followed by )
extern uint8_t current_qualifiers;
extern uint8_t current_function_level;
extern int32_t current_enum_constant;

extern uint8_t block_level;
extern Obj*    current_function_body;
extern Obj*    latest_function_decl;
extern Stack   param_scope_stack;
extern Scope*  func_prototype_scope;
extern uint8_t nonprototype_redecl;
  // at beginning of full declaration, fdef and pso are both 0 (and so shall be at the end)
  // pso is set to 1 when pso is 0 and fparam open is reduced (also add new scope)
  // fdef is incremented every time pso is 1 and fparam open is reduced
  // fdef is decremented every time fparam closed is reduced
  // nonprototype redecl is 1 after completing function declarator and before function body entry

extern int32_t current_static_counter;
extern Stack   stack_frame_stack; // nested stack counter per block

typedef struct TypeFrame{
  Obj* current_type;
  int type_specifiers;
  int storage_specifier;
  int type_qualifiers;
  int full_decl_specifiers;
  int identifier_expected; // tells compiler to force identifier lexing instead of checking symtab
    // this is necessary after using typedef inside declaration specifier (since we are declaring a variable of a custom type)
    // and  is necessary after using struct-union-enum keywords for declaring new tag (it's in its own namespace)
    // reset after declarator: it has to be 0 for initialization expression to work, and then set it to 1 for next declarator
} TypeFrame;

TypeFrame*  TypeFrameCreateEmpty(void);
void        TypeFrameDrop (TypeFrame*);
void        TypeFrameClear(TypeFrame*);

typedef struct NameFrame{
  char* name;
  int   tag_type;
} NameFrame;

NameFrame*  NameFrameCreateEmpty(void);
void        NameFrameDrop (NameFrame*);
void        NameFrameClear(NameFrame*);

typedef enum StaticValKind{
  VAL_ERROR,
  VAL_ARITHM,
  VAL_ADDRESS,
  VAL_STRING,
} StaticValKind;

typedef struct ConstExpr{
  Obj* obj_ref;    // if targets address of an obj
  int string_ref; //  if targets address of a string
  int value;
  StaticValKind kind;
  Struct* type;
} ConstExpr;

ConstExpr* ConstExprCreateEmpty(void);
void       ConstExprDrop(ConstExpr*);

typedef enum InitKind{
  INIT_ERROR,
  INIT_SCALAR,
  INIT_ARRAY,
  INIT_STRUCT,
  INIT_UNION,
} InitKind;

typedef enum InitFrameStatus{
  INIT_FRAME_FIRST_ACTIVE,
  INIT_FRAME_ACTIVE,
  INIT_FRAME_ACTIVE_DESIGNATED,
  INIT_FRAME_FIRST_OPEN,
  INIT_FRAME_IMPLICIT_OPEN,
  INIT_FRAME_EXPLICIT_OPEN,
} InitFrameStatus;

typedef struct InitFrame{
  Struct* type;
  Node* field;       // Node(Obj*)
  unsigned int index;
  InitFrameStatus xopen;
  // int offset;
  // int parent_offset;
} InitFrame;

InitFrame* InitFrameCreateEmpty(void);
void       InitFrameDrop(InitFrame*);
void       InitFrameInitializeWithType(InitFrame*, Struct* type, int first);

typedef struct TreeNode TreeNode;

typedef struct InitVal{
  int size;
  int offset; // offset of the field from the beginning of the object
  TreeNode* expression;
} InitVal;

InitVal* InitValCreateEmpty();
void     InitValDrop(InitVal*);
void     InitValDump(InitVal*);

void InitValAddToList(InitVal*, LinkedList*);
int  InitValAddToListNoReplace(InitVal*, LinkedList*); // 1 for successful add

void StaticObjListDump(void);
void LabelNameListDump(void);
void GlobalNameListDump(void);
void ExternNameListDump(void);

void declarations_init(void);
void declarations_free(void);

extern Queue identifier_queue; // communication between lexer and parser
void identifier(const char*);

#endif