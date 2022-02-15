#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string substr(string s, int i) {
	if(i >= s.length()) return "";
	else return s.substr(i);
}
string substr(string s, int i, int len) {
	if(i >= s.length()) return "";
	else return s.substr(i, len);
}

int main(){

    string input;
    int i, k, t = 0;
    bool open = 0;

    char c;
    char token[1000] = {'\0'};

    c = getchar();
    while(c != EOF){
        if(c != '\n'){token[t++] = c;}
        c = getchar();
    }

    int temp_t = 0;
    while(temp_t != t){input += token[temp_t++];}

    while(input.length() > 0){

        if(input[0] == ' '){input = substr(input, 1);}
        else if((isalpha(input[0]) || isdigit(input[0])) && open == 1){
            i = 1;
            while(isalpha(input[i]) || isdigit(input[i])){i++;}
            cout << "TAG_NAME " << substr(input, 0, i) << endl;
            input = substr(input, i);

        }

        else if(input[0] == '<'){
            open = 1;
            if(input[1] == '/'){
                    cout << "TAG_OPEN_SLASH " << substr(input, 0, 2) << endl;
                    input = substr(input, 2);
            }
            else{
                cout << "TAG_OPEN " << substr(input, 0, 1) << endl;
                input = substr(input, 1);
            }
        }

        else if(input[0] == '>'){
            open = 0;
            cout << "TAG_CLOSE " << substr(input, 0, 1) << endl;
            input = substr(input, 1);

        }
        else if(input[0] == '='){
            cout << "TAG_EQUALS " << substr(input, 0, 1) << endl;
            input = substr(input, 1);
        }
        else if(input[0] == '"' && open == 1){
            i = 1;
            while(input[i] != '"'){i++;}
            cout << "DOUBLE_QUOTE_STRING " << substr(input, 1, i-1) << endl;
            input = substr(input, i+1);
        }
        else{
            if(open == 1){
                i = 1;
                while(input[i] != '<' && input[i] != '/' && input[i] != '>' &&\
                        input[i] != '=' && input[i] != '"'){i++;}
                cout << "SINGLE_QUOTE_STRING " << substr(input, 1, i-2) << endl;
                input = substr(input, i);
            }
            else{
                k = 1;
                while(input[k] != '<'){k++;}
                cout << "HTML_TEXT " << substr(input, 0, k) << endl;
                input = substr(input, k);
            }
        }
    }

    return 0;
}
