#include <iostream>
#include <queue>
using namespace std;

// ================== K Queues in n size array =================
class KQueue
{
public:
    int n, k;
    int *front, *rear, *arr, *next;
    int freespot;

    KQueue(int n, int k)
    {
        this->n = n;
        this->k = k;
        front = new int[k];
        rear = new int[k];
        next = new int[n];
        arr = new int[n];
        freespot = 0; // 1st freespot
        for (int i = 0; i < k; i++)
        {
            front[i] = -1;
            rear[i] = -1;
        }
        for (int i = 0; i < k; i++)
        {
            next[i] = i + 1;
        }
        next[n - 1] = -1; // no next empty after last
    }

    void enqueue(int data, int qn)
    {
        if (freespot == -1)
        {
            return;
        }
        int index = freespot;
        // next freespot after this index
        freespot = next[index];

        if (front[qn - 1] == -1) // is this first element?
        {
            // intialise queue front to where element placed
            front[qn - 1] = index;
        }
        else
        {
            // next of where rear was earlier is not current index
            next[rear[qn - 1]] = index;
        }
        // this index place is now filled
        next[index] = -1;
        // rear of this Queue moves to where this element place
        rear[qn - 1] = index;
        // insert data
        arr[index] = data;
    }

    int dequeue(int qn)
    {
        if (front[qn - 1] == -1) // if this queue empty
        {

            return -1;
        }
        // element to be popped from front of this queue
        int index = front[qn - 1];
        // front moves forward to next element[where next of this element stored for this queue element NOT just next place] of this queue qn
        front[qn - 1] = next[index];
        //  current freespot is next free for current index, &this index will become current freespot
        next[index] = freespot;
        // and this empty index is freespot
        freespot = index;

        return arr[index];
    }
};

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
    KQueue q(7, 3);
    q.enqueue(5, 1);
    q.enqueue(13, 1);
    q.enqueue(10, 2);
    q.enqueue(15, 1);
    cout << q.dequeue(1) << endl;
    cout << q.dequeue(2) << endl;
    q.enqueue(30, 2);
    cout << q.dequeue(2) << endl;
    cout << q.dequeue(1) << endl;
    return 0;
}