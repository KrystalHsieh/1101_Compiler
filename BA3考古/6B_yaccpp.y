%code requires {
    #include <iostream>
    #include <string>
    #include <map>

    int yylex(void);
    void yyerror(const char *);

    std::map<std::string, int> merge_map(std::map<std::string, int>, std::map<std::string, int>);
    std::map<std::string, int> diff_map(std::map<std::string, int>, std::map<std::string, int>);
    void print_map(std::map<std::string, int>);

    struct Type {
        int ival;
        std::string elem;
        std::map<std::string, int> dict;
    };
    
    #define YYSTYPE Type  // for cpp and c (bison itself) compatibility
}

/* This section defines the additional function using the data type in
 * `%code requires` section.
*/
%code provides {}

/* declarations */
%token <ival> INTEGER
%token <elem> ELEM
%type <dict> expr
%type <dict> formula

/* precedences */
%left ARROW
%left '+'
%nonassoc '(' ')'
%nonassoc ELEM
%nonassoc INTEGER
%nonassoc REDUCE_FORMULA    // force `formula . formula` reduce instead of
                            // shifting

%%
line    : expr ARROW expr '\n'  {print_map(diff_map($1, $3));}
        ;

expr    : expr '+' expr         {$$ = merge_map($1, $3);}
        | INTEGER formula       {   // factor of the compound
                                    for (std::map<std::string, int>::iterator it = $2.begin(); it != $2.end(); it++)
                                        it->second *= $1;
                                    $$ = $2;
                                }
        | formula               {$$ = $1;}
        ;

formula : formula formula %prec REDUCE_FORMULA {
                                $$ = merge_map($1, $2);
                                }
        | '(' formula ')' INTEGER {
                                    size_t i;
                                    for (std::map<std::string, int>::iterator it = $2.begin(); it != $2.end(); it++)
                                        it->second *= $4;
                                    $$ = $2;
                                }
        | '(' formula ')'       {$$ = $2;}
        | ELEM INTEGER          {
                                    std::map<std::string, int> m;
                                    m[$1] += $2;
                                    $$ = m;
                                }
        | ELEM                  {
                                    std::map<std::string, int> m;
                                    m[$1]++;
                                    $$ = m;
                                }
        ;

%%

void yyerror(const char *message) {
    std::cout << "Invalid format" << std::endl;
}

int main(void) {
    yyparse();
    return 0;
}

std::map<std::string, int> merge_map(std::map<std::string, int> map1,
                                      std::map<std::string, int> map2) {
    for (std::map<std::string, int>::iterator it = map2.begin(); it != map2.end(); it++)
        map1[it->first] += it->second;
    return map1;
}

std::map<std::string, int> diff_map(std::map<std::string, int> map1,
                                     std::map<std::string, int> map2) {
    for (std::map<std::string, int>::iterator it = map2.begin(); it != map2.end(); it++)
        map1[it->first] -= it->second;
    return map1;
}

void print_map(std::map<std::string, int> m) {
    for (std::map<std::string, int>::iterator it = m.begin(); it != m.end(); it++)
        if (it->second != 0)
            std::cout << it->first << " " << it->second << std::endl;
}
