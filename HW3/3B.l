%option noyywrap
%{
#include "3B.tab.h"
int col = 0;
%}

%%
[1-9]|[1-9][0-9]+ {
    col += yyleng;
    yylval.ival = atoi(yytext);
    return NUM;
}
"*"|"^"|"+"|"-" {
    col += yyleng;
    yylval.loc = col;
    return(yytext[0]);
}
"("|")"|"["|"]"|"T"|","	{
    col += yyleng;
    return(yytext[0]);
}
[\t ]+ {col += yyleng;}
\n {return 0;}
. {return(yytext[0]);}
%%