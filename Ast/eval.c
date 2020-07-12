#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "../Qmanagedmnet/qManagment.h"
#include "../SymbolTable/SymbolTable.h"
#include "../code-generation/codeGeneration.h"
#include "../ErrorHandler/ErrorHandler.h"

void insertAsLocalVariable(struct ast *a, int scope, int offset)
{
  struct declaration *d = (struct declaration *)a;

  insertLocalVariableToSymbolTable(d->id, offset, d->type, scope);
}

int spaceRequiredForLocalVariable(struct ast *body, int offset)
{
  int aux;

  if (body->nodetype == 'L')
  {
    aux = spaceRequiredForLocalVariable(body->l, offset);
    aux = spaceRequiredForLocalVariable(body->r, aux);
    return aux;
  }

  if (body->nodetype == 'I' || body->nodetype == 'F' || body->nodetype == 'W')
  {
    return spaceRequiredForLocalVariable(((struct flow *)body)->body, offset);
  }

  if (body->nodetype == 'D')
  {
    if (equalTypes(((struct declaration *)body)->type, lookupTypeInSymbolTable("float")))
    {
      insertAsLocalVariable(body, getActiveLabel(), -offset - 8);
      return offset + 8;
    }
    else
    {
      insertAsLocalVariable(body, getActiveLabel(), -offset - 4);
      return offset + 4;
    }
  }

  return offset;
}

void evalDArray(struct declaration *d)
{
  struct constant *k = ((struct constant *)d->length);
  int addr;
  int space;

  if (d->length->nodetype != 'K')
  {
    throwError(8);
  }
  else if (equalTypes(k->type, lookupTypeInSymbolTable("int")))
  {
    space = (int)(k->nValue * d->type->bytes);

    addr = getNextFreeAddress(space);

    insertArrayToSymbolTable(d->id, addr, (int)(k->nValue), d->type);

    gcStoreArrayInMemory(addr, space);
  }
  else
  {
    throwError(8);
  }
}

struct reg *evalK(struct ast *a)
{
  struct constant *c = (struct constant *)a;
  struct reg *r;
  int addr;

  r = assignRegister(c->type);

  if (equalTypes(lookupTypeInSymbolTable("char"), c->type) && c->array)
  {
    addr = getNextFreeAddress(strlen(c->sValue));
    gcStoreStringInMemory(addr, c->sValue);
    gcCopyAddrToRegister(r, addr);
  }
  else
  {
    gcNumericConstant(r, c->nValue);
  }

  return r;
}

void evalD(struct ast *a)
{
  struct declaration *d = (struct declaration *)a;
  int addr;

  if (d->length != NULL)
  {
    evalDArray(d);
  }
  else
  {
    addr = getNextFreeAddress(d->type->bytes);

    insertVariableToSymbolTable(d->id, addr, d->type);

    gcReservePrimitiveSpace(addr, d->type);
  }
}

struct reg *evalRArray(struct ref *r, struct Symbol *s)
{
  struct reg *reg;

  if (!s->a)
  {
    throwError(6);
  }

  reg = eval(r->a);

  if (!equalTypes(reg->type, lookupTypeInSymbolTable("int")))
  {
    throwError(8);
  }

  gcMultiplyRegisterForNumericConstant(reg, s->type);

  if (r->rightHand)
  {
    gcStoreArrayDataInRegister(s->address, reg, s->type);
  }
  else
  {
    gcStoreArrayDirInRegister(s->address, reg);
  }

  return reg;
}

struct reg *evalR(struct ast *a)
{
  struct ref *r = (struct ref *)a;
  struct Symbol *s = lookupVariableInSymbolTable(r->id);
  struct reg *reg;

  if (!s)
  {
    throwError(5);
  }

  if (r->a)
  {
    reg = evalRArray(r, s);
  }
  else
  {
    reg = assignRegister(s->type);
    if (r->rightHand)
    {
      gcCopyContentToRegister(reg, s);
    }
    else
    {
      if (s->a)
      {
        reg->array = 1;
        reg->length = s->a->length;
      }
      gcCopyAddrToRegister(reg, s->address);
    }
  }

  return reg;
}

struct reg *evalA(struct ast *a)
{
  printf("Assigning\n");
  struct reg *l = eval(a->l);
  struct reg *r = eval(a->r);

  if (!areTypesCompatible(l->type, r->type))
  {
    throwError(7);
  }

  if (l->array)
  {
    if (!equalTypes(l->type, lookupTypeInSymbolTable("char")))
    {
      throwError(7);
    }

    gcCopyArrayToDirUsingRegister(l, r);
  }
  else
  {
    gcSaveInMemoryUsingRegister(l, r);
  }

  freeRegister(l);
  return r;
}

void evalL(struct ast *a)
{
  eval(a->l);
  eval(a->r);
}

void evalFuntion(struct ast *a)
{
  struct funAst *f = (struct funAst *)a;
  struct ast *aux;
  int numberOfParams = 0, numberOfBytesRequiered, label;
  int baseDir = 8;
  int auxDir = 0;

  aux = f->params;
  label = getNextLabel();

  printf("Function declaration, params: %d\n", f->params != NULL);

  while (aux != NULL)
  {
    if (aux->nodetype == 'L')
    {
      insertAsLocalVariable(aux->l, label, baseDir);
      auxDir = ((struct declaration *)aux->l)->type->bytes;
      baseDir += auxDir < 4 ? 4 : auxDir;
      aux = aux->r;
    }
    else
    {
      insertAsLocalVariable(aux, label, baseDir);
      auxDir = ((struct declaration *)aux)->type->bytes;
      baseDir += auxDir < 4 ? 4 : auxDir;
      aux = NULL;
    }
    numberOfParams++;
  }

  numberOfBytesRequiered = spaceRequiredForLocalVariable(f->body, 0);

  insertFunctionToSymbolTable(f->id, f->type, label, numberOfParams, numberOfBytesRequiered);
}

struct reg *eval(struct ast *a)
{
  printf("nodetype: %d\n", a->nodetype);
  struct reg *r;
  switch (a->nodetype)
  {
  case 'K':
    r = evalK(a);
    break;
  case 'D':
    evalD(a);
    break;
  case 'R':
    r = evalR(a);
    break;
  case '=':
    r = evalA(a);
    break;
  case 'L':
    evalL(a);
    break;
  case 'P':
    evalFuntion(a);
    break;
  case '0':
    break;
  default:
    break;
  }

  return r;
}
void treefree(struct ast *a)
{
  freeAllRegisters();
}