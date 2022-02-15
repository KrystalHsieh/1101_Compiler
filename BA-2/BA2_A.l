%{
#include <stdio.h>
#include <stdlib.h>
%}

dot [.]
sign [+|-]
i [0-9]
exp [E|e]


%%

^{i}+{exp}{sign}{i}+$ {printf("%s\n", yytext);}
^{i}+{dot}{i}*$ {printf("%s\n", yytext);}
^{i}*{dot}{i}+$ {printf("%s\n", yytext);}
^{i}*{dot}{i}+{exp}{sign}{i}+$ {printf("%s\n", yytext);}
^{i}*{dot}{i}+{exp}{i}+$ {printf("%s\n", yytext);}
^({i}*{dot}{i}+{exp}{sign}{i}+{dot}{i}*)$ {printf("%s\n", yytext);}
^{i}*{dot}{i}+{exp}{sign}{i}*{dot}{i}+$ {printf("%s\n", yytext);}
^{i}+{exp}{i}+$ {printf("%s\n", yytext);}
^{i}*{dot}{exp}{i}+$ {printf("%s\n", yytext);}
\n {}
. {}
<<EOF>> {return 0;}
%%

int main(int argc, char *argv[]){

    yylex();
    return 0;
}