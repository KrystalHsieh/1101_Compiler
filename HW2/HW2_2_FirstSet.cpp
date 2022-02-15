#include <bits/stdc++.h>

using namespace std;

vector<string> nonterminal_vec;
vector<string> tmp_vec;
vector<vector<string>> grammar_vec;
vector<string> FirstTable;
vector<string> Nonterminal_Table;

vector<string> split(string, char);
void build_table(string, vector<string>);
bool IsInTable(char);
int SearchLoc(char);
bool IsNonterminal(char);
void FIRST(vector<string>, vector<vector<string>>);
string sorted_FIRST(string);
bool IsEmptySymbol(char);
string NoSemicomma(char);
bool IsEnd(int, string);

int main(){

    //input and seperate symbols and grammar with '|'
    string nonterminal, grammer;
    while (cin >> nonterminal){

        if(nonterminal == "END_OF_GRAMMAR"){break;}
        nonterminal_vec.push_back(nonterminal);
        cin >> grammer;
        tmp_vec = split(grammer, '|');
        grammar_vec.push_back(tmp_vec);
    }

    FIRST(nonterminal_vec, grammar_vec);

    //to output with alphabetic order
    //due to the last prototype, this one is needed to configure
    string first_set, sorted_first;
    char match_Nonterminal = 'A';

    while(match_Nonterminal <= 'Z'){
        for (int i=0; i<Nonterminal_Table.size(); i++){
            if (Nonterminal_Table[i][0] == match_Nonterminal) {
                sorted_first = sorted_FIRST(FirstTable[i]);
                cout << match_Nonterminal << " " << sorted_first << "\n";
                break;
            }
        }
        match_Nonterminal++;
    }
    cout << "END_OF_FIRST\n";
    return 0;
}

vector<string> split(string str, char c){

    vector<string> splited_str;
    string tmp_str = "";
    for(int i=0; i<str.size(); i++){

        if (str[i] == c){
            splited_str.push_back(tmp_str);
            tmp_str = "";
            continue;
        }
        tmp_str += str[i];
    }
    splited_str.push_back(tmp_str);
    return splited_str;
}

//when there's no nonterminal in one's grammar, build it into the table
void build_table(string str, vector<string> str_grammar){
    string tmp_str = "";
    Nonterminal_Table.push_back(str);
    for(int i=0; i<str_grammar.size(); i++){
        tmp_str += str_grammar[i][0];
    }
    FirstTable.push_back(tmp_str);
}

//to determine whether the nonterminals we encountered is in the table we built or not
bool IsInTable(char c){

    for(int i=0; i<Nonterminal_Table.size(); i++){
        if(Nonterminal_Table[i][0] == c){return true;}
    }
    return false;
}

int SearchLoc(char c){

    for(int i=0; i<Nonterminal_Table.size(); i++){
        if(Nonterminal_Table[i][0] == c){return i;}
    }
    return 0;
}

bool IsNonterminal(char c){
    if(c>='A' && c<='Z'){return 1;}
    else{return 0;}
}

void FIRST(vector<string> non_ter, vector<vector<string>> grammar){

    for (int i=0; i<non_ter.size(); i++){
        for (int j=0; j<non_ter.size(); j++){

            string tmp_str;
            bool NonTer = 0;
            bool InTable = 0;
            vector<string> tmp_grammar_vec;
            int loc;

            //find whether there's a nonterminal in the grammar or not
            for(int k=0; k<grammar[j].size(); k++){
                if(IsNonterminal(grammar[j][k][0])){
                    NonTer = 1;
                    break;
                }
            }
            if(!NonTer){build_table(non_ter[j], grammar[j]);}
            else{
                //make sure all the nonterminals are in the table
                for(int k=0; k<grammar[j].size(); k++){
                    if (IsNonterminal(grammar[j][k][0])){
                        if (IsInTable(grammar[j][k][0])){
                            InTable = 1;
                        }
                        else{InTable = 0;break;}
                    }
                }
                //if all nonterminals in table, than build table
                if (InTable){

                    int tmp = 0;
                    for(int k=0; k<grammar[j].size(); k++){
                        //when encounter nonterminals
                        if(IsNonterminal(grammar[j][k][tmp])){

                            loc = SearchLoc(grammar[j][k][tmp]);
                            if(IsEnd(tmp, grammar[j][k])){tmp_str += FirstTable[loc];}
                            else{tmp_str += NoSemicomma(grammar[j][k][tmp]);}
                            //if there's a empty symbol in the nonterminal's grammar
                            if(IsEmptySymbol(grammar[j][k][tmp])){
                                tmp++;
                                k--;
                                continue;
                            }
                        }
                        else{tmp_str += grammar[j][k][tmp];}
                        tmp = 0;
                    }
                    Nonterminal_Table.push_back(non_ter[j]);
                    FirstTable.push_back(tmp_str);
                }
            }
        }
    }
}

//to output the string with ascii order, and delete the characters that were repeated
string sorted_FIRST(string str1){

    string str2;
    string minRepeat;
    sort(str1.begin(), str1.end());
    minRepeat += str1[0];

    for(int i=1; i<str1.size(); i++){
        if (str1[i] != str1[i - 1]){minRepeat += str1[i];}
    }
    for(int i=0; i<minRepeat.size(); i++){
        if(minRepeat[i] >= 59 || minRepeat[i] == 36){
            str2 += minRepeat[i];
        }
    }
    return str2;
}

bool IsEmptySymbol(char c){

    int num;
    for (int i=0; i<Nonterminal_Table.size(); i++) {
        if(Nonterminal_Table[i][0] == c){
            num = i;
            break;
        }
    }
    for(int i=0; i<FirstTable[num].size(); i++){
        if(FirstTable[num][i] == ';'){return 1;}
    }
    return 0;
}

//to determine whether encounter the character ';' or not
string NoSemicomma(char c){

    string str;
    int num;
    num = SearchLoc(c);
    for(int i=0; i<FirstTable[num].size(); i++){
        if(FirstTable[num][i] != ';'){str += FirstTable[num][i];}
    }
    return str;
}

//to tell if there is a ';' in one nonterminal's table or not
bool IsEnd(int num, string str){

    if(num == str.size()-1){return 1;}
    else{return 0;}
}


/*

^.*John.*$.     辨識包含John的
"[^"\r\n]*"     ".*" 但扣除 ", \r, \n 等等
#.*$            match a single line comment starting with a # and continuing until EOF



*/
