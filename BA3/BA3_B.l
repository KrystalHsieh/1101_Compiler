%option noyywrap
%{
#include "y.tab.h"
%}

%%
[0-9]+ {
    yylval.ival = atoi(yytext);
    return(DIGITS);
}
"," {return COMMA;}
"[" {return LBR;}
"]" {return RBR;}
"*" {return MUL;}
"+" {return ADD;}
\n {}
[ \t]+ {}
<<EOF>> {return 0;}
. {return (yytext[0]);}
%%