#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// =======================Queue Reversal=========================

// Function to reverse queue using stack by recursion
void queueReversal_2(queue<int> &q)
{
    if (q.empty())
    {
        return;//until queue becomes empty, pop out elements
    }
    int element = q.front();
    q.pop();
    queueReversal_2(q);
    q.push(element);//last element popped out gets pushed first
}

// Function to reverse queue using stack by iteration
queue<int> queueReversal_1(queue<int> q)
{
    stack<int> s;
    while (!q.empty())
    {
        // push all elements from queue into stack
        int element = q.front();
        q.pop();
        s.push(element);
    }
    while (!s.empty())
    {
        // pop elements from stack - will be in reverse order-> push into queue
        int element = s.top();
        s.pop();
        q.push(element); // last element into stack(last of queue) will be first element in new queue
    }
    return q;
}

// function to print the queue
void printQueue(queue<int> q)
{
    // printing content of queue
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main()
{
    queue<int> q;
    q.push(5);
    q.push(6);
    q.push(14);
    q.push(74);
    q.push(23);
    printQueue(q);
    q = queueReversal_1(q);
    queueReversal_2(q);
    printQueue(q);

    return 0;
}