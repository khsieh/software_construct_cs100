//Kevin Hsieh, 861054367
//Tony Mazza, 861069305

#include <iostream>

using namespace std;

class Library;

//~ struct Book
//~ {
    //~ string title;
    //~ string author;
    //~ int  year;
    //~ Library * last_book;
    //~ Library * next_book;
//~ };

class Library
{
    private:
        Library * head;
        string title;
        string author;
        int  year;
        Library * last_book;
        Library * next_book;
    public:
        Library();
        Library(string t, string a, int y);
        void search(string t);
        void addBook(string t, string a, int y);
        void removeBook(string t);
        void print();
        ~Library();
};
