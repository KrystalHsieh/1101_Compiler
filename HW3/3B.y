%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void sematic_error(int col);
void yyerror(const char *message);
int yylex();
%}

%union {
int ival;
int loc;
struct def{ int i;  int j;} m;
}
%type <m> matrix
%token <ival> NUM
%token <loc> '+'
%token <loc> '-'
%token <loc> '*'
%left '+' '-'
%left '*'
%left '^'
%%
line : matrix {printf("Accepted");}
	 ;
matrix : '[' NUM ',' NUM ']' {$$.i = $2; $$.j = $4;}
	   | matrix '+' matrix {
                            if ($1.i==$3.i && $1.j==$3.j){$$ = $1;}
							else {sematic_error($2);   return 0;}
		}
	   | matrix '-' matrix {
							if ($1.i==$3.i && $1.j==$3.j){$$ = $1;}
							else {sematic_error($2);   return 0;}
		}
	   | matrix '*' matrix {
							if ($1.j==$3.i){
								$$.i = $1.i;
								$$.j = $3.j;
							}
							else {sematic_error($2);  return 0;}
        }
	   | matrix '^' 'T' {$$.i = $1.j;  $$.j = $1.i;}
	   | '(' matrix ')'	{$$ = $2;}
	   ;
%%
void sematic_error(int col){printf("Semantic error on col %d\n", col);}
void yyerror (const char *message){fprintf (stderr, "%s\n",message);}

int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}