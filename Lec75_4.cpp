#include <iostream>
#include <queue>
using namespace std;

//===================== Merge two Binary Max Heap ============================

void heapify(vector<int> &arr, int n, int i)
{
    int largest = i; // let largest be current and wego further down to find which is actually largest
    int left = 2 * i + 1;//0 based indexing
    int right = 2 * i + 2;
    // update largest index by comparing with left and right child, make sure left and right are within bounds
    if (left < n && arr[largest] < arr[left])
    {
        largest = left;
    }
    if (right < n && arr[largest] < arr[right])
    {
        largest = right;
    }
    // If index was updated then swap those two
    if (largest != i)
    {
        swap(arr[largest], arr[i]);
        // Now check further if element placed at this need to updated further wrt child
        // so call again with this new index 'largest'
        heapify(arr, n, largest);
    }
}

vector<int> mergeTwoMaxHeaps(vector<int> a, vector<int> b, int m, int n)
{
    // merge both the arays as it is
    vector<int> ans;
    for (auto i : a)
        ans.push_back(i);
    for (auto i : b)
        ans.push_back(i);

    int size = ans.size();

    // heapify to create maxHeap out of given random array
    //0 based indexing, n/2 - 1 and go upto 0
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(ans, size, i);
    }
    return ans;
}

int main()
{
    vector<int> a{10, 5, 6, 2};
    int m = 4;
    vector<int> b{12, 7, 9};
    int n = 3;
    vector<int> c = mergeTwoMaxHeaps(a, b, m, n);
    for (int i = 0; i < c.size(); i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;
    return 0;
}