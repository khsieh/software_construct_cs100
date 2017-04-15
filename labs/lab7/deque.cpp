#include <iostream>
#include <deque>
#include <queue>
#include <iterator>

using namespace std;

struct Process{
    int id;
    int priority;
    Process(int i, int p)
    :id(i), priority(p){}
};

struct PairComparator{
    bool operator() (const Process p1, const Process p2)const
    {
        return (p1.priority > p2.priority);
    }
};

int main(){
    priority_queue<Process, deque<Process>, PairComparator> dq;
    Process p1(000000, 1);
    Process p2(889578, 5);
    Process p3(125245, 2);
    
    dq.push(p1);
    dq.push(p2);
    dq.push(p3);
    
    //~ for(priority_queue<Process>::iterator i = dq.begin(); i != dq.end(); i++)
        //~ if(*i)
    while(!dq.empty()){
        cout << dq.top().priority << " " << dq.top().id << endl;
        dq.pop();
    }
    
    return 0;
}
