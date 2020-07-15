#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "../Qmanagedmnet/qManagment.h"
#include "../SymbolTable/SymbolTable.h"
#include "../code-generation/codeGeneration.h"
#include "../ErrorHandler/ErrorHandler.h"

#define PRINT -12

int insideFun = 0;
int actualScope = 0;
int reference = 0;
int breakLabel = 0;
int continueLabel = 0;

/**
 *  Función auxiliar para introducir en la tabla de simbolos las variables locales 
 */

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

/**
 * Calcula la cantidad de bytes a reservar para poder guardar en la pila las variables locales 
 * y lo devuleve, también introduce las variables locales.
 */

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

/**
 * Evaluación de los nodos de declaración de arrays
 */

void evalDArray(struct declaration *d)
{
  int addr;
  int space;

  space = d->length * d->type->bytes;

  addr = getNextFreeAddress(space);

  insertArrayToSymbolTable(d->id, addr, d->length, d->type);

  gcStoreArrayInMemory(addr, space);
}

/**
 * Evaluación de los nodos de Constantes
 */

struct reg *evalK(struct ast *a)
{
  struct constant *c = (struct constant *)a;
  struct reg *r;
  int addr;

  r = assignRegister(c->type);

  if (equalTypes(lookupTypeInSymbolTable("char"), c->type) && c->array)
  {
    r->array = 1;
    r->length = strlen(c->sValue) + 1;
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

/**
 * Evaluación de los nodos de declaración
 */

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

/**
 * Evaluación de los nodos de referencias de arrays
 */

struct reg *evalRArray(struct ref *r, struct Symbol *s)
{
  struct reg *reg;
  struct reg *free;

  if (r->a)
  {
    reg = eval(r->a);

    if (!equalTypes(reg->type, lookupTypeInSymbolTable("int")))
    {
      throwError(8);
    }
    gcMultiplyRegisterForNumericConstant(reg, s->type);

    if (r->rightHand)
    {
      free = assignRegister(reg->type);
      gcStoreArrayDataInRegister(s->address, reg, s->type, free);
      if (isInFunction() && s->reference)
      {
        gcStorePointerInRegisterInTheSameRegister(reg);
      }
      freeRegister(free);
    }
    else
    {
      free = assignRegister(reg->type);
      gcStoreArrayDirInRegister(s->address, reg, free);
      if (isInFunction() && s->reference)
      {
        gcStorePointerInRegisterInTheSameRegister(reg);
      }
      freeRegister(free);
    }
  }
  else
  {
    reg = assignRegister(s->type);
    reg->array = 1;
    reg->length = s->a->length;
    gcStoreArrayAddressInRegister(s->address, reg);
  }

  return reg;
}

/**
 * Evaluación de los nodos referencia
 */

struct reg *evalR(struct ast *a)
{
  struct ref *r = (struct ref *)a;
  struct Symbol *s;

  struct reg *reg;

  s = !isInFunction() ? lookupVariableInSymbolTable(r->id) : lookupLocalVariableInSymbolTable(r->id, actualScope);

  if (!s)
  {
    throwError(5);
  }

  if (s->a)
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

/**
 * Evaluación de los nodos de asignación
 */

struct reg *evalA(struct ast *a)
{
  printf("Assigning\n");
  struct reg *free;
  struct reg *l = eval(a->l);
  struct reg *r = eval(a->r);

  if (!areTypesCompatible(l->type, r->type))
  {
    throwError(7);
  }

  if (l->array)
  {
    if (!r->array)
    {
      throwError(15);
    }
    if (!equalTypes(r->type, l->type))
    {
      throwError(7);
    }

    if (r->length > l->length)
    {
      throwError(13);
    }

    free = assignRegister(r->type);
    gcCopyArrayToArrayUsingRegister(l, r, free, r->length);
    freeRegister(free);
  }
  else
  {
    gcSaveInMemoryUsingRegister(l, r);
  }

  freeRegister(l);
  return r;
}

/**
 * Evaluación de los nodos lista
 */

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

/**
 * se comprueba que la cantidad de argumentos que se pasa es igual a la cantidad
 * de parametros de la función, devuelve esta cantidad.
 */

int _checkParams(struct ast *params, struct Symbol *fun)
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

  return count;
}

/**
 * Introduce los argumentos de la llamada en la pila
 */

int evalArgumentList(struct ast *a, int paramCounter)
{
  int returnValue = 0;

  struct reg *r = NULL, *dummy;
  reference = 1;

  if (!(dummy = malloc(sizeof(struct reg))))
  {
    throwError(1);
  }

  dummy->index = 7;
  dummy->label = "R";

  if (paramCounter == 0)
  {
    return 0;
  }
  else if (paramCounter == 1)
  {
    r = eval(a);
    returnValue += r->type->bytes;
    dummy->type = r->type;
    gcMoveStackPointer(-r->type->bytes);
    gcSaveInMemoryUsingRegister(dummy, r);
  }
  else
  {
    if (paramCounter >= 2)
    {
      returnValue += evalArgumentList(a->r, paramCounter - 1);
    }

    r = eval(a->l);
    returnValue += r->type->bytes;
    dummy->type = r->type;
    gcMoveStackPointer(-r->type->bytes);
    gcSaveInMemoryUsingRegister(dummy, r);
  }

  freeRegister(r);
  reference = 0;

  return returnValue;
}

/**
 * Evaluación de los nodos de llamadas a funciones
 */

void evalCall(struct ast *a)
{
  struct userCall *u = (struct userCall *)a;
  struct context *c;
  int moved;
  int label;
  int paramCounter;

  struct Symbol *s = lookupFunctionInSymbolTable(u->id);
  if (!s)
  {
    throwError(10);
  }

  paramCounter = _checkParams(u->params, s);
  c = pushContext();

  gcWriteContext(c);
  moved = evalArgumentList(u->params, paramCounter);
  printf("Moved : %d\n", moved);
  gcMoveStackPointer(-8);
  label = getNextLabel();

  gcSaveActualBase();
  gcSaveReturningLabel(label);
  gcJumpToLabel(s->fun->label);
  gcWriteLabel(label);
  gcMoveStackPointer(moved + 8);
  popContext();
  gcRestoreContext(c);
}

/**
 * Evaluación de los nodos de declaración de funciones
 */

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

/**
 * Evaluación de los nodos de operaciones numericas
 */

struct reg *evalCalculator(struct ast *a)
{
  struct reg *l = eval(a->l);
  struct reg *r = eval(a->r);
  struct reg *result, *free;

  if (!(((equalTypes(l->type, lookupTypeInSymbolTable("int"))) ||
         (equalTypes(l->type, lookupTypeInSymbolTable("float")))) &&
        ((equalTypes(r->type, lookupTypeInSymbolTable("int"))) ||
         (equalTypes(r->type, lookupTypeInSymbolTable("float"))))))
  {
    throwError(12);
  }

  gcRegisterNumericCalculation(a->nodetype, l, r);

  freeRegister(r);
  return l;
}

/**
 * Evaluación de los nodos de valores negativos
 */

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

/**
 * Función auxiliar para invertir las condiciones
 */

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

/**
 * Evaluación de los nodos condición
 */

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

/**
 * Evaluación de los nodos IF
 */

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

/**
 * Evaluación de los nodos WHILE
 */

void evalWhile(struct ast *a)
{
  int auxContinueLabel = continueLabel;
  int auxBreakLabel = breakLabel;
  continueLabel = getNextLabel();
  breakLabel = getNextLabel();

  gcWriteLabel(continueLabel);
  manageConditions(a->l, breakLabel);
  eval(a->r);
  gcJumpToLabel(continueLabel);
  gcWriteLabel(breakLabel);

  continueLabel = auxContinueLabel;
  breakLabel = auxBreakLabel;
}

/**
 * Evaluación de los nodos Continue
 */

void evalContinue()
{
  if (continueLabel != 0)
  {
    gcJumpToLabel(continueLabel);
  }
}

/**
 * Evaluación de los nodos Break
 */

void evalBreak()
{
  if (continueLabel != 0)
  {
    gcJumpToLabel(breakLabel);
  }
}

/**
 * Evaluación de los nodos Print
 */

void evalPrint(struct ast *a)
{
  struct context *c;
  struct reg *r0, *r1, *r2;
  int label;

  c = pushContext();
  gcWriteContext(c);
  label = getNextLabel();

  r0 = getRegister(lookupTypeInSymbolTable("int"), "R", 0);
  gcNumericConstant(r0, label);

  r1 = eval(a->l);

  if (a->r != NULL)
  {
    r2 = eval(a->r);
  }

  gcJumpToLabel(PRINT);
  gcWriteLabel(label);
  gcRestoreContext(c);
  popContext(c);
}

/**
 * Evaluación de los nodos
 */

struct reg *
eval(struct ast *a)
{
  printf("nodetype: %d\n", a->nodetype);
  struct reg *r = NULL;

  if (a->nodetype == 'L' || a->nodetype == 'P' || a->nodetype == 'W' ||
      a->nodetype == '0' || a->nodetype == 'U' || a->nodetype == 'I' ||
      a->nodetype == 'B' || a->nodetype == 'C')
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
  case '%':
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
  case 'W':
    evalWhile(a);
    break;
  case 'B':
    evalBreak();
    break;
  case 'C':
    evalContinue();
    break;
  case 'O':
    evalPrint(a);
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