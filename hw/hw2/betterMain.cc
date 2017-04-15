//betterMain.cc
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

const int CENTS_FOR_CHIPS = 68;
int main()
{
    Coins pocket(5,3,6,8);
    Coins piggyBank(50,50,50,50);
    
    cout << "I have " << pocket << " in my pocket" << endl;

    if(pocket.hasSufficientAmount(CENTS_FOR_CHIPS))
    {
        Coins payForChips = pocket.extractChange(CENTS_FOR_CHIPS);
        cout << "Using " << payForChips << " to pay for Chips " << endl;
    }
    else
    {
        cout << "Not enough change in pocket to pay for the item, "
             << "Time to break the piggy bank :C"
             << endl;
    }
    cout << "I have " << pocket << " left in my pocket" << endl;
    cout << "Taking $5.00 from the piggy bank." << endl;
    Coins takingFromPiggy = piggyBank.extractChange(500);
    pocket.depositChange(takingFromPiggy);
    cout << "Now I have " << pocket << " in my pocket." << endl;
    cout << "And I have " << piggyBank << " in my piggyBank." << endl << endl;
    
    Coins foundChange(1,4,6,3);
    cout << "While vacuuming I found " << foundChange << endl;
    cout << "Storing the found changes in the Piggy Bank" << endl;
    piggyBank.depositChange(foundChange);
    cout << "Now Piggy Bank has " << piggyBank << endl << endl;
    
    return 0;
}
