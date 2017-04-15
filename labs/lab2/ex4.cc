//Kevin Hsieh, 861054367
//Tony Mazza, 861069305

#include <iostream>

using namespace std;

class List
{
    private:
            List * head;
            int num, tracker, size;
            List * next;
    public:
        List();
        List(int n)
        {
            num = n;
            next = NULL;
            size = 0;
            tracker = 0;            
        }
        void addNum(int n)
        {
            List * x = new List(n);
            next = x;
        }
        void countSize()
        {
            ++size;
            while(this->next!= NULL)
            {
              next->countSize();   
            }
        }
        
        int nth(int t)
        {
            while( t != 0)
            {
                
               --t; 
            }
        }
};
