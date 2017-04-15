//String.h
/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #3>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */  
 
#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
#include <fstream>

class String
{
    public:
        //Both constructor should construct this String from parameter s
        String(const char* s);
        String(const String & s);
        String operator = (const String & s);
        char & operator [] (int index);
        int size();
        String reverse(); //does not modify this string
        int indexOf(char c);
        int indexOf(String pattern);
        bool operator == (String s);
        bool operator != (String s);
        bool operator > (String s);
        bool operator < (String s);
        bool operator >= (String s);
        bool operator <= (String s);
        
        ///concatenates this and s to return result
        String operator + (String s);
        ///concatenates s onto end of this
        String operator += (String s);
        
        void print (std::ostream & out);
        void read (std::istream & in);
        ~String ();
    private:
        bool inBound(int i)
        {
            return i >= 0 && i < len;
        }
        char * buf;
        int len; // number of chars in buf
};

std::ostream & operator << (std::ostream & out, String str);
std::istream & operator >> (std::istream & in, String & str);
#endif //__STRING_H__
