#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "memory_safety.h"

typedef struct Vector{
  void** content;
  int size;
  int reserved;
} Vector;

Vector* VectorCreateEmpty();
void VectorDrop(Vector*);

Vector* VectorInit();
void  VectorReserve(Vector*, int);
void  VectorPush(Vector*, void*);
void* VectorPop(Vector*);
void* VectorGet(Vector*, int);
int   VectorSize(Vector*);

#endif