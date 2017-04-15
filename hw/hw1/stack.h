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
  
#ifndef STACK_H
#define STACK_CAPACITY 1000

using namespace std;

class Stack
{
    private:
        char * data;
        unsigned current_size;
    public:
        Stack(); // constructor for a stack
        void push( char c ); // adds c to the top of the stack
        char pop(); // removes top element, returns it
        char top(); // returns the top element
        bool isEmpty(); // returns true iff the stack is empty
        ~Stack();// destructor for a stack
};
#endif //STACK_H
