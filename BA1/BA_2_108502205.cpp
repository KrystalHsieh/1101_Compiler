#include <iostream>

using namespace std;

void s1(string, int);
void s2(string, int);
void s3(string, int);
void s4(string, int);

int main(){

    string input;
    cin >> input;
    int k = 0;
    s1(input, k);

    return 0;
}

void s1(string str, int i){
    if(str[i] == '$'){cout << "NO";}
    else if(str[i] == 'a'){i++;s2(str, i);}
    else if(str[i] == 'b'){i++;s3(str, i);}
    else {cout << "NO";}
}

void s2(string str, int i){
    if(str[i] == '$'){cout << "NO";}
    else if(str[i] == 'a'){i++;s2(str, i);}
    else if(str[i] == 'b'){i++;s4(str, i);}
    else {cout << "NO";}
}

void s3(string str, int i){
    if(str[i] == '$'){cout << "YES s3";}
    else if(str[i] == 'a'){i++;s3(str, i);}
    else if(str[i] == 'c'){i++;s4(str, i);}
    else {cout << "NO";}
}

void s4(string str, int i){
    if(str[i] == '$'){cout << "YES s4";}
    else {cout << "NO";}
}
