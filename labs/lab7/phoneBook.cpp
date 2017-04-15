#include <iostream>
#include <iterator>
#include <map>
#include <string>

using namespace std;

class phoneBook{
    private:
        map <string, int> m;
    public:
        void insert(string s, int i){
            map<string,int>::iterator j = m.end();
            m.insert(j, pair<string,int>(s,i) );
        }
        
        void remove(string s){
            if(find(s) != m.end())
                m.erase(find(s));
            else
                cerr << "NOT FOUND\n";
        }
        
        map<string,int>::iterator find(string s){
            return m.find(s);
        }
        
        void print(){
            map<string,int>::iterator l;
            for(l = m.begin(); l != m.end(); ++l){
                cout << "name: " << l -> first 
                     << "\tphone: " << l -> second << endl;
            }
        }
};

int main(){
    
    phoneBook p;
    p.insert("kevin", 626532546);
    p.insert("David Ton", 6969696);
    p.insert("JJ", 6265452);
    p.print();
    
    cout << "=====remove=====\n";
    p.remove("David Ton");
    p.print();
    
    cout << "=====find=====\n";
    cout << p.find("JJ") -> first << endl;
    cout << p.find("JJ") -> second << endl;
    
    
    return 0;
}
