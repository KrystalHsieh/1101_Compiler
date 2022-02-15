%option noyywrap
%{
#include "3A.tab.h"
%}

%%
[0-9]+ {
    yylval.ival = atoi(yytext);
    return(INUMBER);
}
"add" {return ADD;}
"sub" {return SUB;}
"mul" {return MUL;}
"mod" {return MOD;}
"inc" {return INC;}
"dec" {return DEC;}
"load" {return LOAD;}
\n {}
[ \t]+ {}
. {return (yytext[0]);}
<<EOF>> {return END_OF_FILE;}
%%