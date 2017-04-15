#include <vector>
#include <iostream>
#include <iterator>
#include <stack>

using namespace std;

void printvec(vector<char> &v){
    for(vector<char>::iterator i = v.begin(); i != v.end(); ++i){
        cout << *i << " ";
    }
    cout << endl;
}

int main(){
    vector<char> v;
    char c;
    for(c  = 'A'; c <= 'Z'; c++){
        v.push_back(c);
    }
    
    printvec(v);
    
    stack<char, vector<char> > S;
    for(vector<char>::iterator i = v.begin(); i != v.end(); ++i){
        S.push(*i);
    }
    
    while(!S.empty()){
        cout << S.top() << " ";
        S.pop();
    } 
    cout << endl;
    return 0;
}
