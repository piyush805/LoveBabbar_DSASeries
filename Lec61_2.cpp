#include <iostream>
#include <queue>
using namespace std;

// =========First Negative Integer in window of K===================

// function to print the queue
void printQueue(deque<long long int> q)
{
    // printing content of queue
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop_front();
    }
    cout << endl;
}

vector<long long> firstNegative(vector<long long> A, int k, int n)
{
    deque<long long int> dq;
    vector<long long> ans;
    // Push in dq index of all -ve integers in first window size K
    for (int i = 0; i < k; i++)
    {
        if (A[i] < 0)
        {
            dq.push_back(i);
        }
    }
    // If there was any integer index pushed in 1st time
    if (dq.size() > 0)
    {
        ans.push_back(A[dq.front()]);
        // 1st -v integer index of dq.front() so push this index element into the answer
    }
    else
    {
        // if none index was pushed and no -ve integer in this first window
        ans.push_back(0);
    }
    // from kth to end move window,add one element to window and remove front of the window
    for (int i = k; i < n; i++)
    {
        cout << "Window:";
        printQueue(dq);
        if (!dq.empty() && i - dq.front() >= k)
        {
            dq.pop_front(); // remove front of window
        }

        if (A[i] < 0)
        {
            dq.push_back(i); // pushed newly encountered -ve integer into deque
        }

        if (dq.size() > 0) // If there was any integer index pushed in 1st time
        {

            ans.push_back(A[dq.front()]);
            // 1st -v integer index of dq.front() so push this index element into the answer
        }
        else
        {
            ans.push_back(0);
            // if none index was pushed and no -ve integer in this first window
        }
    }
    return ans;
}

int main()
{
    vector<long long> A{-8, 2, 3, -6, 10};
    cout << "Array is: ";
    for (int i = 0; i < A.size(); i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
    vector<long long> v = firstNegative(A, 3, 5);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    return 0;
}