#include <iostream>
#include <queue>
using namespace std;

// =========== Sum of Max and Min in k size window ==============

// Approach 1: Brute Force: TC O(n*k)
int sumMaxMinK_1(int *arr, int n, int k)
{
    int ans = 0;
    // i=0 to last window n-k to n-1
    for (int i = 0; i <= n - k; i++)
    {
        int max = INT_MIN;
        int min = INT_MAX;
        // Find max & min for each window size K
        for (int j = i; j < i + k; j++)
        {
            if (arr[j] <= min)
            {
                min = arr[j];
            }
            if (arr[j] >= max)
            {
                max = arr[j];
            }
        }
        // Sum max min for this window
        ans += max + min;
    }

    return ans;
}

// Approach 2: Queue, updating min and max in queues while shifting windows, and summing
// TC = O(n), SC = O(k)
int sumMaxMinK_2(int *arr, int n, int k)
{
    deque<int> maxi(k);
    deque<int> mini(k);
    // First Window
    for (int i = 0; i < k; i++)
    {
        while (!maxi.empty() && arr[maxi.back()] <= arr[i])
        {
            // pop all smaller elements
            maxi.pop_back();
        }
        while (!mini.empty() && arr[mini.back()] >= arr[i])
        {
            // Pop all greater elements in each iteration
            mini.pop_back();
        }
        maxi.push_back(i);
        // maxi elements will be in decreasing order
        mini.push_back(i);
        // mini elements will be in increasing order
    }

    int ans = 0;

    for (int i = k; i < n; i++)
    {
        ans += arr[maxi.front()] + arr[mini.front()];

        // Removal
        while (i - maxi.front() >= k)
        {
            maxi.pop_front();
        }
        while (!mini.empty() && i - mini.front() >= k)
        {
            mini.pop_front();
        }

        // Addition
        while (!maxi.empty() && arr[maxi.back()] <= arr[i])
        {
            maxi.pop_back();
        }
        while (!mini.empty() && arr[mini.back()] >= arr[i])
        {
            mini.pop_back();
        }

        maxi.push_back(i);
        mini.push_back(i);
    }
    // answer for last instance not calcualed as contd becomes false and it comes out of the loop before ans+=...
    ans += arr[maxi.front()] + arr[mini.front()];

    return ans;
}
/*
DRY RUN Approach 2:

First Window [0, 3]
=> i = 0 maxi: 0 mini: 0
in maxi 2<5 so 0(index of 5) popped and index of 2 is 1 pushed
=> i = 1 maxi: 1, mini: 0
in mini -1 < 2 so 0(index of 2 ) popped and index of -1 is 2 pushed
=> i =2 maxi: 1 mini: 2
in maxi, 1(index of 5) popped because 5<7 and pushed 3(index of 7)
=> i =3 maxi: 3, mini: 2

ans = arr[3] + arr[2] = 7 + (-1) = 6
=> i = 4; window [1, 4]
    Removal
    maxi 3, mini 2 - as these indices lie within new window as well, if it were 0 then it would be popped
    Addition
    maxi 3, mini 4 - mini popped 2(index of -1) and pushed 4(index of -3)

=> i = 5; window [2, 5]
    ans = 6 + (7) + (-3) = 10
    maxi 3, mini 4: No removal maxi front 3 within [2,5] and 4 also within [2, 5]
    maxi 3, mini 4: No addtion because maxi 7 > -1 and -3 < -1

=> i =6; window [3, 6]
    ans = 10 + (7) +(-3) = 14
    maxi 3, mini 4: No removal maxi front 3 within [2,5] and 4 also within [2, 5]
    maxi 3, mini 4: No addtion because maxi 7 > -2 and -3 < -2

For loop breaks on i = 7
ans = 14  + (7) + (-3) = 18

*/

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
    int arr[] = {2, 5, -1, 7, -3, -1, -2};
    int n = 7;
    int k = 4;
    int ans = sumMaxMinK_1(arr, n, k);
    cout << ans << endl;
    return 0;
}
