#include "logger.h"

#include <stdio.h>

extern int column, row;

extern void ReportError   (const char* message){
  extern int semantic_errors;

  semantic_errors = 1;
  printf("ERROR (%d:%d): %s\n", row, column, message);
}

extern void ReportWarning (const char* message){
  printf("WARNING (%d:%d): %s\n", row, column, message);
}