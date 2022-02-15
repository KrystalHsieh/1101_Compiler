#include <bits/stdc++.h>

using namespace std;

vector<string> split(string, char);
bool IsNonterminal(char);
bool IsEmpty(string);
string sorted_FollowSet(string);
int searchPosition(char);

class Rule{
    public:
        string nonterminal;
        vector<string> grammar;
};
vector<Rule> Rules;

class FirstSet{
    public:
        string nonterminal;
        string set;
};

class FollowSet{
    public:
        string nonterminal;
        string set;
        void add();
};

int main(){

    vector<FirstSet> FIRST;
    vector<FollowSet> FOLLOW;
    string input1, input2;
    int count = 0;

    while(1){

        Rule r;
        cin >> input1;
        if (input1 == "END_OF_GRAMMAR"){break;}
        cin >> input2;
        r.nonterminal = input1;
        r.grammar = split(input2, '|');
        Rules.push_back(r);
    }

    while(1){

        cin >> input1;
        if (input1 == "END_OF_FIRST_SET"){break;}
        cin >> input2;

        FirstSet FS;
        FollowSet FL;

        FS.nonterminal = input1;
        FS.set = input2;
        FIRST.push_back(FS);

        FL.nonterminal = input1;
        FL.set = "";
        FOLLOW.push_back(FL);
    }

    FOLLOW[0].set += '$';
    for(int i=0; i<10; i++){
        for(int j=0; j<Rules.size(); j++){
            for(int k=0; k<Rules[j].grammar.size(); k++){
                for(int t = 0; t < Rules[j].grammar[k].size(); t++){

                    if(!IsNonterminal(Rules[j].grammar[k][t])){if(t+1 == Rules[j].grammar[k].size()){break;}}
                    if(t == Rules[j].grammar[k].size()-1){
                        FOLLOW[searchPosition(Rules[j].grammar[k][t])].set += FOLLOW[searchPosition(Rules[j].nonterminal[0])].set;
                        break;
                    }

                    for(int n=t+1; n<Rules[j].grammar[k].size(); n++){

                        if(IsNonterminal(Rules[j].grammar[k][n])){

                            FOLLOW[searchPosition(Rules[j].grammar[k][t])].set += FIRST[searchPosition(Rules[j].grammar[k][n])].set;

                            if(IsEmpty(FIRST[searchPosition(Rules[j].grammar[k][n])].set)){count = n;continue;}
                            else{break;}
                        }
                        else{
                            FOLLOW[searchPosition(Rules[j].grammar[k][t])].set += Rules[j].grammar[k][n];
                            break;
                        }
                    }

                    if(count == Rules[j].grammar[k].size()-1){
                        FOLLOW[searchPosition(Rules[j].grammar[k][t])].set += FOLLOW[searchPosition(Rules[j].nonterminal[0])].set;
                    }
                    count = 0;
                }
            }
        }
    }
    for(int i=0; i<FOLLOW.size(); i++){FOLLOW[i].set = sorted_FollowSet(FOLLOW[i].set);}
    char match_nonterminal = 'A';
    while(match_nonterminal <= 'Z'){
        for (int i=0; i<FOLLOW.size(); i++){
            if(FOLLOW[i].nonterminal[0] == match_nonterminal){cout << FOLLOW[i].nonterminal << " " << FOLLOW[i].set << "\n";}
        }
        match_nonterminal++;
    }
    return 0;
}

vector<string> split(string str, char c){

    vector<string> splited_vec;
    string tmp = "";
    for (int i=0; i<str.size(); i++){
        if(str[i] == c){
            splited_vec.push_back(tmp);
            tmp = "";
        }
        else if(i == str.size()-1){
            tmp += str[i];
            splited_vec.push_back(tmp);
        }
        tmp += str[i];
    }
    return splited_vec;
}

bool IsNonterminal(char c) {
    if(c>='A' && c<='Z'){return 1;}
    else{return 0;}
}

bool IsEmpty(string str){
    for(int i=0; i<str.size(); i++){
        if (str[i] == ';'){return 1;}
    }
    return 0;
}

string sorted_FollowSet(string str1){

    string minUsed;
    string str2;

    sort(str1.begin(), str1.end());
    minUsed += str1[0];

    for(int i=1; i<str1.size(); i++){
        if(str1[i] != str1[i-1]){minUsed += str1[i];}
    }
    for(int i=0; i<minUsed.size(); i++){
        if(minUsed[i]>59 || minUsed[i]==36){str2 += minUsed[i];}
    }
    return str2;
}

int searchPosition(char c){
    for(int i=0; i<Rules.size(); i++){
        if(Rules[i].nonterminal[0] == c){return i;}
    }
    return -1;
}
