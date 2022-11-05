#include <iostream>
#include <stack>
#include <vector>
using namespace std;
//==========================Largest Rectangle area in histrogram=====================================

// Find 1st bar with smaller height than ith bar on right
vector<int> nextSmallerElement(vector<int> arr, int n)
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
vector<int> prevSmallerElement(vector<int> arr, int n)
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
int largestAreaRectangle(vector<int> &heights)
{

    int n = heights.size();

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

int main()
{
    vector<int> heights{2, 1, 5, 6, 2, 3};
    cout << "Maximum passible area of rectangle: " << largestAreaRectangle(heights) << endl;
    return 0;
}