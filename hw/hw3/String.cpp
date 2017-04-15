//String.cpp
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
#include "String.h"

using namespace std;

String::String(const char* s = ""){
    unsigned i; // using i to count the length of the char array s
    for(i = 0; s[i] != '\0'; ++i){
    }
    
    buf = new char[i + 1];
    len = i;
    for(int j = 0; j < len; ++j){
        buf[j] = s[j];
    }
    
    buf[len] = '\0';
}

String::String(const String & s){
    buf = new char[s.len + 1];
    for(int i = 0; i < s.len; ++i){
        buf[i] = s.buf[i];
    }
    len = s.len;
    buf[len] = '\0';
}

String String::operator = (const String & s){
    delete [] buf;
    buf = new char[s.len + 1];
    for(int i = 0; i < s.len; ++i){
        buf[i] = s.buf[i];
    }
    len = s.len;
    buf[len] = '\0';
    return *this;
}

char & String::operator [] (int index){
    if( !inBound(index) )
        return buf[len];
    return *(buf + index);
}

int String::size(){
    return len;
}

//does not modify this string
String String::reverse(){ 
    String reverstr = *this;
    int mid = len / 2;
    for(int i = 0; i <= mid; i++){
        swap(reverstr[i],reverstr[len-i - 1]);
    }
    return reverstr;
}

int String::indexOf(char c){
    for(int i = 0; i < len; ++i){
        if(buf[i] == c)
            return i;
    }
    return -1;
}

int String::indexOf(String pattern){
    for(int i = 0; i < len; ++i){
        if(buf[i] == pattern[0]){
            for(unsigned j = 0; buf[j] != '\0'; ++j){
                if(pattern[j-i] == '\0')
                    return i;
                if(buf[j] != pattern[j-i])
                    break;
            }
        }
    }
    return -1;
}

bool String::operator == (String s){
    
    if(len != s.len)
        return false;
        
    for(unsigned i = 0; buf[i] != '\0'; ++i){
        if(buf[i] != s.buf[i])
            return false;
    }
    return true;
}

bool String::operator != (String s){
    
    if(len != s.len)
        return true;
        
    for(unsigned i = 0; buf[i] != '\0'; ++i){
        if(s.buf[i] == '\0')
            return true;
        if(buf[i] != s.buf[i])
            return true;
    }
    
    return false;
}

bool String::operator > (String s){
    unsigned i = 0;
    for(i = 0; buf[i] != '\0'; ++i){
        if(buf[i] > s.buf[i])
            return true;
        if(buf[i] < s.buf[i])
            return false;
    }
    
    if(len == s.len)
        return false;
    if(len < s.len)
        return false;
    return true;
}

bool String::operator < (String s){
    unsigned i = 0;
    for(i = 0; buf[i] != '\0'; ++i){
        if(buf[i] < s.buf[i])
            return true;
        if(buf[i] > s.buf[i])
            return false;
    }
    
    if(len == s.len)
        return false;
    if(len > s.len)
        return false;
    return true;
}

bool String::operator >= (String s){
    if(*(this) > s )
        return true;
    if(*(this) == s)
        return true;
    return false;
}

bool String::operator <= (String s){
    if(*(this) < s )
        return true;
    if(*(this) == s)
        return true;
    return false;
}

///concatenates this and s to return result
String String::operator + (String s){
    String * newString = new String(*this);
    int i = 0;
    for(i = len; i < len + s.len; ++i){
        newString->buf[i] = s.buf[i - len];
    }
    newString -> len = len + s.len;
    return *newString;
}

///concatenates s onto end of this
String String::operator += (String s){
    *this = *this + s;
    return *this;
}

void String::print (ostream & out){
    for(int i = 0; i < len; ++i){
        out << buf[i];
    }
}
void String::read (istream & in){
    delete [] buf;
    buf = NULL;
    char * newbuf = new char[100];
    
    unsigned i = 0;
    for(i = 0; in; ++i){
        in >> newbuf[i];
        //~ cout << newbuf[i] << endl;
    }
    newbuf[i] = '\0';
    
    *this = String(newbuf);
    
    delete newbuf;
}

String::~String (){
    delete [] buf;
}

ostream & operator << (std::ostream & out, String str){
    str.print(out);
    return out;
}
istream & operator >> (std::istream & in, String &  str){
    str.read(in);
    return in;
}
