%{
#include <stdio.h>
#include <stdlib.h>
int count_ht = 0;
int link_text_loc = 0;
int text_loc = 0;
%}

hashtag [#]
whitespace [ ]
text [a-zA-Z0-9 ]
divider [-]
link_text [a-zA-Z0-9 /?:.&=”’,-_]
check [Xx]

%%

{hashtag}+{whitespace}{text}* {
    count_ht = 0;
    for(int i=0; i < yyleng; i++){
        if(yytext[i] == '#'){count_ht++;}
    }
    printf("<h%d>", count_ht);
    for(int i=count_ht+1; i < yyleng; i++){
        printf("%c", yytext[i]);
    }
    printf("</h%d>", count_ht);
}
  
{divider}{divider}{divider} {printf("<hr />");}

!\[{text}*\]\({link_text}*\) {
    printf("<img alt=\"");
    for(int i=2; i<yyleng; i++){
        if(yytext[i] == ']'){
            link_text_loc = i+2;
            break;
        }
        printf("%c", yytext[i]);
    }
    
    printf("\" src=\"");
    for(int i=link_text_loc; i<yyleng-1; i++){
        printf("%c", yytext[i]);
    }
    printf("\">");
}

{divider}{whitespace}\[{check}\]{whitespace}{text}* {
    printf("<p>\n\t<input checked=\"checked\" type=\"checkbox\" /> ");
    for(int i=6; i<yyleng; i++){printf("%c", yytext[i]);}
    printf("\n</p>");
}

{divider}{whitespace}\[{whitespace}\]{whitespace}{text}* {
    printf("<p>\n\t<input type=\"checkbox\" /> ");
    for(int i=6; i<yyleng; i++){printf("%c", yytext[i]);}
    printf("\n</p>");
}

^\n {printf("\n");}
. {}
<<EOF>> {return 0;}
%%

int main(int argc, char *argv[]){

    yylex();
    return 0;
}