// Coins.h ///  The name of this file.s

#ifndef _COINS_H_
#define _COINS_H_

using namespace std;

const int CENTS_PER_QUARTER = 25, CENTS_PER_DIME = 10, CENTS_PER_NICKEL = 5;

class Coins
{
    private:
        int quarters, dimes, nickels, pennies;
    public:
        Coins(int q, int d, int n, int p);
        void depositChange( Coins c);
        bool hasSufficientAmount( int amount );
        Coins extractChange( int amount );
        void print( ostream & out );
};

ostream & operator << ( ostream & out, Coins & c);

#endif //_COINS_H_
