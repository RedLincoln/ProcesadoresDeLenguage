#include <stdio.h>
#include <stdlib.h>
#include "ErrorHandler.h"

char *errors[] = {
    "",
    "Out of Space",
    "Variable already declared",
    "Out of Registers",
    "Output file error",
    "Variable not declared",
    "Indexing is only posible with arrays and strings",
    "Incompatible Types",
    "Array Length can only be int type",
    "Internal Error",
    "Function not declared",
    "Arguments missmatch"};

void throwError(int code)
{
  fprintf(stderr, "Error: %s\n", errors[code]);
  exit(code);
}