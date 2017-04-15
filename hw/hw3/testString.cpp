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
 * Assignment: <Homework #3>
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
    cout << str1;
    cout << endl;
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
    cout << "new str1: " << str1 << endl;
}

void test4(){
    cout << "Using operator [] to print out str1" << endl << endl;
    
    String str1("Time And Relative Dimesion In Space");
    cout << "str1: " << str1 << endl;
    for(unsigned i = 0; str1[i] != '\0'; ++i){
        cout << str1[i];
    }
    cout << endl;
}

void test5(){
    cout << "Calling function int size() on str1, str1.size()" 
         << endl << endl;
    
    String str1("Nilin");
    cout << "str1: " << str1 << endl;
    cout << "str1.size(): " << str1.size() << endl;
 }

void test6(){
    cout << "Calling reverse() on str1, str1.reverse()" << endl << endl;
    
    String str1("Winchester");
    cout << "str1: " << str1 << endl;
    cout << "str1.reverse(): " << str1.reverse() << endl;
}

void test7(){
    cout << "Calling indexOf() on str1, with 'm' pass in as argument, "
         << "str1.indexOf('m')" << endl << endl;
    
    String str1("Remember Me");
    cout << "str1: " << str1 << endl;
    cout << "str1.indexOf('m'): " << str1.indexOf('m') << endl;
}

void test8(){
    cout << "Calling indexOf() on str1, with 'lock' pass in as argument, " 
         << "str1.indexOf(''lock'')" << endl << endl;
    
    String str1("Sherlock Holmes");
    cout << "st1: " << str1 << endl;
    cout << "str1.indexOf(''lock''): " << str1.indexOf("lock") << endl;
}

void test9(){
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

void test10(){
    cout << "Using operator != to check str1 and str2, then str1 and str3"
         << endl << endl;
    String str1("Supernatural");
    String str2("Supernatural");
    String str3("Spooky");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl << endl;
    
    bool testbool1 = str1 != str2;
    bool testbool2 = str1 != str3;
    cout << "str1 != str2: " << testbool1 << endl;
    cout << "str1 != str3: " << testbool2 << endl;
}

void test11(){
    cout << "Using operator > to check str1 and str2, then str1 and str3, "
         << "then str1 and str4"<< endl << endl;
    String str1("Hello World");
    String str2("Hello");
    String str3("Hello World!");
    String str4("Hello World");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl << endl;
    
    bool testbool1 = str1 > str2;
    bool testbool2 = str1 > str3;
    bool testbool3 = str1 > str4;
    
    cout << "str1 > str2: " << testbool1 << endl;
    cout << "str1 > str3: " << testbool2 << endl;
    cout << "str1 > str4: " << testbool3 << endl;
}

void test12(){
    cout << "Using operator > to check str1 and str2, then str1 and str3, "
         << "then str1 and str4" << endl << endl;
    String str1("Hello World");
    String str2("Hello");
    String str3("Hello World!");
    String str4("Hello World");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl << endl;
    
    bool testbool1 = str1 < str2;
    bool testbool2 = str1 < str3;
    bool testbool3 = str1 < str4;
    
    cout << "str1 < str2: " << testbool1 << endl;
    cout << "str1 < str3: " << testbool2 << endl;
    cout << "str1 < str4: " << testbool3 << endl;
}

void test13(){
    cout << "Using operator >= to check str1 and str2, then str1 and str3, "
         << "then str1 and str4" << endl << endl;
    String str1("Coca Cola");
    String str2("Coca");
    String str3("Coca Cola!");
    String str4("Coca Cola");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl << endl;
    
    bool testbool1 = str1 >= str2;
    bool testbool2 = str1 >= str3;
    bool testbool3 = str1 >= str4;
    
    cout << "str1 >= str2: " << testbool1 << endl;
    cout << "str1 >= str3: " << testbool2 << endl;
    cout << "str1 >= str4: " << testbool3 << endl;
}

void test14(){
    cout << "Using operator <= to check str1 and str2, then str1 and str3, "
         << "then str1 and str4" << endl << endl;
    String str1("Coca Cola");
    String str2("Coca");
    String str3("Coca Cola!");
    String str4("Coca Cola");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl << endl;
    
    bool testbool1 = str1 <= str2;
    bool testbool2 = str1 <= str3;
    bool testbool3 = str1 <= str4;
    
    cout << "str1 <= str2: " << testbool1 << endl;
    cout << "str1 <= str3: " << testbool2 << endl;
    cout << "str1 <= str4: " << testbool3 << endl;
}

void test15(){
    cout << "Using operator + to concatenate str1 and str2" << endl << endl;
    String str1("Doctor");
    String str2(" Who");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl << endl;
    
    cout << "str1 + str2: " << str1 + str2 << endl;
}

void test16(){
    cout << "Using operator += to concatenate str2 onto str1"<< endl << endl;
    String str1("Doctor");
    String str2(" Who");
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl << endl;
    
    str1 += str2;
    cout << "str1+=str2: " << str1 << endl;
}

void test17(){
    cout << "Using print in the overloaded operator <<, " << endl
         << "where str1 is an empty string, and str2 is 'Bad Wolf'"
         << endl << endl;
    String str1("");
    String str2("Bad Wolf");
    
    cout << "cout << str1: " << str1 << endl;
    cout << "cout << str2: " << str2 << endl;
    
}

void test18(){
    cout << "Using read in the overloaded operator >>, " << endl
         << "making a stringstream with 'Bad Wolf', " << endl
         << "the use operator >> to load stringsteam into a String object str1"
         << endl << endl;
         
    String str1("");
    stringstream ss;
    ss << "Bad Wolf";
    ss >> str1;
    cout << "str1: " << str1 << endl;
    
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
    
    cout << "\n========TEST5: int size()========\n";
    test5();
    
    cout << "\n========TEST6: String reverse()========\n";
    test6();
    
    cout << "\n========TEST7: int indexOf(char c)========\n";
    test7();
    
    cout << "\n========TEST8: int indexOf(String pattern)========\n";
    test8();
    
    cout << "\n========TEST9: bool operator == (String s)========\n";
    test9();
    
    cout << "\n========TEST10: bool operator != (String s)========\n";
    test10();
    
    cout << "\n========TEST11: bool operator > (String s)========\n";
    test11();
    
    cout << "\n========TEST12: bool operator < (String s)========\n";
    test12();
    
    cout << "\n========TEST13: bool operator >= (String s)========\n";
    test13();
    
    cout << "\n========TEST14: bool operator <= (String s)========\n";
    test14();
    
    cout << "\n========TEST15: String operator + (String s)========\n";
    test15();
    
    cout << "\n========TEST16: String operator += (String s)========\n";
    test16();
    
    cout << "\n========TEST17: void print (std::ostream & out)========\n";
    test17();
    
    cout << "\n========TEST18: void read (std::istream & in)========\n";
    test18();
    
    
    return 0;
}
