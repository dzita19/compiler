#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "obj.h"
#include "util/stack.h"
#include <stdint.h>

#define POINTER_SIZE 4

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
  ERROR_TYPE  = 1 << 10, // added to mark errors
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
  TYPE_ARRAY_UNSPEC,
  TYPE_INCOMPLETE,
} StructType;

struct Obj;

extern const int NONPROTOTYPE_FUNCTION;
extern const int ELLIPSIS_FUNCTION;

typedef struct Struct {
  struct Obj*    obj;
  StructKind     kind;
  StructType     type;
  struct Struct* parent;
  LinkedList     derived;
  LinkedList     parameters;
  int            attributes; // type qualifiers for qualified
                  // length for array
                  // functions: bit 0 - nonprototype
                  //            bit 1 - ellipsis
  int            size, align;
} Struct;

typedef enum Indirection{
  INDIRECTION_ARRAY_VARIABLE  =  0,
  INDIRECTION_POINTER         = -1,
  INDIRECTION_FUNCTION        = -2, //    prototype function
  INDIRECTION_NONPROTOTYPE    = -3, // nonprototype function
  INDIRECTION_CONST           = -4,
  INDIRECTION_VOLATILE        = -5,
  INDIRECTION_CONST_VOLATILE  = -6,
  SEPARATOR_INACTIVE          = -7,
  SEPARATOR_ACTIVE            = -8,
  SEPARATOR_DISABLED          = -9,
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

extern void       StructCompleted(Struct*);
extern Struct*    StructGetUnqualified(Struct*);
extern Struct*    StructGetParentUnqualified(Struct*);

extern Struct*    StructStringLiteral();
extern Struct*    StructVoidPtr();
extern Struct*    StructToPtr(Struct* str);
extern Struct*    StructArrayToPtr(Struct* array);
extern Struct*    StructFunctionToPtr(Struct* function);
extern Struct*    StructQualify(Struct* str, int qualifiers);
extern Struct*    StructGetHigherRank(Struct* str1, Struct* str2);
extern Struct*    StructArrayLengthSpecification(Struct* str, uint32_t length);

extern int        StructIsVoid(Struct* str);
extern int        StructIsVoidPtr(Struct* str);
extern int        StructIsInteger(Struct* str);
extern int        StructIsArithmetic(Struct* str);
extern int        StructIsChar(Struct* str);
extern int        StructIsScalar(Struct* str);
extern int        StructIsPointer(Struct* str);
extern int        StructIsPointerToObject(Struct* str);
extern int        StructIsFunctionPtr(Struct* str);
extern int        StructIsArray(Struct* str);
extern int        StructIsFunction(Struct* str);
extern int        StructIsPrototype(Struct* str);
extern int        StructIsNonprototype(Struct* str);
extern int        StructIsAggregate(Struct* str);
extern int        StructIsStructOrUnion(Struct* str);
extern int        StructIsEnum(Struct* str);
extern int        StructIsModifiable(Struct* str);
extern int        StructIsCastable(Struct* from, Struct* into);

extern int        StructIsCompatible(Struct* str1, Struct* str2);
extern int        StructIsCompatibleUnqualified(Struct* str1, Struct* str2);

extern Struct*    StructComposite(Struct* str1, Struct* str2); // return 0 if error

#endif