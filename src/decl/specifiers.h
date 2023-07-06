#ifndef _SPECIFIERS_H_
#define _SPECIFIERS_H_

#include "declarations.h"

void declarations_init(void);

void Declaration(void);
void FullDeclarationSpecifiers(void);
void RedeclarationSpecifiers(void);

void StorageClassSpecifierRef(StorageClassSpecifier);
void TypeSpecifierRef(TypeSpecifier);
void TypeQualifierRef(TypeQualifier);
void TypedefName(void);

void TagTypeRef(int tag_type);
void TagDefOpen(void);
void TagDefined(void);
void TagDeclared(void);

void IsFunctionDefinition(void);
void NotFunctionDefinition(void);

#endif