#include <iostream>
#include <vector>
#include <string>

using namespace std;

char input;
char token[1000] = {'\0'};
string ans;
int n, k;
vector <pair<string,int> > tokenStr;

void Lambda();

void DOT();
void LBR();
void RBR();
void ID();
void STRLIT();

void stmts();
void stmt();
void primary();
void primary_tail();


int main(){

    //while(!EOF){

        k = 0;
        input = getchar();
        while(input != '\n'){
            token[k++] = input;
            input = getchar();
        }

        token[k] = '$';

        for(int i=0; i<k; i++){

            if((token[i] >='a' && token[i] <='z') || \
            (token[i] >='A' && token[i] <='Z') || token[i]=='_'){

                tokenStr.push_back(make_pair("ID", i));
                while((token[i] >='a' && token[i] <='z') || (token[i] >='A' && token[i] <='Z') \
                    || (token[i] >='0' && token[i] <='9') || token[i] == '_'){i++;}
            }

            switch(token[i]){
                case '"':
                    tokenStr.push_back(make_pair("STRLIT",i++));
                    while(token[i] != '"' && token[i] != '$'){i++;}
                    if(token[i] != '"'){Lambda();}
                    break;
                case '(':
                    tokenStr.push_back(make_pair("LBR",0));
                    break;
                case ')':
                    tokenStr.push_back(make_pair("RBR",0));
                    break;
                case '.':
                    tokenStr.push_back(make_pair("DOT",0));
                    break;
                case '$':
                    tokenStr.push_back(make_pair("$",0));
                    break;
                default:
                    Lambda();
            }
        }
        stmts();
        cout << ans;
    //}


    return 0;

}

void Lambda(){
     cout << "invalid input\n";
     exit(0);
}

void DOT(){
    ans += "DOT .\n";
    n++;
}

void LBR(){
    ans += "LBR (\n";
    n++;
}

void RBR(){
    ans += "RBR )\n";
    n++;
}

void ID(){
    ans += "ID ";
    int i;
    for(i = tokenStr[n].second; (token[i] >= 'a' && token[i] <= 'z') \
    || (token[i] >= 'A' && token[i] <= 'Z') || token[i] == '_'; i++){ans += token[i];}

    while((token[i] >= 'a' && token[i] <= 'z') \
    || (token[i] >= 'A' && token[i] <= 'Z') || (token[i] >= '0' && token[i] <= '9') \
    || token[i] == '_'){ans += token[i];i++;}
    ans += "\n";
    n++;
}

void STRLIT(){
    ans += "STRLIT ";
    int i = tokenStr[n].second;
    do{
        ans += token[i++];
    }while(token[i] != '"');
    ans += token[i];
    ans += "\n";
    n++;
}

void stmts(){
    if(tokenStr[n].first == "STRLIT" || tokenStr[n].first == "ID"){
        stmt();
        stmts();
    }
}

void stmt(){
    if(tokenStr[n].first == "ID"){
        primary();
        primary_tail();
    }
    else if(tokenStr[n].first == "STRLIT"){
        STRLIT();
    }
    else if(tokenStr[n].first != "RBR"){
        Lambda();
    }
}

void primary(){
    ID();
    primary_tail();
}

void primary_tail(){

    if(tokenStr[n].first == "DOT"){
        DOT();
        ID();
        primary_tail();
    }
    else if(tokenStr[n].first == "LBR"){
        LBR();
        stmt();
        RBR();
        primary_tail();
    }
    else if(tokenStr[n].first != "$" && tokenStr[n].first != "ID" && tokenStr[n].first != "STRLIT"){
        Lambda();
    }
}



