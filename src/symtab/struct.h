#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "obj.h"
#include "util/stack.h"

extern const int POINTER_SIZE;

typedef enum PredefinedType {
    VOID_T,
    INT8_T,
   UINT8_T,
   INT16_T,
  UINT16_T,
   INT32_T,
  UINT32_T,
   INT64_T,
  UINT64_T,
  PREDEFINED_TYPES_COUNT,
} PredefinedType;

typedef enum TypeSpecifier{
  VOID        = 1 << 0,
	CHAR        = 1 << 1,
	SHORT       = 1 << 2,
	INT         = 1 << 3,
	LONG        = 1 << 4,
	FLOAT       = 1 << 5,
	DOUBLE      = 1 << 6,
	SIGNED      = 1 << 7,
	UNSIGNED    = 1 << 8,
  CUSTOM_TYPE = 1 << 9,
} TypeSpecifier;

typedef enum TypeQualifier{
  CONST       = 1 << 0,
  VOLATILE    = 1 << 1,
} TypeQualifier;

typedef enum StructKind {
  STRUCT_DIRECT,
  STRUCT_QUALIFIED,
  STRUCT_ARRAY,
  STRUCT_POINTER,
  STRUCT_FUNCTION,
} StructKind;

typedef enum StructType{
  TYPE_OBJECT,
  TYPE_FUNCTION,
  TYPE_INCOMPLETE,
  TYPE_ARRAY_UNSPEC,
} StructType;

struct Obj;

typedef struct Struct {
  struct Obj* obj;
  StructKind kind;
  StructType type;
  struct Struct* parent;
  LinkedList derived;
  LinkedList parameters;
  int attributes; // type qualifiers for qualified
                  // length for array
  int size;
  int align;
} Struct;

typedef enum Indirection{
  INDIRECTION_ARRAY_VARIABLE  =  0,
  INDIRECTION_POINTER         = -1,
  INDIRECTION_FUNCTION        = -2,
  INDIRECTION_CONST           = -3,
  INDIRECTION_VOLATILE        = -4,
  INDIRECTION_CONST_VOLATILE  = -5,
  SEPARATOR_INACTIVE          = -6,
  SEPARATOR_ACTIVE            = -7,
  SEPARATOR_DISABLED          = -8,
} Indirection;

extern Indirection qualifiers_to_indirection[];

extern Struct*  StructCreateEmpty();
extern void     StructDrop(Struct*);
extern void     StructDump(Struct*);
extern void     StructTreeDump(Struct*);

extern Struct* StructProcessIndirections(
  Struct* base_type,
  int base_type_qualifiers,
  LinkedList* indirections,
  Stack* parameters
); // returns 0 if error

extern StructType StructGetType(Struct*);
extern Struct*    StructGetUnqualified(Struct*);
extern Struct*    StructGetParentUnqualified(Struct*);

extern Struct*    StructStringLiteral();
extern Struct*    StructVoidPtr();
extern Struct*    StructToPtr(Struct* str);
extern Struct*    StructArrayToPtr(Struct* array);
extern Struct*    StructFunctionToPtr(Struct* function);
extern Struct*    StructQualify(Struct* str, int qualifiers);
extern Struct*    StructGetHigherRank(Struct* str1, Struct* str2);

extern int        StructIsVoid(Struct* str);
extern int        StructIsInteger(Struct* str);
extern int        StructIsArithmetic(Struct* str);
extern int        StructIsScalar(Struct* str);
extern int        StructIsPointer(Struct* str);
extern int        StructIsFunctionPtr(Struct* str);
extern int        StructIsArray(Struct* str);
extern int        StructIsAggregate(Struct* str);
extern int        StructIsStructOrUnion(Struct* str);
extern int        StructIsModifiable(Struct* str);
extern int        StructIsCastable(Struct* from, Struct* into);

#endif