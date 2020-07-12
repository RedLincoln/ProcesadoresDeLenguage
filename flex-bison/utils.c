#include <stdlib.h>
#include "../ErrorHandler/ErrorHandler.h"

char *substr(char *src, int start, int end)
{

  int len = end - start;

  char *dest = (char *)malloc(sizeof(char) * (len + 1));

  // extracts characters between m'th and n'th index from source string
  // and copy them into the destination string
  for (int i = start; i < end && (*(src + i) != '\0'); i++)
  {
    *dest = *(src + i);
    dest++;
  }

  // null-terminate the destination string
  *dest = '\0';

  // return the destination string
  return dest - len;
}

void yyerror(char *format, ...)
{
}
