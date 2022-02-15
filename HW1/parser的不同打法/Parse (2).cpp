#include <bits/stdc++.h>

using namespace std;

vector<pair<string, string> > v;
string substr(string s, int pos) {
	if(pos >= s.length()) return "";
	else return s.substr(pos);
}
string substr(string s, int pos, int len) {
	if(pos >= s.length()) return "";
	else return s.substr(pos, len);
}

void primary(string s) {
	if(s.length() == 0) return;
	if(s[0] == '.') {
		v.push_back(make_pair("DOT", "."));
		primary(substr(s, 1));
	} else if(s[0] == '(') {
		v.push_back(make_pair("LBR", "("));
		primary(substr(s, 1));
	} else if(s[0] == ')') {
		v.push_back(make_pair("RBR", ")"));
		primary(substr(s, 1));
	} else {
		int pos = 0;
		while(pos < s.length() && s[pos] != '.' && s[pos] != '(' && s[pos] != ')') pos++;
		v.push_back(make_pair("ID", substr(s, 0, pos)));
		primary(substr(s, pos));
		
	}
}

void oper(string s) {
	if(s.length() == 0) return;

	
	int pos = 1;
	while(pos < s.length() && s[pos] != '"') pos++;
	if(s[0] == '"') {
		v.push_back(make_pair("STRLIT", substr(s, 0, pos + 1)));
		oper(substr(s, pos + 1));
	} else {
		primary(substr(s, 0, pos));
		oper(substr(s, pos));
	}
}

int main() {
	string s;
	while(cin >> s) {
		v.clear();
		oper(s);

		bool ok = true;
		for(int i = 0; i < v.size(); i++) {
			if(v[i].first == "ID") {
				for(int j = 0; j < v[i].second.length(); j++) {
					if(j == 0 && (!isalpha(v[i].second[j]) && v[i].second[j] != '_')) ok = false;
					else if(j && (!isalpha(v[i].second[j]) && !isdigit(v[i].second[j]) && v[i].second[j] != '_')) ok = false;
				}
			}
			if(v[i].first == "STRLIT" && v[i].second[v[i].second.length() - 1] != '"') ok = false;
		}
		if(ok) {
			for(int i = 0; i < v.size(); i++) {
				cout << v[i].first << ' ' << v[i].second << endl;
			}
		} else {
			cout << "invalid input\n";
		}
	}
}
