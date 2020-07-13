#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "../SymbolTable/SymbolTable.h"
#include "../ErrorHandler/ErrorHandler.h"

struct ast *newString(char *sValue)
{
  struct constant *c = malloc(sizeof(struct constant));
  if (!c)
    throwError(1);

  c->nodetype = 'K';
  c->type = lookupTypeInSymbolTable("char");
  c->array = 1;
  c->sValue = sValue;

  return (struct ast *)c;
}

struct ast *newChar(char *ch)
{
  struct constant *c = malloc(sizeof(struct constant));
  if (!c)
    throwError(1);

  c->nodetype = 'K';
  c->sValue = ch;
  c->type = lookupTypeInSymbolTable("char");

  return (struct ast *)c;
}

struct ast *newNumeric(char *type, double nValue)
{
  struct constant *c = malloc(sizeof(struct constant));
  if (!c)
    throwError(1);

  c->nodetype = 'K';
  c->type = lookupTypeInSymbolTable(type);
  c->nValue = nValue;

  return (struct ast *)c;
}

struct ast *newDeclaration(char *type, char *id)
{
  struct declaration *d = malloc(sizeof(struct declaration));
  if (!d)
  {
    throwError(1);
  }

  d->nodetype = 'D';
  d->id = id;
  d->type = lookupTypeInSymbolTable(type);
  d->length = -1;

  return (struct ast *)d;
}

struct ast *newArrayDeclaration(char *type, char *id, int length)
{
  struct declaration *d = (struct declaration *)(newDeclaration(type, id));
  d->length = length;

  return (struct ast *)d;
}

struct ast *newReference(char *id)
{
  struct ref *r = malloc(sizeof(struct ref));
  if (!r)
  {
    throwError(1);
  }

  r->nodetype = 'R';
  r->id = id;
  r->a = NULL;

  return (struct ast *)r;
}

struct ast *newIndexingReference(char *id, struct ast *index)
{
  struct ref *r = (struct ref *)newReference(id);
  r->a = index;

  return (struct ast *)r;
}

struct ast *newRightHandReference(struct ast *ref)
{
  struct ref *r = (struct ref *)ref;
  r->rightHand = 1;

  return (struct ast *)r;
}

struct ast *newAssign(struct ast *l, struct ast *r)
{
  struct ast *a = malloc(sizeof(struct ast));
  if (!a)
  {
    throwError(1);
  }

  a->nodetype = '=';
  a->l = l;
  a->r = r;

  return a;
}

struct ast *newList(struct ast *l, struct ast *r)
{
  struct ast *a = malloc(sizeof(struct ast));

  if (!a)
  {
    throwError(1);
  }

  a->nodetype = 'L';
  a->l = l;
  a->r = r;

  return a;
}

struct ast *newFuntion(char *type, char *id, struct ast *params, struct ast *body)
{
  struct funAst *f = malloc(sizeof(struct funAst));

  if (!f)
  {
    throwError(1);
  }

  f->nodetype = 'P';
  f->id = id;
  f->type = lookupTypeInSymbolTable(type);
  f->params = params;
  f->body = body;

  return (struct ast *)f;
}

struct ast *newNothing()
{
  struct ast *a = malloc(sizeof(struct ast));
  if (!a)
  {
    throwError(1);
  }
  a->nodetype = '0';
  return a;
}