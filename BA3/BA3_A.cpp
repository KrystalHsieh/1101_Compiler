#include <bits/stdc++.h>
#include <stack>

using namespace std;

stack<int> s;

int main(){

    string op;
    int num, temp, temp2;
    while(cin >> op){

        if(op == "$"){break;}
        else if(op == "push"){
            cin>>num;
            s.push(num);
        }
        else if(op == "inverse"){
            temp = s.top();
            s.pop();
            temp2 = s.top();
            s.pop();
            s.push(temp);
            s.push(temp2);
        }
        else if(op == "inc"){
            temp = s.top();
            s.pop();
            temp++;
            s.push(temp);
        }
        else if(op == "dec"){
            temp = s.top();
            s.pop();
            temp--;
            s.push(temp);
        }
    }
    cout<<s.top()<<endl;

    return 0;
}
