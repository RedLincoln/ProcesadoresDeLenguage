
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
%token IF ELSE WHILE BREAK CONTINUE
%token PRINT 

%nonassoc <fn> CMP

%right '='
%left '+' '-'
%left '*' '/'
%left '(' ')'
%nonassoc UMINUS

%type <a> exp stmt declaration leftHand fun_declaration declarationList expList paramList cond

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

stmt  : IF '(' cond ')' '{' EOL expList '}'                           { $$ = newIf($3, $7, NULL); }
      | IF '(' cond ')' '{' EOL expList '}' ELSE '{' EOL expList '}'  { $$ = newIf($3, $7, $12); }
      | WHILE '(' cond ')' '{' EOL expList '}'                         { $$ = newAst('W',$3,$7); }
      | exp
      | declaration
      | NAME '(' paramList ')'          { $$ = newUserCall($1, $3); }
      | BREAK                           { $$ = newAst('B', NULL, NULL); }
      | CONTINUE                        { $$ = newAst('C', NULL, NULL); }
      | PRINT '(' STRING ',' exp ')'    { $$ = newAst('O', newString($3), $5); }
      ;


cond: exp CMP exp                     { $$ = newAst($2, $1, $3);}
    ;

exp : '(' exp ')'                     { $$ = $2; }
    | exp '+' exp                     { $$ = newAst('+', $1, $3); }
    | exp '-' exp                     { $$ = newAst('-', $1, $3); }
    | exp '*' exp                     { $$ = newAst('*', $1, $3); }
    | exp '/' exp                     { $$ = newAst('/', $1, $3); }
    | '-' exp %prec UMINUS            { $$ = newAst('M', $2, NULL); }
    | leftHand '=' exp                { $$ = newAssign($1, $3); }
    | NUMBER                          { $$ = newNumeric("float", $1); }
    | INTEGER                         { $$ = newNumeric("int",$1); }
    | STRING                          { $$ = newString($1); }
    | CHAR                            { $$ = newChar($1); }
    | leftHand                        { $$ = newRightHandReference($1); }
    ;

paramList :                     { $$ = NULL; }
          | exp
          | exp ',' paramList   { $$ = newList($1, $3); }
          ;
          
declaration : TYPE NAME                   { $$ = newDeclaration($1, $2); }
            | TYPE NAME '=' exp           { $$ = newList(newDeclaration($1, $2),
                                                 newAssign(newReference($2), $4)); }
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