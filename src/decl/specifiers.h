#ifndef _SPECIFIERS_H_
#define _SPECIFIERS_H_

#include "declarations.h"

void declarations_init();

void Declaration();
void DeclarationSpecifiers();

void StorageClassSpecifierRef(StorageClassSpecifier);
void TypeSpecifierRef(TypeSpecifier);
void TypeQualifierRef(TypeQualifier);

void TagTypeRef(TagType);
void TagDefOpen();
void TagDefClose();

void TagNamedDef();
void TagAnonymousDef();
void TagNamedDecl();

#endif