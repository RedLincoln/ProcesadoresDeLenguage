#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "../Ast/ast.h"
#include "../SymbolTable/SymbolTable.h"
#include "../ErrorHandler/ErrorHandler.h"
#include "../Qmanagedmnet/qManagment.h"

int scope;
char *output_file = "out.q.c";
char *tmpFunc = ".tmp_fnc";
char *tmpMain = ".tmp_main";
int stat = -1;
int code = 0;

FILE *funFile;
FILE *mainFile;
FILE *output;

void inFunction()
{
  scope = 1;
}

void outsideFunction()
{
  scope = 0;
}

int isInFunction()
{
  return scope;
}

int openFiles()
{
  funFile = fopen(tmpFunc, "w+");
  mainFile = fopen(tmpMain, "w+");

  if (!funFile || !mainFile)
  {
    throwError(4);
  }

  return 0;
}

void writeInTmpFile(char *format, ...)
{
  va_list ap;
  va_start(ap, format);

  vfprintf(scope == 1 ? funFile : mainFile, format, ap);

  va_end(ap);
}

void writeOutputFile(char *format, ...)
{
  va_list ap;
  va_start(ap, format);

  vfprintf(output, format, ap);

  va_end(ap);
}

void manageStat()
{
  if (scope == 0 && code > stat)
  {
    writeInTmpFile("\tSTAT(%d)\n", code);
    stat = code;
  }
}

void manageCode()
{
  if (scope == 0 && code == stat)
  {
    writeInTmpFile("\tCODE(%d)\n", code);
    code++;
  }
}

void closeFiles()
{
  int c;

  if (!(output = fopen(output_file, "w")))
  {
    throwError(4);
  }

  manageCode();

  fseek(mainFile, 0, SEEK_SET);
  fseek(funFile, 0, SEEK_SET);

  writeOutputFile("#include \"Qlib.h\"\n");
  writeOutputFile("#include \"Q.h\"\n\n");
  writeOutputFile("BEGIN\n");

  while ((c = fgetc(funFile)) != EOF)
  {
    fputc(c, output);
  }

  writeOutputFile("L 0:\n");

  while ((c = fgetc(mainFile)) != EOF)
  {
    fputc(c, output);
  }

  writeOutputFile("\t\tGT(-2);\n");
  writeOutputFile("END\n");

  fclose(funFile);
  fclose(mainFile);
  fclose(output);
}

void gcNumericConstant(struct reg *r, double value)
{
  writeInTmpFile("\t\t%s%d = ", r->label, r->index);
  if (strcmp(r->label, "R") == 0)
  {
    writeInTmpFile("%d;\n", (int)value);
  }
  else
  {
    writeInTmpFile("%f;\n", value);
  }
}

void gcReservePrimitiveSpace(int addr, struct TypeSymbol *type)
{
  int space = type->bytes < 4 ? 4 : type->bytes;
  if (!scope)
  {
    manageStat();
    writeInTmpFile("\t\tMEM(0x%x, %d);\n", addr, space);
  }
}

void gcCopyContentToRegister(struct reg *r, struct Symbol *s)
{
  char sign;
  manageCode();
  if (!isInFunction())
    writeInTmpFile("\t\t%s%d = %c(0x%x);\n", r->label, r->index, s->type->qName, s->address);
  else
  {
    sign = s->address < 0 ? '-' : '+';
    writeInTmpFile("\t\t%s%d = %c(R6%c%d);\n", r->label, r->index, s->type->qName, sign, abs(s->address));
  }
}

void gcCopyAddrToRegister(struct reg *r, int addr)
{
  char sign;
  manageCode();
  if (!isInFunction())
    writeInTmpFile("\t\t%s%d = 0x%x;\n", r->label, r->index, addr);
  else
  {
    sign = addr < 0 ? '-' : '+';
    writeInTmpFile("\t\t%s%d = R6%c%d;\n", r->label, r->index, sign, abs(addr));
  }
}

void gcSaveInMemoryUsingRegister(struct reg *dst, struct reg *src)
{
  manageCode();
  writeInTmpFile("\t\t%c(%s%d) = %s%d;\n", dst->type->qName, dst->label, dst->index, src->label, src->index);
}

void gcStoreArrayInMemory(int addr, int bytes)
{
  if (!scope)
  {
    manageStat();
    writeInTmpFile("\t\tFIL(0x%x, %d, 0);\n", addr, bytes);
  }
}

void gcStoreStringInMemory(int addr, char *s)
{
  int aux = scope;
  scope = 0;
  manageStat();
  writeInTmpFile("\t\tSTR(0x%x, \"%s\");\n", addr, s);
  scope = aux;
}

void gcStoreArrayDirInRegister(int addr, struct reg *r)
{
  char sign;
  manageCode();
  if (!isInFunction())
    writeInTmpFile("\t\t%s%d = 0x%x+%s%d;\n", r->label, r->index, addr, r->label, r->index);
  else
  {
    sign = addr < 0 ? '-' : '+';
    writeInTmpFile("\t\tI(R7-4) = %s%d;\n", r->label, r->index);
    writeInTmpFile("\t\t%s%d = R6%c%d;\n", r->label, r->index, sign, abs(addr));
    writeInTmpFile("\t\t%s%d = I(R7-4) + %s%d;\n", r->label, r->index, r->label, r->index);
  }
}

void gcStoreArrayDataInRegister(int addr, struct reg *r, struct TypeSymbol *type)
{
  char sign;
  manageCode();
  if (!isInFunction())
    writeInTmpFile("\t\t%s%d = %c(0x%x+%s%d);\n", r->label, r->index, type->qName, addr, r->label, r->index);
  else
  {
    sign = addr < 0 ? '-' : '+';
    gcStoreArrayDirInRegister(addr, r);
    writeInTmpFile("\t\t%s%d = %c(%s%d);\n", r->label, r->index, type->qName,
                   r->label, r->index, r->label, r->index);
  }
}

void gcMultiplyRegisterForNumericConstant(struct reg *r, struct TypeSymbol *type)
{
  manageCode();
  writeInTmpFile("\t\t%s%d = %s%d * %d;\n", r->label, r->index, r->label, r->index, type->bytes);
}

void gcCopyArrayToDirUsingRegister(struct reg *dst, struct reg *src)
{
  manageCode();
  writeInTmpFile("\t\tCopy with a for look;\n");
}

void gcWriteLabel(int label)
{
  manageCode();
  writeInTmpFile("L %d:\n", label);
}

void gcNewBase()
{
  writeInTmpFile("\t\tR6=R7;\n");
}

void gcRestoreBase()
{
  writeInTmpFile("\t\tR6=P(R7+4);\n");
}

void gcFreeLocalSpace()
{
  writeInTmpFile("\t\tR7=R6;\n");
}

void gcWriteContext(struct context *c)
{
  int count = 0;
  int countUp = 0;
  manageCode();
  for (int i = 0; i < sizeof(c->R) / sizeof(c->R[0]); i++)
  {
    if (c->R[i] != 0)
    {
      count += 4;
    }
  }

  for (int i = 0; i < sizeof(c->RR) / sizeof(c->RR[0]); i++)
  {
    if (c->RR[i] != 0)
    {
      count += 8;
    }
  }

  writeInTmpFile("\t\tR7 = R7 - %d;\n", count);

  for (int i = 0; i < sizeof(c->R) / sizeof(c->R[0]); i++)
  {
    if (c->R[i] != 0)
    {
      writeInTmpFile("\t\tI(R7 + %d) = R%d;\n", countUp, i);
      countUp += 4;
    }
  }

  for (int i = 0; i < sizeof(c->RR) / sizeof(c->RR[0]); i++)
  {
    if (c->RR[i] != 0)
    {
      writeInTmpFile("\t\tD(R7 + %d) = RR%d;\n", countUp, i);
      countUp += 8;
    }
  }
}

void gcRestoreContext(struct context *c)
{
  int countUp = 0;
  manageCode();
  for (int i = 0; i < (sizeof(c->R) / sizeof(c->R[0])); i++)
  {
    if (c->R[i] != 0)
    {
      writeInTmpFile("\t\tR%d = I(R7 + %d);\n", i, countUp);
      countUp += 4;
    }
  }

  for (int i = 0; i < sizeof(c->RR) / sizeof(c->RR[0]); i++)
  {
    if (c->RR[i] != 0)
    {
      writeInTmpFile("\t\tRR%d = D(R7 + %d);\n", i, countUp);
      countUp += 8;
    }
  }

  writeInTmpFile("\t\tR7 = R7 + %d;\n", countUp);
}

void gcReserveSpaceForLocalVariables(int bytes)
{
  writeInTmpFile("\t\tR7=R7-%d;\n", bytes);
}

void gcSaveActualBase()
{
  manageCode();
  writeInTmpFile("\t\tP(R7+4) = R6;\n");
}

void gcSaveReturningLabel(int label)
{
  writeInTmpFile("\t\tP(R7) = %d;\n", label);
}

void gcJumpToLabel(int label)
{
  writeInTmpFile("\t\tGT(%d);\n", label);
}

void gcStoreReturnLabelFromStackInRegister(struct reg *r)
{
  manageCode();
  writeInTmpFile("\t\t%s%d = P(R7);\n", r->label, r->index);
}

void gcPrintGTFromRegister(struct reg *r)
{
  manageCode();
  writeInTmpFile("\t\tGT(%s%d);\n", r->label, r->index);
}

void gcMoveStackPointer(int offset)
{
  int sign = offset < 0 ? '-' : '+';
  offset = abs(offset) < 4 ? 4 : abs(offset);
  manageCode();
  writeInTmpFile("\t\tR7 = R7%c%d;\n", sign, offset);
}

void gcRegisterNumericCalculation(int operation, struct reg *l, struct reg *r)
{
  manageCode();
  writeInTmpFile("\t\t%s%d = %s%d%c%s%d;\n", l->label, l->index, l->label, l->index, operation, r->label, r->index);
}

void gcMultiplyByConstant(struct reg *r, int value)
{
  manageCode();
  writeInTmpFile("\t\t%s%d = %s%d * %d;\n", r->label, r->index, r->label, r->index, value);
}