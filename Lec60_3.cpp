#include <iostream>
#include <queue>
using namespace std;
//==============Doubly ended queue implementation====================
class DEqueue
{
    int *arr;
    int size, front, rear;

public:
    DEqueue(int n)
    {
        size = n;
        arr = new int[n];
        front = -1;
        rear = -1;
    }

    bool pushFront(int x)
    {
        if ((front == 0 && rear == size - 1) || rear == (front - 1) % (size - 1))
        {
            // Queue Full
            // Front goes 1 step back to reach rear
            return false;
        }
        else if (front == -1 && rear == -1)
        {
            // Empty=>initialize both
            front = rear = 0;
        }
        else if (front == 0 && rear != size - 1)
        {
            // Not full yet, yet front at start and rear not in end=>cyclically shift front to end
            front = size - 1;
        }
        else
        {
            front--; // normal push front
        }
        arr[front] = x;
        return true;
    }

    bool pushRear(int x)
    {
        if ((front == 0 && rear == size - 1) || rear == (front - 1) % (size - 1))
        {
            // Full
            return false;
        }
        else if (front == -1 && rear == -1)
        {
            // Empty=>initialize both
            front = rear = 0;
        }
        else if (front != 0 && rear == size - 1)
        {
            // front is not in start and rear is in end then cyclically rear comes to start
            rear = 0;
        }
        else
        {
            rear++; // normal push rear
        }
        arr[rear] = x;
        return true;
    }

    int popFront()
    {
        if (isEmpty())
        {
            return -1;
        }
        int ans = arr[front];
        arr[front] = -1;
        if (front == rear) // both are at zero, single element, bring both to initial
        {
            front = rear = -1;
        }
        else if (front == size - 1) // front in end then cylically being to start
        {
            front = 0;
        }
        else
        {
            front++; // normal popFront
        }
        return ans;
    }
    int popRear()
    {
        if (isEmpty())
        {
            return -1;
        }
        int ans = arr[rear];
        arr[front] = -1;
        if (front == rear) // both are at zero, single element, bring both to initial
        {
            front = rear = -1;
        }
        else if (rear == 0) // rear at start then cylically being to start
        {
            rear = size - 1;
        }
        else
        {
            rear--; // normal popRear;
        }
        return ans;
    }

    bool isEmpty()
    {
        if (front == -1)
        {
            return true;
        }
        return false;
    }

    bool isFull()
    {
        if ((front == 0 && rear == size - 1) || (front != 0 && rear == (front - 1) % (size - 1)))
        {
            // front at start and rear at end, OR rear is one behind front
            return true;
        }
        return false;
    }
    int getFront()
    {
        if (isEmpty())
        {
            return -1;
        }
        return arr[front];
    }
    int getRear()
    {
        if (isEmpty())
        {
            return -1;
        }
        return arr[rear];
    }
};

void DEqueueSTL()
{
    deque<int> d;
    d.push_front(12);
    d.push_back(14);
    d.push_back(25);
    cout << d.front() << endl;
    cout << d.back() << endl;
    d.pop_front();
    cout << d.front() << endl;
    cout << d.empty() << endl;
    d.pop_back();
    cout << d.empty() << endl;
}

int main()
{
    // DEqueueSTL();
    DEqueue q(5);
    q.pushRear(12);
    q.pushRear(13);
    cout << q.getFront() << endl;

    q.pushRear(16);
    q.pushRear(22);
    q.pushRear(45);
    cout << q.getRear() << endl;
    cout << q.isEmpty() << endl;
    cout << q.isFull() << endl;
    cout << q.popFront() << endl;
    q.pushRear(55);
    cout << q.getRear() << endl;
    cout << q.isEmpty() << endl;
    cout << q.isFull() << endl;

    return 0;
}