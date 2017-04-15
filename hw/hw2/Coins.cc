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

using namespace std;

Coins::Coins(int q, int d, int n, int p)
:quarters(q), dimes(d), nickels(n), pennies(p)
{}

void Coins::depositChange( Coins c)
{
    quarters += c.quarters;
    dimes += c.dimes;
    nickels += c.nickels;
    pennies += c.pennies;
}

bool Coins::hasSufficientAmount( int amount )
{
    int t_amount = quarters * CENTS_PER_QUARTER;
    t_amount += dimes * CENTS_PER_DIME;
    t_amount += nickels * CENTS_PER_NICKEL;
    t_amount += pennies;
    
    return t_amount >= amount;
}

Coins Coins::extractChange( int amount )
{
    //calculate each coins and how much of each we need
    //consider if payable by lower tier of coins
    int quarters_to_pay = amount / CENTS_PER_QUARTER;
    if(quarters_to_pay > quarters)
        quarters_to_pay = quarters;
    amount -= quarters_to_pay * CENTS_PER_QUARTER;
    
    int dimes_to_pay = amount / CENTS_PER_DIME;
    if(dimes_to_pay > dimes)
        dimes_to_pay = dimes;
    amount -= dimes_to_pay * CENTS_PER_DIME;
    
    int nickels_to_pay = amount / CENTS_PER_NICKEL;
    if(nickels_to_pay > nickels)
        nickels_to_pay = nickels;
    amount -= nickels_to_pay * CENTS_PER_NICKEL;
    
    int pennies_to_pay = amount;
    
    //taking out all the coins
    quarters -= quarters_to_pay;
    dimes -= dimes_to_pay;
    nickels -= nickels_to_pay;
    pennies -= pennies_to_pay;
    
    return Coins(quarters_to_pay, dimes_to_pay, nickels_to_pay, pennies_to_pay);
    
}

void Coins::print( ostream & out )
{
    out << quarters << " quarters, ";
    out << dimes << " dimes, ";
    out << nickels << " nickels, and ";
    out << pennies << " pennies";
}

ostream & operator << ( ostream & out, Coins & c)
{
    c.print(out);
    return out;
}
