//Matrix.cpp
/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #6>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */


#include "Matrix.h"

#ifndef _MATRIX_CPP_
#define _MATRIX_CPP_

using namespace std;

template <class Element>
Matrix<Element>::Matrix(int newRows, int newCols)
	throw(IndexOutOfBoundsException)
:m(0){
	if(newRows < 0 || newCols < 0)
		throw IndexOutOfBoundsException();
	rows = newRows;
	cols = newCols;
	m= rows;

	for(int i = 0; i < rows; ++i)
		m[i] = new Array < Element > (cols);
}

template <class Element>
int Matrix<Element>::numRows()
{
	return rows;
}

template <class Element>
int Matrix<Element>::numCols()
{
	return cols;
}

template <class Element>
Array<Element>& Matrix<Element>::operator [] (int row)
	throw(IndexOutOfBoundsException){
		if(row < 0 || row > rows)
			throw IndexOutOfBoundsException();
	return *m[row];
}

template <class Element>
void Matrix<Element>::print(std::ostream & out){
	for(int x = 0; x < rows; ++x){
		out << *(m[x]) << std::endl;
	}
}

#endif //_MATRIX_CPP_
