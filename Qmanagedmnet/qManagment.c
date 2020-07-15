#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "../SymbolTable/SymbolTable.h"
#include "../Ast/ast.h"
#include "../ErrorHandler/ErrorHandler.h"
#include "qManagment.h"

#define R_SIZE 6
#define RR_SIZE 4

int R[R_SIZE];
int RR[RR_SIZE];
int label = 0;
int dir = 0x12000;

struct reg *getRegister(struct TypeSymbol *type, char *label, int index)
{
  struct reg *r;
  if (!(r = malloc(sizeof(struct reg))))
  {
    throwError(1);
  }

  if (strcmp(label, "R") == 0)
  {
    if (R[index] == 1)
    {
      throwError(3);
    }
    R[index] = 1;
  }
  else
  {
    if (RR[index] == 1)
    {
      throwError(3);
    }
    RR[index] = 1;
  }

  r->label = label;
  r->index = index;
  r->type = type;

  return r;
}

struct reg *assignRegister(struct TypeSymbol *type)
{
  struct reg *r;
  int i;
  char *label = type->bytes <= 4 ? "R" : "RR";
  int size = type->bytes <= 4 ? R_SIZE : RR_SIZE;
  if (!(r = malloc(sizeof(struct reg))))
  {
    throwError(1);
  }

  r->label = label;
  r->type = type;
  if (type->bytes <= 4)
  {
    for (i = 0; i < R_SIZE; i++)
    {
      if (R[i] == 0)
      {
        R[i] = 1;
        break;
      }
    }
  }
  else
  {
    for (i = 0; i < RR_SIZE; i++)
    {
      if (RR[i] == 0)
      {
        RR[i] = 1;
        break;
      }
    }
  }

  if (i == size)
  {
    throwError(3);
  }

  r->index = i;
  return r;
}

void freeRegister(struct reg *r)
{
  if (r->type->bytes <= 4)
  {
    R[r->index] = 0;
  }
  else
  {
    RR[r->index] = 0;
  }
}

void freeAllRegisters()
{
  for (int i = 0; i < R_SIZE; i++)
  {
    R[i] = 0;
  }
  for (int i = 0; i < RR_SIZE; i++)
  {
    RR[i] = 0;
  }
}

int getNextFreeAddress(int bytes)
{
  dir -= bytes;
  dir = dir & 0xffffc;
  return dir;
}

int getActiveLabel()
{
  return label;
}

int getNextLabel()
{
  return ++label;
}

struct context *pushContext()
{
  context_stack *aux;
  struct context *c = malloc(sizeof(struct context));

  if (!c)
  {
    throwError(1);
  }

  for (int i = 0; i < R_SIZE; i++)
  {
    c->R[i] = R[i];
  }
  for (int i = 0; i < RR_SIZE; i++)
  {
    c->RR[i] = RR[i];
  }

  if (!last)
  {
    if (!(last = (context_stack *)malloc(sizeof(context_stack))))
    {
      throwError(1);
    }

    last->val = c;
  }
  else
  {
    if (!(last->next = (context_stack *)malloc(sizeof(context_stack))))
    {
      throwError(1);
    }

    aux = last;
    last = last->next;
    last->val = c;
    last->last = aux;
  }

  freeAllRegisters();

  return c;
}

void popContext()
{
  if (last)
  {
    for (int i = 0; i < R_SIZE; i++)
    {
      R[i] = last->val->R[i];
    }
    for (int i = 0; i < RR_SIZE; i++)
    {
      RR[i] = last->val->RR[i];
    }

    last = last->last;
  }
}