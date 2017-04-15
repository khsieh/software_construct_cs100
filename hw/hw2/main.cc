//main.cc
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

const int CENTS_FOR_CANDYBAR = 482;
int main()
{
    /// Creates a Coins object calld 'pocket"
    Coins pocket(100, 10, 10, 100);
    cout << "I started with " << pocket << " in my pocket" << endl;
    /// Create a Coins object called payForCandy and initializes it.
    Coins payForCandy = pocket.extractChange(CENTS_FOR_CANDYBAR);
    cout << " I bought a candy bar for " << CENTS_FOR_CANDYBAR
         << " cents using " << payForCandy << endl;
    cout << " I have " << pocket << " left in my pocket" << endl;
    return 0;
}
