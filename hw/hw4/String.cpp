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
 * Assignment: <Homework #4>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */ 

#include "String.h"

using namespace std;

String::String(const char * s){
    //counting the size of c string
    //O(N)
    unsigned aSize = 0;
    while(s[aSize] != '\0')
        ++aSize;
    //1 ListNode constructor O(1)
    head = new ListNode('\0', NULL);
    ListNode * temp = head;
    
    //O(N)
    for(unsigned i = 0; i < aSize; ++i){
        temp -> info = s[i];
        temp ->  next = new ListNode ('\0', NULL); 
        temp = temp -> next;
    }
    
}

String::String(const String & s){
    
    head = new ListNode('\0', NULL);
    ListNode * temp = head;
    ListNode * temp2 = s.head;

    while (temp2){
        temp -> info = temp2 -> info;
        temp -> next = new ListNode('\0', NULL);
        temp = temp -> next;
        temp2 = temp2 -> next;
    }
    
    //~ temp -> next = NULL;
}

String String::operator = (const String & s){
    //delete current String to prevent memory leak;
    //O(N)
    ListNode * temp = head;
    while(head != NULL)
    {
        temp = temp -> next;
        delete head;
        head = temp;
    }
    
    //start copying over s to current String
    head = new ListNode('\0', NULL); //O(1)
    ListNode * copy = head;
    ListNode * current = s.head;
    //O(N)
    while(current){
        copy -> info = current -> info;
        copy -> next = new ListNode('\0', NULL);
        copy = copy -> next;
        current = current -> next;
    }
    
    return *this;
}

char & String::operator [] (const int index){

    ListNode * current = head;
    for(int i = 0; i < index; ++i){
        current = current -> next;
    }
    if(current -> info == '\0'){
        cerr << "Invalid index\n";
        return current -> info;
    }
    
    return current -> info;

}

int String::length() const{
    int len = 0;
    ListNode * current = head;
    while(current){
        if(current -> info != '\0')
            ++len;
        current = current -> next;
    }
    return len;
}

int String::indexOf(char c) const{
    int cIndex = 0;
    ListNode * current = head;
    while(current){
        if(current -> info != '\0')
            ++cIndex;
        if(current -> info == c)
            break;
        current = current -> next;
    }
    return cIndex;
}

bool String::operator == (const String & s) const{
    ListNode * current = head;
    ListNode * tracker = s.head;
    
    while(current && tracker){
        if(current -> info != tracker -> info)
            return false;
        current = current -> next;
        tracker = tracker -> next;
    }
    return true;
}

String String::operator + (const String & s) const{
    
    int curlen = length(); //1 call length O(N)
    int slen = s.length(); //2 call length O(M)
    int newlen = curlen + slen;
    char *tempStr = (char*) malloc(newlen + 1);
    
    //O(N)
    ListNode * curTracker = head;
    for(int i = 0; i < curlen; ++i){
        tempStr[i] = curTracker -> info;
        curTracker = curTracker -> next;
    }
    //O(M)
    ListNode * sTracker = s.head;
    for(int i = curlen; i < newlen; ++i){
        tempStr[i] = sTracker -> info;
        sTracker = sTracker -> next;
    }
    tempStr[newlen] = '\0';
    
    //3 call constructor O(2N+2M)
    return String(tempStr);
    //one String copy by the copy cons'tor
    //total: 3 fucnion calls
    //total runtime: O(4N + 4M) 
}

String String::operator += (const String & s) {
    *this = (*this + s);
    return *this;
    //one copy by calling +, the return value form copy cons'tor
}

void String::print(ostream & out){
    ListNode * temp = head;
    while(temp){
        out << temp -> info;
        temp = temp -> next;
    }
}

void String::read(istream & in){
    
    char tempStr[100];
    in >> tempStr;
    *this = String(tempStr);
}

String::~String(){
    ListNode* temp = head;
    while(head != NULL)
    {
        temp = temp -> next;
        delete head;
        head = temp;
    }
}

ostream & operator << (ostream & out, String str){
    str.print(out);
    return out;
}

std::istream & operator >> (istream & in, String& str){
    str.read(in);
    return in;
}
