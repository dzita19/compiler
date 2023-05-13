#ifndef _INITIALIZER_H_
#define _INITIALIZER_H_

#include "declarations.h"

void FullInitialization(void);

void InitializerOpen(void);   // handles errors of openning scalar fields
void InitializerClose(void);
void Initializer(void);       // handles errors of invalid assignments

#endif