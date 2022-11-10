#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// ======= Interleave First Half of queue with second half ========

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
// Function to interleaf 1st half od node with second half
queue<int> interleafQueue(queue<int> q, int n)
{
    queue<int> newQ;
    int count = 0;
    while (count < n / 2)
    {
        int val = q.front();
        q.pop();
        newQ.push(val);
        count++;
    }
    // q: 15 16 17 18            newQ: 11 12 13 14
    while (!newQ.empty())
    {

        int val = newQ.front(); // newQ front into q rear
        newQ.pop();
        q.push(val);
        // q: 15 16 17 18 11            newQ: 12 13 14
        // q: 16 17 18 11 15 12         newQ: 13 14
        // q: 17 18 11 15 12 16 13      newQ: 14
        // q: 18 11 15 12 16 13 17 14   newQ: __
        val = q.front(); // q front into q rear
        q.pop();
        q.push(val);
        // q: 16 17 18 11 15            newQ: 12 13 14
        // q: 17 18 11 15 12 16         newQ: 13 14
        // q: 18 11 15 12 16 13 17      newQ: 14
        // q: 11 15 12 16 13 17 14 18   newQ: __
    }

    return q;
}

// Function using Stack Auxilary space
queue<int> interleafQueue_2(queue<int> q, int n)
{
    stack<int> s;
    int count = 0;
    // first half elements into stack
    while (count < n / 2)
    {
        int val = q.front();
        q.pop();
        s.push(val);
        count++;
    }
    // q: 15 16 17 18                s: 11 12 13 14
    // pop from stack push into q
    while (!s.empty())
    {
        int val = s.top();
        s.pop();
        q.push(val);
    }
    // q: 15 16 17 18 14 13 12 11    s:_
    count = 0;
    while (count < n / 2)
    {
        int val = q.front();
        q.pop();
        q.push(val);
        count++;
    }
    // q: 14 13 12 11 15 16 17 18     s:__
    // first half elements into stack
    count = 0;
    while (count < n / 2)
    {
        int val = q.front();
        q.pop();
        s.push(val);
        count++;
    }
    //q: 15 16 17 18                 s: 14 13 12 11
    while(!s.empty()){
        // pop 
        int val = s.top();
        s.pop();
        q.push(val);

        int val2 = q.front();
        q.pop();
        q.push(val2);
    }

    return q;
}

int main()
{

    queue<int> q;
    q.push(11);
    q.push(12);
    q.push(13);
    q.push(14);
    q.push(15);
    q.push(16);
    q.push(17);
    q.push(18);
    printQueue(q);
    queue<int> newQ = interleafQueue_2(q, 8);
    printQueue(newQ);
    return 0;
}