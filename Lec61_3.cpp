#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// ===========Reverse first k elements in queue =================

queue<int> queueKReversal_1(queue<int> q, int k)
{
    stack<int> s;
    // Queue: 1 2 3 4 5
    // Pop first k elements from q and push into stack
    for (int i = 0; i < k; i++)
    {
        int element = q.front();
        q.pop();
        s.push(element);
    }
    // Queue: 4 5, Stack: 1 2 3
    // push those 1st k elements back into queue 'reversed'
    while (!s.empty())
    {

        int element = s.top();
        s.pop();
        q.push(element);
    }
    // These k elements now are in reverse order in back of the queue
    // Queue: 4 5 3 2 1, stack: _
    int t = q.size() - k;
    // pop front and pushback remaining element in same order in the queue
    while (t--)
    {
        int val = q.front();
        q.pop();
        q.push(val);
    }
    // Queue: 3 2 1 4 5
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
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(32);
    q.push(4);
    q.push(5);
    printQueue(q);
    q = queueKReversal_1(q, 4);
    printQueue(q);

    return 0;
}