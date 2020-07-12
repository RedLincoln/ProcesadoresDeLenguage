
struct context
{
  int R[6];
  int RR[4];
};

typedef struct c_node
{
  struct context *val;
  struct c_node *next;
  struct c_node *last;
} context_stack;

context_stack *last;

struct reg *assignRegister(struct TypeSymbol *type);
void freeRegister(struct reg *r);
void freeAllRegisters();
int getNextFreeAddress(int bytes);
int getNextLabel();

struct context *pushContext();
void popContext();