%{
#include <stdio.h>
#include <stdlib.h>
int count_ht = 0;
int link_text_loc = 0;
int text_loc = 0;
int count_star = 0;
int newstar = 0;
int newline = 0;
int strong = 0;
%}

hashtag [#]
whitespace [ ]
text [a-zA-Z0-9 ]
divider [-]
link_text [a-zA-Z0-9 /?!:.()&=”’,-_'"]
check [Xx]
list_mark [*]
newline_mark [>]

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

({list_mark}{whitespace}{text}*\n)+{divider}{divider}{divider} {
    printf("<ul>\n");
    for(int i=0; i<yyleng-3; i++){
        if(yytext[i] == '\n'){
            printf("</li>\n");
        }
        else if(newstar && yytext[i] == ' '){
            newstar = 0;
            printf("\t<li>");
        }
        else if(yytext[i] == '*'){newstar = 1;}
        else {printf("%c", yytext[i]);}
    }
    printf("</ul>\n<hr />");
}

\[{text}*\]\({link_text}*\) {
    printf("<a href=\"");
    for(int i=0; i<yyleng; i++){
        if(yytext[i] == '('){link_text_loc = i+1;break;}
    }
    for(int i=link_text_loc; i<yyleng-1; i++){printf("%c", yytext[i]);}
    printf("\">\n\t<span>");
    for(int i=1; i<yyleng; i++){
        if(yytext[i] == ']'){break;}
        printf("%c", yytext[i]);
    }
    printf("</span>\n</a>");
}

({newline_mark}{whitespace}({link_text}*({list_mark}{list_mark}{text}*{list_mark}{list_mark})*{link_text}*)*\n)+{divider}{divider}{divider} {
    printf("<blockquote>\n");
    for(int i=0; i<yyleng-3; i++){
        if(yytext[i] == '>'){newline = 1;}
        else if(newline && yytext[i] == ' '){newline = 0;}
        else if(yytext[i] == '*'){
            strong++;
            if(strong == 1){printf("<strong>");}
            if(strong == 4){
                printf("</strong>");
                strong = 0;
            }
        }
        else if(yytext[i] == '\n'){
            printf("\n");
            newline = 1;
        }
        else {printf("%c", yytext[i]);}
    }
    printf("</blockquote>\n<hr />");
}

^\n {printf("\n");}
. {}
<<EOF>> {return 0;}
%%

int main(int argc, char *argv[]){

    yylex();
    return 0;
}