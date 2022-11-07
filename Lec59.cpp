#include <iostream>
#include <stack>
using namespace std;
// Specail Stack with minimum element to find in TC O(1), and SC O(1).
class SpecialStack
{
    stack<int> s;
    int mini;

public:
    void push(int data)
    {
        if (s.empty()) // First element normal push
        {
            s.push(data);
            mini = data;
        }
        else
        {
            if (data < mini)
            {
                int val = 2 * data - mini; // value to push so that when pop, we can calculate min below this value
                s.push(val);
                mini = data; // new min
            }
            else
            {                 // data > mini so, mini will not be updated when popping and comparing so data pushed as it is
                s.push(data); // normal push
            }
        }
    }

    int pop()
    {
        if (s.empty()) // underflow
        {
            return -1;
        }

        int curr = s.top();
        s.pop();

        if (curr > mini)
        {
            return curr; // normal pop
        }
        else
        {
            int prevMin = mini;
            int val = 2 * mini - curr;
            mini = val;
            return prevMin;
        }
    }

    int top()
    {
        if (s.empty())
        {
            return -1;
        }
        int curr = s.top();
        if (curr < mini) // because not all are real values but modified ones
        {
            return mini;
        }
        else
        {
            return curr;
        }
    }

    bool isEmpty()
    {
        return s.empty();
    }

    int getMin()
    {
        if (s.empty())
        {
            return -1;
        }
        return mini;
    }
};

int main()
{
    SpecialStack s;
    s.push(13);
    s.push(47);
    cout << "Min: " << s.getMin() << endl;
    cout << "Empty? " << s.isEmpty() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Empty? " << s.isEmpty() << endl;
    cout << "Top: " << s.top() << endl;

    return 0;
}