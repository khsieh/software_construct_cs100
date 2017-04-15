//array.h
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

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <iostream>
 
using namespace std;

template <typename T>
class Array
{
	private:
		int len;
		T *buf;
	public:
		class IndexOutOfBoundsException{};

		Array(int newLen)
			throw(IndexOutOfBoundsException);

		Array(Array<T> & l);

		int length();

		T& operator [] (int i)
			throw(IndexOutOfBoundsException);

		void print (std::ostream &out);

		friend ostream & operator << (ostream &out, Array<T> & a){
			a.print(out);
			return out;
		}
};

#include "Array.cpp"

#endif //_ARRAY_H_
