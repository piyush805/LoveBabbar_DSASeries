#include <iostream>
#include <queue>
using namespace std;

class Queue
{
    int *arr;
    int qfront;
    int rear;
    int size;

public:
    Queue()
    {
        size = 10001;
        arr = new int[size];
        qfront = 0;
        rear = 0;
    }

    void enqueue(int data)
    {
        if (rear == size) // rear reached the end
        {
            cout << "Full" << endl;
        }
        else
        {
            arr[rear] = data;
            rear++; // rear points to next empty space
        }
    }

    int dequeue()
    {
        if (isEmpty()) // check empty
        {
            return -1;
        }
        int ans = arr[qfront]; // store the value to pop
        arr[qfront] = -1;      // filler
        qfront++;              // move front forward
        if (qfront == rear)
        {
            // qfront and rear meet in middle means array is empty from both side
            // qfront and rear meet in the end means array has become empty after dequeue
            qfront = 0;
            rear = 0;
        }
        return ans;
    }

    int front()
    {
        if (isEmpty()) // check empty
        {
            return -1;
        }
        return arr[qfront];
    }

    bool isEmpty()
    {
        if (qfront == rear) // at -1
        {
            return true;
        }
        return false;
    }
};

// void printQueue(int arr[], int size)
// {
//     for (int i = 0; i < n; i++)
//     {
//         cout << arr[] << " ";
//     }
//     cout << endl;
// }

int main()
{
    Queue q;
    q.enqueue(12);
    q.enqueue(15);
    q.enqueue(5);
    q.enqueue(8);
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    return 0;
}