struct TypeSymbol
{
  char *name;
  int bytes;
  char qName;
};

struct array
{
  int length;
};

struct function
{
  int numberOfParams;
  int numberOfSpaceRequired;
  int label;
};

struct Symbol
{
  char *id;
  struct TypeSymbol *type;
  struct array *a;
  struct function *fun;
  int address;
  int scope;
  int reference;
};

typedef struct node
{
  struct Symbol *val;
  struct node *next;
} symbol_node;

typedef struct node_t
{
  struct TypeSymbol *val;
  struct node_t *next;
} type_node;

type_node *type_head, *type_tail;
symbol_node *symbol_head, *symbol_tail;

void insertArrayToSymbolTable(char *id, int address, int length, struct TypeSymbol *type);
void insertVariableToSymbolTable(char *id, int address, struct TypeSymbol *type);
void insertLocalVariableToSymbolTable(char *id, int address, struct TypeSymbol *type, int scope, int length, int array, int reference);
void insertFunctionToSymbolTable(char *id, struct TypeSymbol *type, int label, int numberOfParams, int numberOfBytesRequiered);
void insertTypeToSymbolTable(char *name, int bytes, char qName);
int areTypesCompatible(struct TypeSymbol *a, struct TypeSymbol *b);
int getDominantType(struct TypeSymbol *a, struct TypeSymbol *b);
struct TypeSymbol *lookupTypeInSymbolTable(char *name);
struct Symbol *lookupVariableInSymbolTable(char *id);
struct Symbol *lookupLocalVariableInSymbolTable(char *id, int scope);
struct Symbol *lookupFunctionInSymbolTable(char *id);
void loadPrimitiveTypes();
void printSymbolTableContent();
int isSymbolAFunction(struct Symbol *s);
int isSymbolAnArray(struct Symbol *s);
int equalTypes(struct TypeSymbol *a, struct TypeSymbol *b);