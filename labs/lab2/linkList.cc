//Kevin Hsieh, 861054367
//Tony Mazza, 861069305

#include <iostream>
#include "linkList.h"

using namespace std;

Library::Library()
{
    title = "";
    author = "";
    year = 0;
    last_book = NULL;
    next_book = NULL;
}

Library::Library(string t, string a, int y)
{
    title = t;
    author = a;
    year = y;
    last_book = NULL;
    next_book = NULL;
        
}

void Library::search(string t)
{
    if(head -> title == t)
    {
        cout << "Book found!\nTitle: " << head -> title << endl;
       cout << "Author: " << head -> author << endl;
       cout << "Year: " << head -> year << endl << endl;
    }
    else if(title == t && this != NULL)
    {
       cout << "Book found!\nTitle: " << t << endl;
       cout << "Author: " << author << endl;
       cout << "Year: " << year << endl << endl;
    }
    else
    {
        if(this != NULL && next_book !=NULL)
            next_book->search(t);
        else
            cout << "BOOK NOT HERE!" << endl << endl;
    }
}

void Library::addBook(string t, string a, int y)
{
    if(head->title > t)
    {
        Library * temp = new Library(t,a,y);
        temp->last_book = NULL;
        
        head->last_book = temp;
        temp->next_book = head;
        head = temp;
        head->next_book->head = head;
        //~ cout << head -> title << endl;
        //~ cout << "HEL:LLLOPPP?" <<endl;
    }
    else if(next_book->title > t)
    {
        Library * temp = new Library(t,a,y);
        temp->last_book = NULL;
        temp->next_book = NULL;
        
        next_book -> last_book = temp;
        temp-> next_book = next_book -> next_book;
        next_book = temp;
        temp->last_book = this;
    }
    else if (next_book-> title < t)
    {
        this->addBook(t, a, y);
    }
}

void Library::removeBook(string t)
{
    if(head -> title == t)
    {
        Library * temp = head;
        next_book -> last_book = NULL;
        head = next_book;
        delete temp;
        cout << "ashdfkjadh" << endl;
    }
    else if(title == t)
    {
        Library * temp = this;
        last_book -> next_book = temp -> next_book;
        next_book -> last_book = temp -> last_book;
        delete temp;
    }
    else
    {
        next_book->removeBook(t);
    }
}

Library::~Library()
{
}

void Library::print()
{
    if(this == head)
    {
        cout << "Title: " << head -> title << endl;
        cout << "Author: " << head -> author << endl;
        cout << "Year: " << head -> year << endl << endl;
        if(head->next_book != NULL)
            head->next_book->print();
    }
    else if(this != NULL)
    {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl << endl;
        next_book->print();
    }
}

int main()
{
    Library test = Library("The c++ guide for dummies", "not me", 2013);
    test.search("The c++ guide for dummies");
    test.addBook("ABCDE", "tester", 2151);
     test.addBook("ABCDE", "tester", 2151);
    test.search("ABCDE");
    cout << "====================" << endl;
    test.print();
    //~ test.removeBook("ABCDE");
    test.search("ABC");
    
    return 0;
}
