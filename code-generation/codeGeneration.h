void gcNumericConstant(struct reg *r, double nValue);
void gcReservePrimitiveSpace(int addr, struct TypeSymbol *type);
void gcCopyContentToRegister(struct reg *r, struct Symbol *s);
void gcCopyArrayToDirUsingRegister(struct reg *dst, struct reg *src);
void gcCopyAddrToRegister(struct reg *reg, int addr);
void gcSaveInMemoryUsingRegister(struct reg *dst, struct reg *src);
void gcStoreArrayInMemory(int addr, int bytes);
void gcStoreStringInMemory(int addr, char *s);
void gcStoreArrayDataInRegister(int addr, struct reg *r, struct TypeSymbol *type);
void gcStoreArrayDirInRegister(int addr, struct reg *r);

void gcMultiplyRegisterForNumericConstant(struct reg *r, struct TypeSymbol *type);

int isInFunction();
void gcWriteLabel(int label);
void gcStoreReturnLabelFromStackInRegister(struct reg *r);
void gcPrintGTFromRegister(struct reg *r);
void gcNewBase();
void gcRestoreBase();
void gcFreeLocalSpace();
void gcReserveSpaceForLocalVariables(int bytes);

void closeFiles();
int openFiles();
void inFunction();
void outsideFunction();