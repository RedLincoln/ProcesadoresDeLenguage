void gcNumericConstant(struct reg *r, double nValue);
void gcReservePrimitiveSpace(int addr, struct TypeSymbol *type);
void gcCopyContentToRegister(struct reg *r, struct Symbol *s);
void gcCopyArrayToDirUsingRegister(struct reg *dst, struct reg *src);
void gcCopyAddrToRegister(struct reg *reg, int addr);
void gcSaveInMemoryUsingRegister(struct reg *dst, struct reg *src);
void gcStoreArrayInMemory(int addr, int bytes);
void gcStoreStringInMemory(int addr, char *s);
void gcStoreArrayDataInRegister(int addr, struct reg *r, struct TypeSymbol *type, struct reg *free);
void gcStoreArrayAddressInRegister(int addr, struct reg *r);
void gcStoreArrayDirInRegister(int addr, struct reg *r, struct reg *free);

void gcMultiplyRegisterForNumericConstant(struct reg *r, struct TypeSymbol *type);

void gcStorePointerInRegisterInTheSameRegister(struct reg *r);
int isInFunction();
void gcWriteLabel(int label);
void gcStoreReturnLabelFromStackInRegister(struct reg *r);
void gcPrintGTFromRegister(struct reg *r);
void gcNewBase();
void gcRestoreBase();
void gcFreeLocalSpace();
void gcReserveSpaceForLocalVariables(int bytes);
void gcMoveStackPointer(int offset);

void gcSaveActualBase();
void gcSaveReturningLabel(int label);
void gcJumpToLabel(int label);
void gcWriteContext(struct context *c);
void gcRestoreContext(struct context *c);

void gcWriteConditionUsingRegister(struct reg *r, int label);
void gcRegisterNumericCalculation(int operation, struct reg *l, struct reg *r);
void gcMultiplyByConstant(struct reg *r, int value);
void gcWritLogicalOperation(char *operation, struct reg *l, struct reg *r);

void gcCopyArrayToArrayUsingRegister(struct reg *l, struct reg *r, struct reg *free, int length);

void closeFiles();
int openFiles();
void inFunction();
void outsideFunction();