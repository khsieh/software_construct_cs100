//bestMain.cc
/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #2>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */
 
#include <iostream>
#include "Coins.h"

void toDeposit(Coins & mc)
{
    int amount;
    cout << "Please enter the amount wish to deposit in cents: ";
    cin  >> amount;
    
    int q, d, n, p;
    q = amount / CENTS_PER_QUARTER;
    amount = amount % CENTS_PER_QUARTER;
    d = amount / CENTS_PER_DIME;
    amount = amount % CENTS_PER_DIME;
    n = amount / CENTS_PER_NICKEL;
    amount = amount % CENTS_PER_NICKEL;
    p = amount;
    
    Coins depositAmount(q,d,n,p);
    
    mc.depositChange(depositAmount);
    cout << endl;
    
}

void toExtract(Coins & mc)
{
    int amount;
    cout << "Please enter the amount you wish to extract in cents: ";
    cin  >> amount;
    
    if(mc.hasSufficientAmount(amount))
        mc.extractChange(amount);
    else
        cout << "Sorry, you don't have enuogh change!"
             << " Time to break the piggy bank :c" << endl;
    cout << endl;
}

int main()
{
    cout << "=========MENU==========" << endl
         << "Deposit (d/D)  |   Extract(e/E)" << endl
         << "Print (p/P)    |   Quit(q/Q)" << endl;
    char command;
    Coins myCoins(0,0,0,0);
    
    while(cin >> command)
    {
        switch(command)
        {
            case 'd':
            case 'D':
                toDeposit(myCoins);
                break;
            case 'e':
            case 'E':
                toExtract(myCoins);
                break;
            case 'p':
            case 'P':
                cout << "You have " << myCoins << endl << endl;
                break;
            case 'q':
            case 'Q':
                cout << "Bye bye~" << endl << endl;
                exit(0);
                break;
            default:
                cout << "unknown command, please enter a valid command\n"
                     << "Deposit (d/D)  |   Extract(e/E)" << endl
                     << "Print (p/P)    |   Quit(q/Q)" << endl
                     << endl;
                break;
        }
        cout << "=========MENU==========" << endl
             << "Deposit (d/D)  |   Extract(e/E)" << endl
             << "Print (p/P)    |   Quit(q/Q)" << endl;
    }
    
    return 0;
}
