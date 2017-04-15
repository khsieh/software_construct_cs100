//ioExercise.cpp
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
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include "Timer.h"

using namespace std;

void ioChar(char* infile, char* outfile, const long int & nTime){
    double eUTime = 0, eSTime = 0, eWCTime = 0;
    
    Timer t;
    char c;
    t.start();
    
    for(unsigned i = 0; i < nTime; ++i){
        ifstream in;
        ofstream out;
        in.open(infile);
        out.open(outfile);
    
        while(in){
            in.get(c);
            out.put(c);
        }
        
        in.close();
        out.close();
    }
    
    t.elapsedUserTime(eUTime);
    t.elapsedSystemTime(eSTime);
    t.elapsedWallclockTime(eWCTime);
    
    cout << "WallClock Time:\t" << eWCTime << endl
         << "User Time:\t" << eUTime << endl
         << "System Time:\t" << eSTime << endl;
         

}

void ioChar2(char* infile, char* outfile, const long int & nTime){
    double eUTime = 0, eSTime = 0, eWCTime = 0;

    Timer t;
    char c[1];
    t.start();
    
    for(unsigned i = 0; i < nTime; ++i){
        int in = open(infile,O_RDONLY);
        int out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    
        while(read(in,c, 1) > 0 && write(out,c, 1) > 0){
        }
        
        close(in);
        close(out);
    }
    
    t.elapsedUserTime(eUTime);
    t.elapsedSystemTime(eSTime);
    t.elapsedWallclockTime(eWCTime);
    
    cout << "WallClock Time:\t" << eWCTime << endl
         << "User Time:\t" << eUTime << endl
         << "System Time:\t" << eSTime << endl;
         
    
}

void ioBuf(char* infile, char* outfile, const long int & nTime){
    double eUTime = 0, eSTime = 0, eWCTime = 0;
    
    Timer t;
    char buf[BUFSIZ];
    t.start();
    for(unsigned i = 0; i < nTime; ++i){
        int in = open(infile,O_RDONLY);
        int out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
        
        while(read(in,buf, BUFSIZ) > 0 && write(out,buf, BUFSIZ) > 0){
        }
        
        close(in);
        close(out);
    }
    t.elapsedUserTime(eUTime);
    t.elapsedSystemTime(eSTime);
    t.elapsedWallclockTime(eWCTime);
    
    cout << "WallClock Time:\t" << eWCTime << endl
         << "User Time:\t" << eUTime << endl
         << "System Time:\t" << eSTime << endl;
    
}

int main(int argc, char* argv[]){
    
    if(argc == 1){
        cerr << "invalid operand" << endl;
        exit(1);
    }
    
    stringstream ss;
    char * in = argv[1];
    char * out = argv[2];
    ss << argv[3];
    
    long int nTime;
    ss >> nTime;
    cout << "\n=====I/O with get(char), put(char)=====" << endl;
    ioChar(in,out,nTime);
    cout << "\n=====I/O with read(), write() with one char=====" << endl;
    ioChar2(in,out, nTime);
    cout << "\n=====I/O with read(), write() with one buff=====" << endl;
    ioBuf(in,out,nTime);
    
    return 0;
}
