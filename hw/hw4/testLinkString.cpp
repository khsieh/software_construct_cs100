//testString.cpp
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
#include <sstream>

using namespace std;

void test1(){
    cout << "Using constructor to make str1 with 'Hello World'" 
         << endl << endl;
    String str1("Hello World");
    cout << "str1: " << str1 << endl;
}

void test2(){
    cout << "Using copy constructor to copy str1 into str2" 
         << endl << endl;
         
    String str1("Hello World");
    String str2(str1);
    
    cout << "str1: " << str1 << endl;
    cout << "str2(str1): " << str2 << endl;
}

void test3(){
    cout << "Using assign operator to set str1 to str2, str1 = str2" 
         << endl << endl;
         
    String str1("Wibbly Wobbly");
    String str2("Timey Wimey");
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    str1 = str2;
    cout << "str1 = str2: " << str1 << endl;
}


void test4(){
    cout << "Using operator [] to print out str1" << endl << endl;
    
    String str1("Time And Relative Dimesion In Space");
    cout << "str1: " << str1 << endl;
    for(int i = 0; i < str1.length(); ++i){
        cout << str1[i];
    }
    cout << endl;
}

void test5(){
    cout << "Calling function int length() on str1, str1.size()" 
         << endl << endl;
    
    String str1("Nilin");
    cout << "str1: " << str1 << endl;
    cout << "str1.length(): " << str1.length() << endl;
 }

void test6(){
    cout << "Calling indexOf() on str1, with 'm' pass in as argument, "
         << "str1.indexOf('m')" << endl << endl;
    
    String str1("Remember Me");
    cout << "str1: " << str1 << endl;
    cout << "str1.indexOf('m'): " << str1.indexOf('m') << endl;
}

void test7(){
    cout << "Using operator == to check str1 and str2, and str1 and str3"
         << endl << endl;
    String str1("Supernatural");
    String str2("Supernatural");
    String str3("Spooky");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl << endl;
    
    bool testbool1 = str1 == str2;
    bool testbool2 = str1 == str3;
    cout << "str1 == str2: " << testbool1 << endl;
    cout << "str1 == str3: " << testbool2 << endl;
}

void test8(){
    cout << "Using operator + to concatenate str1 and str2" << endl << endl;
    String str1("Doctor");
    String str2(" Who");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl << endl;
    
    cout << "str1 + str2: " << str1 + str2 << endl;
}

void test9(){
    cout << "Using operator += to concatenate str2 onto str1"<< endl << endl;
    String str1("Doctor");
    String str2(" Who");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl << endl;
    
    str1 += str2;
    cout << "str1 += str2: " << str1 << endl;
}

void test10(){
    cout << "Using print in the overloaded operator <<, " << endl
         << "where str1 is an empty string, and str2 is 'Bad Wolf'"
         << endl << endl;
    String str1("");
    String str2("Bad Wolf");
    
    cout << "cout << str1: " << str1 << endl;
    cout << "cout << str2: " << str2 << endl;
    
}

void test11(){
    cout << "Using read in the overloaded operator >>, " << endl
         << "making a stringstream with 'Penguinie', " << endl
         << "the use operator >> to load stringsteam into a String object str1"
         << endl << endl;
         
    String str1("what");
    stringstream ss;
    ss << "Penguinie";
    ss >> str1;
    cout << "str1: " << str1 << endl;
    
}

void test12(){
    String s("Hello");
    String t("There");
    
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    s = s + t;
    cout << "s = s + t: " << s << endl;
    cout << "Three function calls, 2 calls on length, both are O(N) runtime,"
         << "1 call for Constructor String(const char *s), O(2N) runtime."
         << endl
         << "Total runtime: O(4N + 4M), where N is s.length,"
         << " and M is t.length"
         << endl
         << "One String copy by the copy constructor" << endl;
}

void test13(){
    String s("Hello");
    String t("There");
    
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    s += t;
    cout << "s += t: " << s <<endl;
    cout << "Four function calls, 3 calls by + operator, O(4N + 4M) runtime"
         << ", 1 by the = operator, O(2N+2M) runtime" << endl
         << "Total runtime: O(6N+6M)" 
         << "where N is s.length, and M is t.length"
         << endl
         << "one copy by calling +, the return value form copy constructor"
         <<endl;
}

int main()
{
    cout << "========TEST1: constructor String(const char* s)========\n";
    test1();
    
    cout << "\n========TEST2: constructor String(const String & s)=======\n";
    test2();
    
    cout << "\n========TEST3: String operator = (const String & s)========\n";
    test3();
    
    cout << "\n========TEST4: char & operator [] (int index)========\n";
    test4();
    
    cout << "\n========TEST5: int length()========\n";
    test5();
    
    cout << "\n========TEST6: int indexOf(char c)========\n";
    test6();
    
    cout << "\n========TEST7: bool operator == (String s)========\n";
    test7();
    
    cout << "\n========TEST8: String operator + (String s)========\n";
    test8();
    
    cout << "\n========TEST9: String operator += (String s)========\n";
    test9();
    
    cout << "\n========TEST10: void print (std::ostream & out)========\n";
    test10();
    
    cout << "\n========TEST11: void read (std::istream & in)========\n";
    test11();
    
    cout << "\n=====TEST12: Assignment 1, s = s+ t=====\n";
    test12();
    
    cout << "\n=====TEST13: Assignment 2, s += t=====\n";
    test13();
    
    cout << "\n=====END OF TEST HARNESS=====\n";
    
    return 0;
}
