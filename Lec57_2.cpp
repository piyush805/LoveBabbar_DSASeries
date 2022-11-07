#include <iostream>
#include <stack>
#include <vector>
#define MAX 1000

using namespace std;
//===============Largest Rectangle area in Binary MATRIX===============

// Find 1st bar with smaller height than ith bar on right
vector<int> nextSmallerElement(int *arr, int n)
{
    stack<int> s;
    s.push(-1); // if none possible then -1 answer
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--)
    {
        int curr = arr[i];
        while (s.top() != -1 && arr[s.top()] >= curr)
        {
            // until smaller element found or -1 reached
            s.pop();
        }
        ans[i] = s.top(); // ans is that smaller element or -1 if none
        s.push(i);
    }
    return ans;
}

// Find 1st bar with smaller height than ith bar on left
vector<int> prevSmallerElement(int *arr, int n)
{
    stack<int> s;
    s.push(-1); // if none possible then -1 answer
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        int curr = arr[i];
        while (s.top() != -1 && arr[s.top()] >= curr)
        {
            s.pop(); // until smaller element found or -1 reached
        }
        ans[i] = s.top(); // ans is that smaller element or -1 if none
        s.push(i);
    }
    return ans;
}

// Each height bar can only cross across bars which are greater height until a smaller bar is encountered.
// Bar to extend to either side.
// thus calculate area of each by multiplying height(i) *[prev(i)-next(i)]
// return the max
int largestRectangleArea(int *heights, int n)
{

    // int n = heights.size();

    vector<int> next(n);
    next = nextSmallerElement(heights, n); // Find all smaller bar indexes on right
    vector<int> prev(n);
    prev = prevSmallerElement(heights, n); // Find all smaller bar indexes on right
    int area = INT_MIN;
    // calculate area of each and returning max area
    for (int i = 0; i < n; i++)
    {
        int l = heights[i]; // height of that bar
        if (next[i] == -1)  // for right most bar, extneding value is -1
        {
            next[i] = n; // but we replace it with n
        }
        int b = next[i] - prev[i] - 1; // because 0 based indexing
        int newArea = l * b;
        area = max(area, newArea); // update maxarea in each step
    }
    return area;
}

int maxArea(int M[4][4], int n, int m)
{
    int area = largestRectangleArea(M[0], m);
    for (int i = 1; i < n; i++) // for each new row
    {
        for (int j = 0; j < m; j++) // add all previous rows to it
        {
            if (M[i][j] != 0)
            {
                M[i][j] = M[i][j] + M[i - 1][j];
            }
            else
            {
                M[i][j] = 0;
            }
        }
        // find the new area considerign this new area as base
        int newArea = largestRectangleArea(M[i], m);
        // update maximum
        area = max(area, newArea);
    }
    return area;
}

int main()
{
    int M[4][4] = {{0, 1, 1, 0},
                   {1, 1, 1, 1},
                   {1, 1, 1, 1},
                   {1, 1, 0, 0}};
    int n = 4, m = 4;
    cout << maxArea(M, n, m) << endl;
    return 0;
}
