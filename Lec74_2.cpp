#include <iostream>
#include <vector>
using namespace std;

//======================= Build a min Heap =============================

void print(int *arr, int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
// Function to build minheap from a given array
void buildMinHeap(int *arr, int n, int i)
{
    // MinHeap: parent < left && parent<right
    int smallest = i; // smallest element be at top
    int left = 2 * i; // since given in question that arr[] follows 0 based indexing
    int right = 2 * i + 1;
    // comapre with left and right child to update smallest index
    if (left <= n && arr[smallest] > arr[left])
    {
        smallest = left;
    }
    if (right <= n && arr[smallest] > arr[right])
    {
        smallest = right;
    }
    // if value was smallest was updated then swap the two elements
    if ((smallest != i))
    {
        swap(arr[smallest], arr[i]);
        // and check further if now this element at new index 'smallest' is at right place
        buildMinHeap(arr, n, smallest);
    }
}

void callBuildMinHeap()
{

    int arr[6] = {-1, 54, 55, 53, 52, 50};
    int n = 5;
    print(arr, n);
    for (int i = n / 2; i > 0; i--)
    {
        buildMinHeap(arr, n, i);
    }
    print(arr, n);
}

int main()
{
    callBuildMinHeap();
    return 0;
}