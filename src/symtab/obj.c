#include "obj.h"

void ObjDrop(Obj* obj){
  if(obj->kind == OBJ_TYPE)
    free(obj->type);  
}