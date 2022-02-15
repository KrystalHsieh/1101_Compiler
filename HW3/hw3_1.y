%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void yyerror(const char *message);
int top=-1;
int okToPrint=1;
int prev=0;
int yylex();
%}

%union{
int ival;
char* word;
}

%token <ival> INUMBER
%token <word> ADD
%token <word> SUB
%token <word> MUL
%token <word> MOD
%token <word> INC
%token <word> DEC
%token <word> LOAD

%type <ival> line

%left '+''-''*''%'

%%
input		:line		{if(top==0 && okToPrint==1){printf("%d\n",$1); return(0);}
				else{printf("Invalid format\n");return(0); }} 
		;
line		:line line	{$<ival>$ = $<ival>2;}
		|ADD		{if(top < 1) okToPrint=0; $$ = $<ival>0 + prev; top--; }
		|SUB            {if(top < 1) okToPrint=0; $$ = $<ival>0 - prev; top--; }
		|MUL            {if(top < 1) okToPrint=0; $$ = $<ival>0 * prev; top--; }
		|MOD            {if(top < 1) okToPrint=0; $$ = $<ival>0 % prev; top--; }
		|INC            {if(top==-1) okToPrint=0; $$ = $<ival>0 + 1; }
		|DEC            {if(top==-1) okToPrint=0; $$ = $<ival>0 - 1; }
		|LOAD INUMBER	{top++; $$ = $<ival>2; prev = $<ival>0; }
		|INUMBER {yyerror("Invalid");}		
		;
%%
void yyerror(const char *message)
{
        printf("Invalid format\n");
}

int main(int argc, char *argv[]){
        yyparse();
        return(0);
}
