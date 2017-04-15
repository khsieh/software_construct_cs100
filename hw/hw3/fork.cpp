//fork.cpp
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
 
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

const unsigned TEN_THOUSAND = 10000;

void print_tenThousand(const char& c){
    for(unsigned i = 0; i < TEN_THOUSAND; ++i){
        cout << c;
        cout.flush();
    }
}

int main(){
    int parent = getpid();
    int kid1 = -1;
    int kid2 = -1;
    int kid3 = -1;
    int kid4 = -1;
    if(getpid() == parent){
        kid1 = fork();
            if(getpid() == parent)
                cout << "PID A: " << kid1 << endl;
    }
    if(getpid() == parent){
        kid2 = fork();
            if(getpid() == parent)
                cout << "PID B: "  << kid2 << endl;
    }
    if(getpid() == parent){
        kid3 = fork();
            if(getpid() == parent)
                cout << "PID C: " << kid3 << endl;
    }
    if(getpid() == parent){
        kid4 = fork();
            if(getpid() == parent)
                cout << "PID D: " << kid4 << endl;
    }
    
    sleep(1);
    
    if(kid1 == 0)
        print_tenThousand('A');
    
    if(kid2 == 0)
        print_tenThousand('B');
    if(kid3 == 0)
        print_tenThousand('C');
    if(kid4 == 0)
        print_tenThousand('D');
    
    if(getpid() == parent){
        while(wait(0) > 0);
        return 0;
    }
    if(kid1 == 0 || kid2 == 0 || kid3 == 0 || kid4 == 0){
        return 0;
    }
    
    return -1;
}
