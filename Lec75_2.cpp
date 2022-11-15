#include <iostream>
#include <queue>
using namespace std;

//===================== Kth largest element ============================
/*
Approach 1:
    Sort array and find k-1th element from end
    TC O(n log n)

Approach 2:
    Build heap for first k elements
    for rest elements, push elements if (pq.top() > elemenet)
    heap.pop();
    heap.push(element)
    Heap will have k smallest elements, because we push only smaller elements and pop the rest
    And in maxHeap largest element is at the top, which is kth largest element
*/

int kthLargestElement(int *arr, int l, int r, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    // push first k element
    for (int i = l; i < k; i++)
    {
        pq.push(arr[i]);
    }
    // kth to end check if smaller pop then push
    for (int i = k; i <= r; i++)
    {
        // only push elements smaller than top
        if (arr[i] > pq.top())
        {
            pq.pop();        // again processes to become correct maxHeap
            pq.push(arr[i]); // On push processes to become correct maxHeap
        }
    }
    // only k smallest elements remain in stack, ans at top is largest of them=> kth smallest element of the array
    int ans = pq.top();
    return ans;
}

int main()
{
    int arr[] = {7, 10, 4, 20, 5};
    int k = 2;
    int l = 0;
    int r = 4;
    int ans = kthLargestElement(arr, 0, 4, k);
    cout << ans << endl;
    return 0;
}