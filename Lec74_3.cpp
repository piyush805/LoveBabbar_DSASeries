#include <iostream>
using namespace std;

//======================= HEAP Sort =============================
/*
    Elements given as decreasing order max heap 
    can be sorted in increasing order in O(n log n)
    By using heapify
*/


// Function to convert given array into Heap
/*
    Traverse Heap array from the right end and check if its valid heap
    contd: if arr[i] > arr[2*i] and arr[i]> arr[2*i+1]
    if not then swap
    and call recusrion to heapify with index = this newly swapped place, going up

    Basially gets all nodes from n/2 to 1 to their correct place
*/
void heapify(int *arr, int n, int i)
{
    int largest = i; // let largest be current and wego further down to find which is actually largest
    int left = 2 * i;
    int right = 2 * i + 1;
    // update largest index by comparing with left and right child, make sure left and right are within bounds
    if (left <= n && arr[largest] < arr[left])
    {
        largest = left;
    }
    if (right <= n && arr[largest] < arr[right])
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
void print(int *arr, int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to sort element given as a maxHeap (in decreasing order), in increasing order
void heapSort(int *arr, int n)
{
    int size = n;
    while (size > 1)
    {
        swap(arr[size], arr[1]); // place root(largest) element at the end
        size--;                  // last is sorted so size --
        heapify(arr, size, 1);   // now with new root, find its right place, to make it correct heap again
    }
}

int main()
{

    int arr[6] = {-1, 70, 60, 55, 45, 50};//Elements to be given in decreasing order to represent max Heap
    int n = 5;
    print(arr, n);
    heapSort(arr, n);
    print(arr, n);
    return 0;
}