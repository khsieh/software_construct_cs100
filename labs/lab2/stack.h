//Kevin Hsieh, 861054367
//Tony Mazza, 861069305

#include <iostream>

using namespace std;

class Stack
{
    private:
        unsigned size;
        unsigned capacity;
        int * array;
    public:
        Stack(); //constructor
        Stack(unsigned s, unsigned c);
        unsigned getSize();
        void push(int n);
        int pop();
        void expand();
        void shrink();
        void print();
        ~Stack(); //destructor
};
