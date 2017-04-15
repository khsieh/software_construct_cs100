#include "Array.h"

#include <iostream>

using namespace std;

int main()
{
	Array<char> a(10);
	char c = 'A';
	for(int i = 0; i < a.length(); ++i){
		a[i] = c;
		c++;
	}

	cout << a << endl;
	try{
		cout << a[11] << endl;
	}
	catch(Array<char>::IndexOutOfBoundsException)
	{cerr << "Error: Index Out Of Bounds.\n";}

	return 0;
}
