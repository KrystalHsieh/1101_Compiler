%{
    #include "equilibrium_cpp.tab.h"
    #include <string>
    void yyerror(const char *);
%}

%%
[0-9]+ {
    yylval.ival = atoi(yytext);
    return INTEGER;
}

[A-Z][a-z]? {
    std::string str(yytext);
    yylval.elem = str;
    return ELEM;
}

"->" {
    return ARROW;
}

\n|"+"|"("|")" {
    return yytext[0];
}

[ \t]+ {
    ;
}

. {
    yyerror("invalid input");
}

%%