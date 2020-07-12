/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno
%{
# include <string.h>
# include "./flex-bison/utils.h"
# include "miint.tab.h"
%}

%%
 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"%" |
"=" |
")" |
"(" |
"}" |
"{" |
"[" |
"]" |
"," |
";"  { return yytext[0]; }


    /* comparison ops, all are a CMP token */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"<>"    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

"and"   { return AND; }
"or"    { return OR; }
 /* Built-in types */
"int"                   { yylval.type = "int" ; return TYPE; }
"float"                 { yylval.type = "float"; return TYPE; }
"char"                  { yylval.type = "char"; return TYPE; }

"if"                    { return IF;}
"else"                  { return ELSE;}
"for"                   { return FOR;}
"while"                 { return WHILE;}

"str"                   { return STR; }
"print"                 { return PRINT; }
"println"               { return PRINTLN; }
"return"                { return RETURN; }
 /* names */
[a-zA-Z][a-zA-Z0-9]*   { yylval.name = substr(yytext, 0, yyleng); return NAME; }
\'(\\.|[^"\\])\'       { yylval.string = substr(yytext, 1, yyleng-1); return CHAR; } 
\"(\\.|[^"\\])*\"      { yylval.string = substr(yytext, 1, yyleng-1); return STRING; } 
[0-9]+"."[0-9]*  { yylval.d = atof(yytext); return NUMBER; }
[0-9]+           { yylval.i = atoi(yytext); return INTEGER; }


"//".*  
[ \t]  /* ignore whitespace */ 

\\\n { printf("c> "); } /* ignore line continuation */

\n   { return EOL; }

.       { yyerror("Mystery character %c\n", *yytext); }
%%