#include <iostream>
#include <string>
#include <vector>
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

string input;
vector<pair<string, string> > ans;

void primary(string);
void stmts(string);
void ID(string);
void STRLIT(string, int);
void DOT();
void LBR();
void RBR();

void  htmlDocument();


int main() {

	while(cin >> input && !cin.eof()) {

		bool valid = 1;
		stmts(input);

		for(int i=0; i<ans.size(); i++){

			if(ans[i].first == "ID"){
				for(int j=0; j<ans[i].second.length(); j++){
					if(j == 0){
                        if(!isalpha(ans[i].second[j]) && ans[i].second[j] != '_'){valid = 0;}
                    }
					else{
                        if(!isalpha(ans[i].second[j]) && !isdigit(ans[i].second[j]) && \
                            ans[i].second[j] != '_'){valid = 0;}
                    }
				}
			}
			if(ans[i].first == "STRLIT"){
                int possible_index_of_strlit = ans[i].second.length()-1;
                if(ans[i].second[possible_index_of_strlit] != '"'){valid = 0;}
            }
		}

		if(valid){
			for(int i = 0; i < ans.size(); i++) {
				cout << ans[i].first << " " << ans[i].second << endl;
			}
		}
		else{cout << "invalid input\n";}
		ans.clear();
	}

    return 0;
}

void ID(string str){

    int i;
    for(i=0; i<str.length(); i++){
        if(str[i] == '(' || str[i] == ')' || str[i] == '.') {break;}
    }
    ans.push_back(make_pair("ID", substr(str, 0, i)));
    primary(substr(str, i));
}

void primary(string str) {
	if(str == "") return;
	if(str[0] == '.'){
		DOT();
		primary(substr(str, 1));
	}
	else if(str[0] == '('){
		LBR();
		primary(substr(str, 1));
	}
	else if(str[0] == ')'){
		RBR();
		primary(substr(str, 1));
	}
	else{
		ID(str);
    }
}

void stmts(string str) {

	if(str == "") return;

    int i;
	for(i=1; i<str.length(); i++){
        if(str[i] == '"'){break;}
	}

	if(str[0] == '"'){
        STRLIT(str, i);
		stmts(substr(str, i+1));
	}
	else {
		primary(substr(str, 0, i));
		stmts(substr(str, i));
	}
}

void STRLIT(string s, int pos){ans.push_back(make_pair("STRLIT", substr(s, 0, pos+1)));}
void DOT(){ans.push_back(make_pair("DOT", "."));}
void LBR(){ans.push_back(make_pair("LBR", "("));}
void RBR(){ans.push_back(make_pair("RBR", ")"));}

