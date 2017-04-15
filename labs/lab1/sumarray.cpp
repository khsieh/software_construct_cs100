// Kevin Hsieh SID: 861054367
// Kevin Do SID: 861069832
//section 22

//ex2: Program takes up to MAXSIZE number of integers and outputs their sum

#include <iostream>

using namespace std;

int arraysum( const int, const int a[] ); //declared function prototype

int main()
{
        const int MAXSIZE = 50;
        int a[MAXSIZE];
        int n;
        cout << "Enter up to " << MAXSIZE << 
                " integers, ctrl-D to end:\n";
        n = 0;
        while ((n < MAXSIZE) && (cin >> a[n])) 
                n++;    //added a semicolon
        if (n == 0)
                cout << "nothing entered!\n";
        else
                cout << "sum of input integers = " << 
                        arraysum(n, a) << endl;
        return 0 ;
}

// ---- function definition ----

int arraysum(const int n, const int a[])
{
        if (n == 0)
                return 0;   //should return 0 instead of 1
        else
                return a[n-1] + arraysum(n-1, a);
}
