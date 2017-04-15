//Kevin Hsieh, 861054367
//Tony Mazza, 861069305

#include <iostream>
#include "stack.h"

using namespace std;

Stack::Stack()
:size(0), capacity(0){}

Stack::Stack(unsigned s, unsigned c)
{
    if(s > c)
    {
        cout << "error!" << endl;
    }
    else
    {
        size = s;
        capacity = c;
        array = new int[c];
    }
}

unsigned Stack::getSize()
{
    return size;
}

void Stack::push(int n)
{
    if(size >= capacity)
        expand();
    array[size] = n;
    size++;
}

int Stack::pop()
{
    if(size < (capacity/2) )
        shrink();
    int x = array[size - 1 ];
    size--;
    
    return x;
}

void Stack::shrink()
{
    int *temp = new int[capacity/2];
    for(unsigned i = 0; i < size; i++)
    {
        temp[i] = array[i];
    }
    delete [] array;
    capacity /= 2;
    array = temp;
    cout << "capacity: " << capacity << endl;
}

void Stack::expand()
{
    int * temp = new int[capacity * 2];
    for(unsigned i = 0; i < size; i++)
    {
        temp[i] = array[i];
    }
    delete [] array;
    capacity *= 2;
    array = temp;
    cout << "capacity: " << capacity << endl;
}

void Stack::print()
{
    for(unsigned i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

Stack::~Stack()
{
    delete [] array;
}


int main()
{
    int num;
    int cap;
    cout << "enter the capacity of the array \n";
    cin >> cap;
    Stack stuff(0, cap);
    
    cout << "enter interger for stuff: ";
    //test push
    while(cin >> num)
        stuff.push(num);
        
    stuff.print();
    
    int x = stuff.getSize();
    //test pop
    for (unsigned i = 0; i < x; i++)
    {
        cout << stuff.pop() << endl;
    }
    
    return 0;
}
