#include <iostream>
#include <string>

using namespace std;

bool NotNum(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' \
       || c == '(' || c == ')'){return 1;}
    else{return 0;}
}

int main(){

    string num;
    char input;
    char token[1000] = {'\0'};
    int k = 0;

    input = getchar();
    while(input != EOF){
        if(input != ' ' && input != '\n'){token[k++] = input;}
        input = getchar();
    }

    for(int i=0; i<k; i++){

        if(NotNum(token[i])){

            if(num != ""){
                cout << "NUM " << num << endl;
                num = "";
            }
            switch(token[i]){
                case '+':
                    cout << "PLUS" << endl;
                    break;
                case '-':
                    cout << "MINUS" << endl;
                    break;
                case '*':
                    cout << "MUL" << endl;
                    break;
                case '/':
                    cout << "DIV" << endl;
                    break;
                case '(':
                    cout << "LPR" << endl;
                    break;
                case ')':
                    cout << "RPR" << endl;
                    break;
            }
        }
        else{num += token[i];}
    }

    if(num != ""){cout << "NUM " << num << endl;}
    return 0;
}
