#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "../ErrorHandler/ErrorHandler.h"

int _functionComparator(char *id, struct Symbol *s)
{
  return (strcmp(id, s->id) == 0 && isSymbolAFunction(s));
}

int _variableComparator(char *id, struct Symbol *s)
{
  return (strcmp(id, s->id) == 0 && !isSymbolAFunction(s) && s->scope == 0);
}

int _localVariableComparator(char *id, struct Symbol *s)
{
  return (strcmp(id, s->id) == 0 && !isSymbolAFunction(s) && s->scope > 0);
}

int _existsInSymbolTable(struct Symbol *s)
{
  if (isSymbolAFunction(s))
  {
    return lookupFunctionInSymbolTable(s->id) != NULL;
  }
  else
  {
    if (s->scope > 0)
    {

      lookupLocalVariableInSymbolTable(s->id, s->scope) != NULL;
    }
    else
    {
      return lookupVariableInSymbolTable(s->id) != NULL;
    }
  }
}

void _addToTypeSymbolTable(struct TypeSymbol *s)
{
  if (type_head)
  {
    if (!(type_tail->next = (type_node *)malloc(sizeof(type_node))))
    {
      throwError(1);
    }
    type_tail = type_tail->next;
  }
  else
  {
    type_head = (type_node *)malloc(sizeof(type_node));
    if (!type_head)
    {
      throwError(1);
    }
    type_tail = type_head;
  }
  type_tail->val = s;
}

void _addToSymbolTable(struct Symbol *s)
{

  if (symbol_head)
  {
    if (_existsInSymbolTable(s))
    {
      throwError(2);
    }
    if (!(symbol_tail->next = (symbol_node *)malloc(sizeof(symbol_node))))
    {
      throwError(1);
    }
    symbol_tail = symbol_tail->next;
  }
  else
  {
    symbol_head = (symbol_node *)malloc(sizeof(symbol_node));
    if (!symbol_head)
    {
      throwError(1);
    }
    symbol_tail = symbol_head;
  }
  symbol_tail->val = s;
}

void insertArrayToSymbolTable(char *id, int address, int length, struct TypeSymbol *type)
{
  struct Symbol *s;
  struct array *a;
  if (!(s = malloc(sizeof(struct Symbol))) || !(a = malloc(sizeof(struct array))))
  {
    throwError(1);
  }

  s->id = id;
  s->a = a;
  s->address = address;
  s->type = type;
  s->fun = NULL;
  a->length = length;

  _addToSymbolTable(s);
}

void insertVariableToSymbolTable(char *id, int address, struct TypeSymbol *type)
{
  struct Symbol *s;
  if (!(s = malloc(sizeof(struct Symbol))))
  {
    throwError(1);
  }

  s->id = id;
  s->a = NULL;
  s->address = address;
  s->type = type;
  s->fun = NULL;

  printf("Inserting %s\n", s->id);
  _addToSymbolTable(s);
}

void insertFunctionToSymbolTable(char *id, struct TypeSymbol *type, int label, int numberOfParams, int numberOfBytesRequiered)
{
  struct Symbol *s;
  struct function *f;
  if (!(s = malloc(sizeof(struct Symbol))) || !(f = malloc(sizeof(struct function))))
  {
    throwError(1);
  }

  s->id = id;
  s->a = NULL;
  s->address = -1;
  s->type = type;
  s->fun = f;
  f->label = label;
  f->numberOfParams = numberOfParams;
  f->numberOfSpaceRequired = numberOfBytesRequiered;

  _addToSymbolTable(s);
}

void insertLocalVariableToSymbolTable(char *id, int address, struct TypeSymbol *type, int scope, int length, int array, int reference)
{
  struct Symbol *s;
  if (!(s = malloc(sizeof(struct Symbol))))
  {
    throwError(1);
  }

  s->id = id;
  s->address = address;
  s->type = type;
  s->fun = NULL;
  s->scope = scope;
  if (array > 0)
  {
    s->a = malloc(sizeof(struct array));
    if (!s->a)
    {
      throwError(1);
    }
    s->a->length = length;
  }
  s->reference = reference;

  printf("Inserting Local\n");
  _addToSymbolTable(s);
}

void insertTypeToSymbolTable(char *name, int bytes, char qName)
{
  struct TypeSymbol *ts;
  if (!(ts = malloc(sizeof(struct Symbol))))
  {
    throwError(1);
  }

  ts->name = name;
  ts->bytes = bytes;
  ts->qName = qName;
  _addToTypeSymbolTable(ts);
}

struct Symbol *_geneticLookupInSymbolTable(char *id, int (*f)(char *, struct Symbol *))
{
  symbol_node *aux;
  if (!symbol_head)
  {
    return NULL;
  }

  aux = symbol_head;
  do
  {
    if ((*f)(id, aux->val))
    {
      return aux->val;
    }

    aux = aux->next;
  } while (aux);

  return NULL;
}

struct TypeSymbol *lookupTypeInSymbolTable(char *name)
{
  type_node *aux;
  if (!type_head)
    return NULL;

  aux = type_head;
  do
  {
    if (strcmp(name, aux->val->name) == 0)
    {
      return aux->val;
    }
    aux = aux->next;
  } while (aux != NULL);

  return NULL;
}

struct Symbol *lookupVariableInSymbolTable(char *id)
{
  return _geneticLookupInSymbolTable(id, _variableComparator);
}

struct Symbol *lookupFunctionInSymbolTable(char *id)
{
  return _geneticLookupInSymbolTable(id, _functionComparator);
}

struct Symbol *lookupLocalVariableInSymbolTable(char *id, int scope)
{
  symbol_node *aux;
  if (!symbol_head)
  {
    return NULL;
  }

  aux = symbol_head;
  do
  {
    if (strcmp(id, aux->val->id) == 0 && !isSymbolAFunction(aux->val) && aux->val->scope == scope)
    {
      return aux->val;
    }

    aux = aux->next;
  } while (aux);

  return NULL;
}

int isSymbolAFunction(struct Symbol *s)
{
  return s->fun != NULL;
}

int isSymbolAnArray(struct Symbol *s)
{
  return s->a != NULL;
}

void loadPrimitiveTypes()
{
  struct TypeSymbol *integer, *decimal, *character;

  if (!(integer = malloc(sizeof(struct TypeSymbol))) ||
      !(decimal = malloc(sizeof(struct TypeSymbol))) ||
      !(character = malloc(sizeof(struct TypeSymbol))))
  {
    throwError(1);
  }

  integer->bytes = 4;
  integer->name = "int";
  integer->qName = 'I';

  decimal->bytes = 8;
  decimal->name = "float";
  decimal->qName = 'D';

  character->bytes = 1;
  character->name = "char";
  character->qName = 'U';

  _addToTypeSymbolTable(integer);
  _addToTypeSymbolTable(decimal);
  _addToTypeSymbolTable(character);
}

int equalTypes(struct TypeSymbol *a, struct TypeSymbol *b)
{
  return strcmp(a->name, b->name) == 0;
}

int areTypesCompatible(struct TypeSymbol *a, struct TypeSymbol *b)
{
  return (equalTypes(a, b) ||
          ((strcmp(a->name, "int") || strcmp(a->name, "float")) &&
           ((strcmp(a->name, "int") || strcmp(a->name, "float")))));
}

int getDominantType(struct TypeSymbol *a, struct TypeSymbol *b)
{
  if (strcmp(b->name, "float"))
  {
    return 1;
  }

  return -1;
}

void printSymbolTableContent()
{
  type_node *aux = type_head;
  symbol_node *auxS = symbol_head;

  if (!type_head)
  {
    printf("TypeSymbolTable is empty\n");
  }
  else
  {
    printf("TypeSymbolTable :\n");

    do
    {
      printf("name: %s, bytes: %d, qName: %c\n", aux->val->name, aux->val->bytes, aux->val->qName);
      aux = aux->next;
    } while (aux != NULL);
  }

  if (!symbol_head)
  {
    printf("SymbolTable is empty\n");
  }
  else
  {
    printf("SymbolTable :\n");

    do
    {
      printf("name: %s, addr: 0x%x, type: %s, array: %d function: %d, local: %d\n", auxS->val->id,
             auxS->val->address, auxS->val->type->name,
             auxS->val->a != NULL, auxS->val->fun != NULL, auxS->val->scope);
      if (auxS->val->fun)
      {
        printf("\tlabel: %d, inputParams: %d, bytes: %d\n", auxS->val->fun->label,
               auxS->val->fun->numberOfParams, auxS->val->fun->numberOfSpaceRequired);
      }
      else if (auxS->val->a)
      {
        printf("\tlength: %d\n", auxS->val->a->length);
      }

      auxS = auxS->next;
    } while (auxS != NULL);
  }
}