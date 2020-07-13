
/* calculator with AST */

%{
#include <stdio.h>
#include <stdlib.h>
#include "SymbolTable/SymbolTable.h"
#include "Ast/ast.h"
#include "code-generation/codeGeneration.h"
%}

%union {
  struct ast *a;
  char *name;
  double d;
  struct Symbol *s;             /* which symbol */
  struct symlist *sl;
  char *type;
  int fn;                       /* which function */
  int i;
  char *string;
  struct variable *v;
}

/* declare tokens */
%token <d> NUMBER
%token <i> INTEGER
%token <string> STRING CHAR
%token <name> NAME
%token <type> TYPE
%token EOL 
%token IF ELSE WHILE FOR 
%token PRINT RETURN PRINTLN STR
%token AND OR

%nonassoc <fn> CMP

%right '='
%left '+' '-'
%left '*' '/'
%left '(' ')'

%type <a> exp stmt declaration leftHand fun_declaration declarationList expList paramList

%start calclist

%%

calclist : /* nothing */
         | calclist fun_declaration EOL {
                eval($2);
                treefree($2);
                }
         | calclist stmt EOL {
                eval($2);
                treefree($2);
                }
         | calclist EOL
         | calclist error EOL { yyerrok; printf("> "); }
         ;

stmt  : exp
      | declaration
      ;


exp : '(' exp ')'                     { $$ = $2; }
    | leftHand '=' exp                { $$ = newAssign($1, $3); }
    | NUMBER                          { $$ = newNumeric("float", $1); }
    | INTEGER                         { $$ = newNumeric("int",$1); }
    | STRING                          { $$ = newString($1); }
    | CHAR                            { $$ = newChar($1); }
    | NAME '(' paramList ')'          { $$ = newUserCall($1, $3); }
    | leftHand                        { $$ = newRightHandReference($1); }
    ;

paramList :                     { $$ = NULL; }
          | exp
          | exp ',' paramList   { $$ = newList($1, $3); }
          ;
          
declaration : TYPE NAME                   { $$ = newDeclaration($1, $2); }
            | TYPE NAME '[' INTEGER ']'   { $$ = newArrayDeclaration($1, $2, $4); }
            ;

declarationList : declaration                       
                | declaration ',' declarationList   { $$ = newList($1, $3); }
                ;
              
expList         : stmt EOL          { $$ = $1; }
                | stmt EOL expList  { $$ = newList($1, $3); }
                | EOL               { $$ = newNothing(); }
                ;

fun_declaration : TYPE NAME '(' declarationList ')' '{' EOL expList '}' { $$ = newFuntion($1, $2, $4, $8); }
                ;

leftHand : NAME                       { $$ = newReference($1); }
         | NAME '[' exp ']'           { $$ = newIndexingReference($1, $3); }
         ;

%%

int
main()
{
  openFiles();
  loadPrimitiveTypes();
  int exit_code = yyparse();
  printSymbolTableContent();
  closeFiles();
  return exit_code;
}