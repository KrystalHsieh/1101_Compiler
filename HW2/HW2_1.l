%{
#include <stdio.h>
#include <stdlib.h>
int count = 0;
int newline = 1;
%}

LBR [{]
RBR [}]

%%
{LBR} {
    if(newline == 1){for(int i=0; i<count; i++){printf("\t");}}
    count++;
    printf("%s", yytext);
    newline = 0;
}
{RBR} {
    count--;
    if(newline == 1){for(int i=0; i<count; i++){printf("\t");}}
    printf("%s", yytext);
    newline = 0;
}
\n {printf("\n"); newline = 1;}
[^{}\n\t]+ {
    if(newline == 1){for(int i=0; i<count; i++){printf("\t");}}
    printf("%s", yytext);
    newline = 0;
}
<<EOF>> {return 0;}
%%

int main(int argc, char *argv[]){

    yylex();
    return 0;
}