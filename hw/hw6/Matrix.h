//Matrix.h
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

#ifndef _MATRIX_H_
#define _MATRIX_H_
#include "Array.h"

template <class Element>
class Matrix
{
	private:
		int rows, cols;
		//define m as an Array of Array pointers
		Array < Array < Element > * > m;

	public:
		class IndexOutOfBoundsException{};

		Matrix(int newRows, int newCols)
			throw(IndexOutOfBoundsException);

		int numRows();

		int numCols();

		Array<Element> & operator [] (int row)
			throw(IndexOutOfBoundsException);

		void print(std::ostream & out);

		friend std::ostream & operator << (std::ostream & out, Matrix & m){
			m.print(out);
			return out;
		}
};

#include "Matrix.cpp"
#endif //_MATRIX_H_
