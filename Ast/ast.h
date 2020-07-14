struct reg
{
  int array;
  int length;
  int reference;
  struct TypeSymbol *type;
  char *label;
  int index;
};

struct ast
{
  int nodetype;
  struct ast *l;
  struct ast *r;
};

struct flow
{
  int nodetype;
  struct ast *body;
};

struct constant
{
  int nodetype;
  struct TypeSymbol *type;
  double nValue;
  char *sValue;
  int array;
};

struct ref
{
  int nodetype;
  int rightHand;
  char *id;
  struct ast *a;
};

struct declaration
{
  int nodetype;
  char *id;
  struct TypeSymbol *type;
  int length;
};

struct funAst
{
  int nodetype;
  char *id;
  struct TypeSymbol *type;
  struct ast *params;
  struct ast *body;
};

struct userCall
{
  int nodetype;
  struct Symbol *s;
  struct ast *params;
};

struct ast *newString(char *sValue);
struct ast *newChar(char *ch);
struct ast *newDeclaration(char *type, char *id);
struct ast *newArrayDeclaration(char *type, char *id, int length);
struct ast *newNumeric(char *type, double nValue);
struct ast *newReference(char *id);
struct ast *newIndexingReference(char *id, struct ast *index);
struct ast *newRightHandReference(struct ast *ref);
struct ast *newAssign(struct ast *l, struct ast *r);
struct ast *newList(struct ast *l, struct ast *r);
struct ast *newFuntion(char *type, char *id, struct ast *params, struct ast *body);
struct ast *newUserCall(char *id, struct ast *params);

struct ast *newAst(int nodetype, struct ast *l, struct ast *r);

struct ast *newNothing();

struct reg *eval(struct ast *a);
void treefree(struct ast *a);