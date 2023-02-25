#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "obj.h"

#define TYPE_SPECIFIER_CONST    0x1
#define TYPE_SPECIFIER_VOLATILE 0x2

typedef enum PredefinedType {
    VOID_T,
    INT8_T,
   UINT8_T,
   INT16_T,
  UINT16_T,
   INT32_T,
  UINT32_T,
} PredefinedType;

typedef enum TypeSpecifier{
  VOID,
	CHAR,
	SHORT,
	INT,
	LONG,
	FLOAT,
	DOUBLE,
	SIGNED,
	UNSIGNED,
} TypeSpecifier;

typedef enum StructKind {
  STRUCT_SCALAR,
  STRUCT_ARRAY,
  STRUCT_POINTER,
  STRUCT_COMPOSITE,
  STRUCT_ENUM
} StructKind;

typedef struct Struct {
  Obj* obj;
  StructKind kind;
  struct Struct* elem_type;
  int type_specifiers;
} Struct;

#endif