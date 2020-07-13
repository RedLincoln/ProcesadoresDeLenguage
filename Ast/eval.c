#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "../Qmanagedmnet/qManagment.h"
#include "../SymbolTable/SymbolTable.h"
#include "../code-generation/codeGeneration.h"
#include "../ErrorHandler/ErrorHandler.h"

int insideFun = 0;
int actualScope = 0;

void insertAsLocalVariable(struct ast *a, int scope, int offset, int reference)
{
  struct declaration *d = (struct declaration *)a;
  struct constant *c;
  int array = 0;
  int length = d->length;

  if (d->length >= 0)
  {
    array = 1;
  }

  insertLocalVariableToSymbolTable(d->id, offset, d->type, scope, length, array, reference);
}

int spaceRequiredForLocalVariable(struct ast *body, int offset)
{
  int aux;
  struct declaration *d;
  int length;

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
    d = (struct declaration *)body;
    length = d->length <= 0 ? 1 : d->length;
    aux = d->type->bytes * length;
    if ((aux % 4) != 0)
    {
      aux = (int)(aux / 4) * 4 + 4;
    }

    insertAsLocalVariable(body, getActiveLabel(), -offset - aux, 0);
    return offset + aux;
  }

  return offset;
}

void evalDArray(struct declaration *d)
{
  int addr;
  int space;

  space = d->length * d->type->bytes;

  addr = getNextFreeAddress(space);

  insertArrayToSymbolTable(d->id, addr, d->length, d->type);

  gcStoreArrayInMemory(addr, space);
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

  if (d->length >= 0)
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
  struct Symbol *s;

  struct reg *reg;

  if (!isInFunction())
  {
    s = lookupVariableInSymbolTable(r->id);
  }
  else
  {
    s = lookupLocalVariableInSymbolTable(r->id, actualScope);
  }

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
    if (r->rightHand)
    {
      reg = assignRegister(s->type);
      gcCopyContentToRegister(reg, s);
    }
    else
    {
      reg = assignRegister(lookupTypeInSymbolTable("int"));
      if (s->a)
      {
        reg->array = 1;
        reg->length = s->a->length;
      }
      gcCopyAddrToRegister(reg, s->address);
      reg->type = s->type;
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

void manageFunctionDeclarationInQ(int label, struct ast *params, struct ast *body,
                                  int numberOfParams, int bytesRequiered)
{
  struct reg *r;

  actualScope = label;
  inFunction();

  gcWriteLabel(label);
  gcNewBase();
  gcReserveSpaceForLocalVariables(bytesRequiered);

  eval(body);
  gcFreeLocalSpace();
  gcRestoreBase();
  r = assignRegister(lookupTypeInSymbolTable("int"));
  gcStoreReturnLabelFromStackInRegister(r);
  gcPrintGTFromRegister(r);
  outsideFunction();

  actualScope = 0;
  freeRegister(r);
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
      insertAsLocalVariable(aux->l, label, baseDir, 1);
      auxDir = ((struct declaration *)aux->l)->type->bytes;
      baseDir += auxDir < 4 ? 4 : auxDir;
      aux = aux->r;
    }
    else
    {
      insertAsLocalVariable(aux, label, baseDir, 1);
      auxDir = ((struct declaration *)aux)->type->bytes;
      baseDir += auxDir < 4 ? 4 : auxDir;
      aux = NULL;
    }
    numberOfParams++;
  }

  numberOfBytesRequiered = spaceRequiredForLocalVariable(f->body, 0);

  insertFunctionToSymbolTable(f->id, f->type, label, numberOfParams, numberOfBytesRequiered);

  manageFunctionDeclarationInQ(label, f->params, f->body, numberOfParams, numberOfBytesRequiered);
}

struct reg *eval(struct ast *a)
{
  printf("nodetype: %d\n", a->nodetype);
  struct reg *r = NULL;

  if (a->nodetype == 'L' || a->nodetype == 'P' || a->nodetype == '0')
  {
    freeAllRegisters();
  }
  switch (a->nodetype)
  {
  case 'K':
    r = evalK(a);
    break;
  case 'D':
    if (!isInFunction())
    {
      evalD(a);
    }
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