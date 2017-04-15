//handle_signals.cpp
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
 
#include <signal.h>
#include <iostream>

using namespace std;

int C = 0;
int Q = 0;
int Z = 0;

void signal_handlers(int sigInt){
    switch(sigInt){
        case SIGINT:
            cout << "I" << flush;
            C++;
            break;
        case SIGQUIT:
            cout << "Q" << flush;
            Q++;
            break;
        case SIGTSTP:
            cout << "S" << flush;
            Z++;
            if(Z == 3){
                cout << "\nInterrupt: " << C << flush << endl;
                cout << "Stop: " << Q << endl << flush;
                cout << "Quit: " << Z << endl << flush;
                exit(0);
            }
            raise(SIGSTOP);
            break;
        default:
            break;
    }
}

int main(){
    
    signal(SIGINT,signal_handlers);
    signal(SIGQUIT,signal_handlers);
    signal(SIGTSTP,signal_handlers);
    
    while(1){
        cout << "X" << flush;
        sleep(1);
    }
}
