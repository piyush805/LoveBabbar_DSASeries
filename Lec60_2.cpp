#include <iostream>
using namespace std;

class circularQueue
{
    int size;
    int *arr;
    int front;
    int rear;

public:
    circularQueue(int n)
    {
        size = n;
        arr = new int[size];
        front = rear = -1;
    }
    bool enqueue(int value)
    {
        if ((front == 0 && rear == size - 1) || (rear == (front - 1) % (size - 1)))
        {
            // 1st condition = front points to initial, rear at the last
            // 2nd condition = rear is one step behind front somehere is middle of array
            return false; // queue is full
        }
        else if (front == -1) // if queue is empty
        {
            front = rear = 0; // intialise both
        }
        else if (rear == size - 1 && front != 0)
        {
            // front in middle and rear is at end, then rear comes back to zero
            rear = 0;
        }
        else
        {
            // normally
            rear++;
        }
        arr[rear] = value; // push the value
        return true;       // element was pushed
    }
    int dequeue()
    {
        if (front == -1) // queue empty because front not initialized
        {
            return -1;
        }
        int ans = arr[front]; // value to be popped
        arr[front] = -1;      // filler
        if (front == rear)    // if only aa single element at was there i.e. 0
        {
            front = rear - 1;
        }
        else if (front == size - 1)

        {
            // front is at queue end then cyclic rotations brings back to 0
            front = 0; // cyclic rotation
        }
        else
        {
            front++; // normally
        }
        return ans;
    }
};

int main()
{
    circularQueue s(5);
    cout << s.enqueue(15) << endl;
    cout << s.enqueue(10) << endl;
    cout << s.enqueue(17) << endl;
    cout << s.enqueue(20) << endl;
    cout << s.enqueue(21) << endl;
    cout << s.enqueue(27) << endl;//cant push: returns 0
    cout << s.dequeue() << endl;//15
    cout << s.dequeue() << endl;//10
    return 0;
}
