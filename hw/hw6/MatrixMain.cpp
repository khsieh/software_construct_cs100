#include "Matrix.h"

using namespace std;

template <typename T>
void fillMatrix(Matrix <T> &m){
	int i, j;
	for(i = 0; i < m.numRows(); ++i)
		m[i][0] = T();
	for(j = 0; j < m.numCols(); ++j)
		m[0][j] = T();
	for(i = 1; i < m.numRows(); ++i){
		for(j=1; j < m.numCols(); ++j){
			m[i][j] = T( i * j );
		}
	}
}

int main()
{
	Matrix <int> m(10,5);
	fillMatrix(m);
	cout << m << endl; 

	try
	{
		cout << m[50] << endl;
	}
	catch(Matrix<int>::IndexOutOfBoundsException)
	{cerr << "Error: Index Out of Bounds\n";}
	return 0;
}
