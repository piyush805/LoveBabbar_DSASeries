#include <iostream>
#include <limits.h>
#include <queue>
using namespace std;

//===================== Median in a stream ========================
/*
Approach 1:
    - Incoming stream so search using binary search for the correct place of element and insert it by shifting left/right elements then find median
    - Insertion Sort O(N^2)
*/

/*
Approach 2:
    -   All left to median will be smaller elements
    -   All right to median will be greater elements
    -   Case 1: [n-1 elements][n elements]
    -   Case 2: [n elements][n-1 elements]
    -   Case 3: [n elements][n elements] (when even number of elements)
    -   Lets make heap of left and right part
        -    max heap on left because we want its largest element(the number just before median) on top
        -   min heap on right because we want smallest of that range at top(the number just next of median)
    -   then median would be (maxiheap.top() + miniheap.top())/2;

    - for i=0, i<n; call median function to find median for stream adding a successive element,

For every element, we make comparison where to put left or right,
TC ->O( n log n)
*/
// Function to compare size of diff heaps, whether equal or which one greater or smaller
int signum(int a, int b)
{
    if (a == b)
    {
        return 0;
    }
    else if (a > b)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void callMedian(int element, priority_queue<int> &maxi, priority_queue<int, vector<int>, greater<int>> &mini, int &median)
{
    cout << element << endl;
    switch (signum(maxi.size(), mini.size()))
    {

    case 0: // when both have equal elements, even no. total

        if (element > median)
        {
            // bigger element pushed into min heap
            mini.push(element);
            median = mini.top();
        }
        else // smaller element pushed into max heap
        {
            maxi.push(element);
            median = maxi.top();
        }
        break;

    case 1: //: max heap smaller  n-1 and n element
        if (element > median)
        {
            // greater element pushed into min heap so now-> n, n
            mini.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        else // smaller element cant be pushed into max because then it will be n-1 and n+1;
        // so we take on from maxheap and push into min, making it n, n-1;
        // then pushed this element into max heap so now case of n,n;
        {
            mini.push(maxi.top());
            maxi.pop();
            maxi.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        break;

    case -1: // min heap smaller:  n and n-1 elements
        if (element > median)
        // greater element to be pushed in to min heap but then it will become n+1, and n-1;
        // so we pop top from min and push into max making it n-1, and n
        // now push this element into minheap
        {
            maxi.push(mini.top());
            mini.pop();
            mini.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        else //
        {
            // smaller element pushed into max heap
            maxi.push(element);
            median = (mini.top() + maxi.top()) / 2;
        }
        break;
    }
}

vector<int> findMedian(vector<int> &arr, int n)
{
    vector<int> ans;
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int median = 0;
    for (int i = 0; i < n; i++)
    {
        callMedian(arr[i], maxHeap, minHeap, median); // median of stream after this new element
        ans.push_back(median);
    }
    return ans;
}
int main()
{
    vector<int> arr{2, 1, 3};
    int n = 3;
    vector<int> ans = findMedian(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}