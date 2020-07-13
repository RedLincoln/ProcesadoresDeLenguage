#include <stdlib.h>
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

struct reg *assignRegister(struct TypeSymbol *type)
{
  struct reg *r;
  if (!(r = malloc(sizeof(struct reg))))
  {
    throwError(1);
  }
  int *arr = type->bytes <= 4 ? R : RR;
  char *label = type->bytes <= 4 ? "R" : "RR";

  for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
  {
    if (arr[i] == 0)
    {
      arr[i] = 1;
      r->label = label;
      r->index = i;
      r->type = type;
      break;
    }
  }

  if (!r->type)
  {
    throwError(3);
  }

  return r;
}

void freeRegister(struct reg *r)
{
  int *arr = r->type->bytes <= 4 ? R : RR;
  arr[r->index] = 0;
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