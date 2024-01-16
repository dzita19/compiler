#ifndef _INITIALIZER_H_
#define _INITIALIZER_H_

#include "declarations.h"

// current active member to be initialized is designated by:
// field (if it's != NULL) or index (if it's >=0) value inside InitFrame object
// the active member's type (if above conditions are not met)

// current_obj_definition is considered only when linking initialization with and Obj*

void FullInitialization(void);
void NotCompoundLiteral(void);

void InitializerOpen(void);   // handles errors of opening scalar fields
void InitializerClose(void);
void Initializer(void);       // handles errors of invalid assignments

void FieldDesignator(void);
void ArrayDesignator(void);

#endif