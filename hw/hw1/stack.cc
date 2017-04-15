/*
* Course: CS 100 Fall 2013
*
* First Name: <Kevin>
* Last Name: <Hsieh>
* Username: <khsie003>
* email address: <khsie003@ucr.edu>
*
*
* Assignment: <Homework #1>
*
* I hereby certify that the contents of this file represent
* my own original individual work. Nowhere herein is there
* code from any outside resources such as another individual,
* a website, or publishings unless specifically designated as
* permissible by the instructor or TA.
*/  

#include <iostream>
#include "stack.h"

using namespace std;

Stack::Stack()
{
    current_size = 0;
    data = new char[STACK_CAPACITY];
}

void Stack::push(char c)
{
    data[current_size] = c;
    current_size++;
}

char Stack::pop()
{
    char temp = data[current_size - 1];
    current_size--;
    return temp;
}

char Stack::top()
{
    return  data[current_size-1];
}

bool Stack::isEmpty()
{
    return current_size == 0;
}

Stack::~Stack()
{
    delete [] data;
}
//========= main ============//

int main()
{
    Stack s;
    string input;
    cout << "Please enter string: ";
    
    getline(cin,input);
    
    for(unsigned i = 0; i < input.size(); i++)
    {
        s.push(input.at(i));
    }
    
    while(!s.isEmpty())
    {
        cout << s.pop();
    }
    
    cout << endl;
    return 0;
}
