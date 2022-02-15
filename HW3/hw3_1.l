%option noyywrap
%{
#include "y.tab.h"
%}

eof             \n
multi_tab       [ \t]+
number          [0-9]+

%%
{eof}           {}
{multi_tab}     {}
{number}	{ yylval.ival = atoi(yytext); return(INUMBER);}
add		{ yylval.word = strdup(yytext); return(ADD); }
sub		{ yylval.word = strdup(yytext); return(SUB); }
mod		{ yylval.word = strdup(yytext); return(MOD); }
mul		{ yylval.word = strdup(yytext); return(MUL); }
inc		{ yylval.word = strdup(yytext); return(INC); }
dec		{ yylval.word = strdup(yytext); return(DEC); }
load		{ yylval.word = strdup(yytext); return(LOAD); }
.		{}
%%
