rm output miint.tab.h miint.tab.c lex.yy.c
bison -d ./flex-bison/miint.y
flex ./flex-bison/miint.l
gcc -o output miint.tab.c lex.yy.c ./SymbolTable/SymbolTable.c ./Ast/eval.c ./Ast/ast.c  ./ErrorHandler/ErrorHandler.c  \
./Qmanagedmnet/qManagment.c ./code-generation/codeGeneration.c ./flex-bison/utils.c -lfl -lm
./output < prueba_input