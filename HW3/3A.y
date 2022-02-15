%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int yylex();
void yyerror(const char *message);
%}
%union {int ival;}
%type <ival> expr
%token <ival> INUMBER
%token ADD
%token SUB
%token MUL
%token MOD
%token INC
%token DEC
%token LOAD
%token END_OF_FILE

%%
input : expr {printf("%d", $1); return 0;}
      ; 
expr : LOAD INUMBER  {$$ = $2;}
     | expr expr ADD {$$ = $2 + $1;}
     | expr expr SUB {$$ = $2 - $1;}
     | expr expr MUL {$$ = $2 * $1;}
     | expr expr MOD {$$ = $2 % $1;}
     | expr INC {$$ = $1 + 1 ;}
     | expr DEC {$$ = $1 - 1 ;}
     | expr ADD {yyerror("Invalid"); return 0;}
     | expr SUB {yyerror("Invalid"); return 0;}
     | expr MUL {yyerror("Invalid"); return 0;}
     | expr MOD {yyerror("Invalid"); return 0;}
     ;
%%
void yyerror (const char *message){printf("Invalid format");}

int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}