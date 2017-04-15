#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

void get_int_vec( vector<int> & v){
	int i;
	cout << "Enter a sequence of intergers you wish"
		 << "to separate into odd.txt and even.txt\n> ";
	while(cin >> i){
		v.push_back(i);
	}
	sort(v.begin(),v.end());
}

void intSeparator(vector<int> & v){
	cout << "separate odd and even integers into odd.txt and even.txt.\n";
	ofstream oddOut, evenOut;
	oddOut.open("odd.txt");
	evenOut.open("even.txt");

	for(vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
		if(*i % 2 == 0)
			evenOut << *i << endl;
		else
			oddOut << *i << " ";
	}
	oddOut << endl;
	oddOut.close();
	evenOut.close();
}

ostream & operator << ( ostream &out, const vector<int> & v){
	for(vector<int>::const_iterator i = v.begin(); i != v.end(); ++i){
		out << *i << " ";
	}
	cout << endl;
	return out;
}

int main(){
	vector <int> intVec;
	get_int_vec(intVec);
	cout << intVec;
	intSeparator(intVec);
	return 0;
}

