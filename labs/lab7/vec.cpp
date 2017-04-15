#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

void printvec(vector<int> &v){
    for(vector<int>::iterator i = v.begin(); i != v.end(); ++i){
        cout << *i << " ";
    }
    cout << endl;
}

int main(){
    vector <int> v;
    vector <int> v2;
    
    int k = 1;
    for(unsigned i = 0; i < 10; ++i){
        v.push_back(k);
        k++;
    }
    
    printvec(v);
    
    vector<int>::iterator i = v.end();
    
    cout << "=====INSERT=====\n";
    v.insert(i,11);
    printvec(v);
    
    cout << "=====ERASE=====\n";
    v.erase(i-3);
    printvec(v);
    
    for(unsigned j = 0; j < 5; ++j){
        v2.push_back(j);
    }
    
    
    cout << "=====SWAP=====\n";
    cout << "BEFORE:\n";
    cout << "v: ";
    printvec(v);
    cout << "v2: ";
    printvec(v2);
    cout << endl;
    
    v.swap(v2);
    cout << "AFTER:\n";
    cout << "v: ";
    printvec(v);
    cout << "v2: ";
    printvec(v2);
        
    cout << "=====CLEAR=====\n";
    v.clear();
    v2.clear();
    
    cout << "v: ";
    printvec(v);
    cout << "v2: ";
    printvec(v2);
    
    return 0;
}

