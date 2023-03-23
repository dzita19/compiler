#ifndef _SPECIFIERS_H_
#define _SPECIFIERS_H_

#include "declarations.h"

void declarations_init();

void Declaration();
void FullDeclarationSpecifiers();
void RedeclarationSpecifiers();

void StorageClassSpecifierRef(StorageClassSpecifier);
void TypeSpecifierRef(TypeSpecifier);
void TypeQualifierRef(TypeQualifier);
void TypedefName();

void TagTypeRef(int tag_type);
void TagDefOpen();
void TagDefined();
void TagDeclared();

#endif