//array.cpp
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

#include "Array.h"
#ifndef _ARRAY_CPP_
#define _ARRAY_CPP_

template <typename T>
Array<T>::Array(int newLen)
	throw(IndexOutOfBoundsException)
{
	if(newLen < 0)
		throw IndexOutOfBoundsException();
	len = newLen;
	buf = new T[newLen];
}

template <typename T>
Array<T>::Array(Array<T> & l)
: len(l.len), buf (new T[l.len] )
{
	for(int i = 0; i < l.len; ++i)
		buf[i] = l.buf[i];
}

template <typename T>
int Array<T>::length(){
	return len;
}

template <typename T>
T& Array<T>::operator [] (int i)
	throw(IndexOutOfBoundsException)
{
	if(0 < i && i > len)
		throw IndexOutOfBoundsException();
	return buf[i];
}

template <typename T>
void Array<T>::print (ostream &out){
	for(int i = 0; i < len; ++ i){
		out << buf[i] << "\t";
	}
}



#endif //_ARRAY_CPP__ARRAY_CPP_
