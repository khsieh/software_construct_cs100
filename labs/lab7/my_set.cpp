#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class my_set{
    private:
        vector <double> v;
    public:
        my_set(vector<double> V){
            for(unsigned i = 0; i < V.size(); ++i){
                v.push_back(V[i]);
            }
        }
        
        bool my_inclusion(my_set s){
            if(includes(v.begin(),v.end(), s.v.begin(), s.v.end() ) )
                return true;
            else
                return false;
        }
            
        vector<double>::iterator my_union(my_set s, vector<double>::iterator result){
            return set_union(v.begin(),v.end(), s.v.begin(), s.v.end(),
                             result);
        }
        vector<double>::iterator my_intersection(my_set s,vector<double>::iterator result){
            return set_intersection(v.begin(),v.end(), s.v.begin(), s.v.end(),
                             result);
        }
        
        vector<double>::iterator my_difference(my_set s,vector<double>::iterator result){
            return set_difference(v.begin(),v.end(), s.v.begin(), s.v.end(),
                             result);
        }
        
        void print(){
            for(unsigned i = 0; i < v.size(); ++i)
                cout << v[i] << " ";
            cout << endl;
        }
};

int main(){
    
    vector <double> v;
    vector <double> v2;
    vector <double> v3;
    vector <double> r(13);
    vector <double> r2(2);
    vector <double> r3(8);
    
    double k = 1;
    for(unsigned i = 0; i < 10; ++i){
        v.push_back(k);
        k++;
    }
    
    int l = 0;
    for(unsigned i = 0; i < 5; ++i){
        v2.push_back(l);
        l += 5;
    }
    
    int j = 1;
    for(unsigned i = 0; i < 5; ++i){
        v3.push_back(j);
        j++;
    }
    
    cout << "=====Construct my_set=====\n";
    my_set set1(v);
    my_set set2(v2);
    my_set set3(v3);
    cout << "set1: ";
    set1.print();
    cout << "set2: ";
    set2.print();
    cout << "set3: ";
    set3.print();
    
    cout << "=====INCLUSION=====\n";
    if(set1.my_inclusion(set2))
        cout << "YAY~"<< endl;
    else
        cout << "BOOO!" << endl;
    
    cout << "=====UNION=====\n";
    set1.my_union(set2,r.begin());
    
    for(unsigned i = 0; i < r.size(); ++i){
        cout << r[i] << " ";
    }
    cout << endl;
    
    cout << "=====INTERSECTION=====\n";
    //~ r.clear();
    set1.my_intersection(set2,r2.begin());
    for(unsigned i = 0; i < r2.size(); ++i){
        cout << r2[i] << " ";
    }
    cout << endl;
    
    cout << "=====DIFFERENCE=====\n";
    set1.my_difference(set2,r3.begin());
    for(unsigned i = 0; i < r3.size(); ++i){
        cout << r3[i] << " ";
    }
    cout << endl;
    
    return 0;
}
