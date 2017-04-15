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
 * Assignment: <Homework #4>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */ 
 
#ifndef _STRING_H_
#define _STRING_H_
#include <iostream>

class String{
    
    private:
        bool inBounds(int i){
            return i >= 0 && i < length();
        }
        struct ListNode{
            char info;
            ListNode * next;
            ListNode(char newInfo, ListNode * newNext )
                :info(newInfo), next(newNext){}
            //static functions here  
        };
        ListNode * head;
        
    public:
        //both cons'tor should construct form parameter s
        String(const char * s = "");
        String(const String & s);
        String operator = (const String & s);
        char & operator [] (const int index);
        int length() const;
        int indexOf(char c) const;
        bool operator == (const String & s) const;
        /// concatenates this and s
        String operator + (const String & s) const;
        /// concatenates s onto end of this
        String operator += (const String & s);
        
        void print(std::ostream & out);
        void read(std::istream & in);
        ~String();
};

std::ostream & operator << (std::ostream & out, String str);
std::istream & operator >> (std::istream & in, String &str);

#endif //_STRING_H_
