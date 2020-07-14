#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "../Qmanagedmnet/qManagment.h"
#include "../SymbolTable/SymbolTable.h"
#include "../code-generation/codeGeneration.h"
#include "../ErrorHandler/ErrorHandler.h"

int insideFun = 0;
int actualScope = 0;
int reference = 0;

void insertAsLocalVariable(struct ast *a, int scope, int offset, int reference, int order)
{
  struct declaration *d = (struct declaration *)a;
  struct constant *c;
  int array = 0;
  int length = d->length;

  if (d->length >= 0)
  {
    array = 1;
  }

  insertLocalVariableToSymbolTable(d->id, offset, d->type, scope, length, array, reference, order);
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

    insertAsLocalVariable(body, getActiveLabel(), -offset - aux, 0, -1);
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
    r->array = 1;
    r->length = strlen(c->sValue);
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

  if (r->rightHand && !reference)
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

    if (!(r->array && equalTypes(r->type, lookupTypeInSymbolTable("char"))))
    {
      throwError(7);
    }

    if (r->length > l->length)
    {
      throwError(13);
    }

    //gcCopyArrayToDirUsingRegister(l, r);
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

void _checkParams(struct ast *params, struct Symbol *fun)
{
  struct ast *pAux;
  int count = 0;
  pAux = params;

  while (pAux != NULL)
  {
    pAux = pAux->nodetype == 'L' ? pAux->r : NULL;
    count++;
  }

  if (count != fun->fun->numberOfParams)
  {
    throwError(11);
  }
}

void evalArgumentList(struct ast *a)
{
  struct reg *r = NULL, *dummy;
  reference = 1;
  if (!a)
  {
    return;
  }

  if (!(dummy = malloc(sizeof(struct reg))))
  {
    throwError(1);
  }

  dummy->index = 7;
  dummy->label = "R";

  if (a->l->nodetype == 'L')
  {
    evalArgumentList(a->l);
  }
  else
  {
    r = eval(a->l);
    gcMoveStackPointer(-r->type->bytes);
    dummy->type = r->type;
    gcSaveInMemoryUsingRegister(dummy, r);
    freeRegister(r);
  }

  if (a->r->nodetype == 'L')
  {
    evalArgumentList(a->r);
  }
  else
  {
    r = eval(a->r);
    gcMoveStackPointer(-r->type->bytes);
    dummy->type = r->type;
    gcSaveInMemoryUsingRegister(dummy, r);
    freeRegister(r);
  }
  reference = 0;
}

void evalCall(struct ast *a)
{
  struct userCall *u = (struct userCall *)a;
  struct context *c;
  _checkParams(u->params, u->s);
  c = pushContext();
  gcWriteContext(c);
  evalArgumentList(u->params);
  gcMoveStackPointer(-8);
  int label = getNextLabel();

  gcSaveActualBase();
  gcSaveReturningLabel(label);
  gcJumpToLabel(u->s->fun->label);
  gcWriteLabel(label);
  popContext();
  gcRestoreContext(c);
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
      insertAsLocalVariable(aux->l, label, baseDir, 1, 1);
      auxDir = ((struct declaration *)aux->l)->type->bytes;
      baseDir += auxDir < 4 ? 4 : auxDir;
      aux = aux->r;
    }
    else
    {
      insertAsLocalVariable(aux, label, baseDir, 1, 2);
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

struct reg *evalCalculator(struct ast *a)
{
  struct reg *l = eval(a->l);
  struct reg *r = eval(a->r);
  struct reg *result, *free;
  int dominant = getDominantType(l->type, r->type);
  result = dominant == -1 ? l : r;
  free = dominant == -1 ? r : l;

  if (!((equalTypes(l->type, lookupTypeInSymbolTable("int"))) ||
        (equalTypes(l->type, lookupTypeInSymbolTable("int"))) ||
        (equalTypes(l->type, lookupTypeInSymbolTable("int"))) ||
        (equalTypes(l->type, lookupTypeInSymbolTable("int")))))
  {
    throwError(12);
  }

  gcRegisterNumericCalculation(a->nodetype, result, free);

  freeRegister(free);
  return result;
}

struct reg *evalNegative(struct ast *a)
{
  struct reg *r = eval(a->l);

  if (!(equalTypes(r->type, lookupTypeInSymbolTable("int")) ||
        equalTypes(r->type, lookupTypeInSymbolTable("float"))))
  {
    throwError(12);
  }

  gcMultiplyByConstant(r, -1);
  return r;
}

char *invertCondition(int operation)
{
  switch (operation)
  {
  case 1:
    return "<=";
  case 2:
    return ">=";
  case 3:
    return "==";
  case 4:
    return "!=";
  case 5:
    return "<";
  case 6:
    return ">";
  default:
    throwError(14);
    break;
  }
}

struct reg *evalCondition(struct ast *a)
{
  struct reg *l = eval(a->l);
  struct reg *r = eval(a->r);
  char *operation = invertCondition(a->nodetype);

  gcWritLogicalOperation(operation, l, r);

  freeRegister(r);
  return l;
}

void manageConditions(struct ast *cond, int label)
{
  struct reg *aux = eval(cond);

  gcWriteConditionUsingRegister(aux, label);
}

void evalIf(struct ast *a)
{
  struct ifFlow *i = (struct ifFlow *)a;
  int label = getNextLabel();
  int elseLabel;

  manageConditions(i->cond, label);
  eval(i->ifBody);

  if (i->elseBody != NULL)
  {
    elseLabel = getNextLabel();
    gcJumpToLabel(elseLabel);
    gcWriteLabel(label);
    eval(i->elseBody);
    label = elseLabel;
  }

  gcWriteLabel(label);
}

struct reg *
eval(struct ast *a)
{
  printf("nodetype: %d\n", a->nodetype);
  struct reg *r = NULL;

  if (a->nodetype == 'L' || a->nodetype == 'P' ||
      a->nodetype == '0' || a->nodetype == 'U' || a->nodetype == 'I')
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
  case 'U':
    evalCall(a);
    break;
  case '+':
  case '-':
  case '*':
  case '/':
    r = evalCalculator(a);
    break;
  case 1: // >
  case 2: // <
  case 3: // <>
  case 4: // ==
  case 5: // >=
  case 6: // <=
    r = evalCondition(a);
    break;
  case 'M':
    r = evalNegative(a);
    break;
  case 'I':
    evalIf(a);
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