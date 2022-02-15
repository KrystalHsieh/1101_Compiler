%option noyywrap
%{
#include "y.tab.h"
int col = 0;
%}

%%
[1-9]|[1-9][0-9]+ {
    col += yyleng;  
    yylval.ival = atoi(yytext);  
    return NUM;
}
"+" | "-" {col += yyleng;   yylval.loc = col;   return ADD_OR_SUB;}
"*" {col += yyleng;   yylval.loc = col;   return MUL;}
"^" {col += yyleng;   yylval.loc = col;   return TRANS;}
"("|")"|"["|"]"|","|"T" {col += yyleng;   return yytext[0];}
[ \t]+ {col += yyleng;}
. {return(yytext[0]);}
\n {return 0;}
%%