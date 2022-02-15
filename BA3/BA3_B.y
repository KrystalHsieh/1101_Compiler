%{
#include <bits/stdc++.h>
using namespace std;
int yylex();
void yyerror(const char *message);
vector <int> list;
int n;
%}

%union {int ival;}
%type <ival> expr
%token <ival> DIGITS
%token ADD MUL LBR RBR COMMA Sum Term List MulDigit ListItem

%%
S     : Sum {return 0;}
      ; 
Sum   : Term ADD Sum
      | Term
Term  : List MUL MulDigit
      | MulDigit MUL List
      | MulDigit MUL List MUL MulDigit
      | List
      ;
MulDigit    : MulDigit MUL DIGITS   {}
            | DIGITS                {
                                          n = $$;
                                          vector <int> temp_list;
                                          for(int i=0; i<n; i++){
                                                list.push_back();
                                          }
                                    }
            ;
List  : LBR ListItem RBR
      ;
ListItem    : DIGITS COMMA ListItem {list.push_back($$);}
            | DIGITS                {list.push_back($$);}
            ;
%%
void yyerror (const char *message){fprintf (stderr, "%s\n",message);}

int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}