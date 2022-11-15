#include <iostream>
using namespace std;

//======================= HEAP =============================
/*
    Max Heap: For every node at ith place,
    Left child is at = 2*i
    Right child is at = 2*i +1;
    Root position = 1, left child at 2, right child at 3
    For left child 2, its left child at 4, and right child at 5 and so on

    As  level order traversal stored in 1-indexed array

    Max Heap: both children greater than current node at each level: smallest element at top

*/
class heap
{
public:
    // Heap is an array with certain properties visualised as an binary tree
    int arr[100];
    int size;
    heap()
    {
        arr[0] = -1;
        size = 0;
    }

    void insert(int val)
    {

        /*Inserting an element
            check wrt parent where its right position
            Place it at that position where it is to be swapped
            Then
            TC-> O(log n)
        */
        size = size + 1;  // increase size to accomodate 1 more element
        int index = size; // insertion to be at right end
        arr[index] = val; // insert at the end
        while (index > 1) // reached root => heap done
        {
            int parent = index / 2; // for both left and right child, parents position will be same
            if (arr[parent] < arr[index])
            {
                // comapre and swap this new element parent element, and this parent index is where new index of this element is
                swap(arr[parent], arr[index]);
                index = parent;
            }
            else // if at some point swap doesnt happen then heap done
            {
                return;
            }
        }
    }
    // Function to print out value of heap, as an array
    void print()
    {
        for (int i = 1; i <= size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void deleteFromHeap() // the root node
    {
        if (size == 0)
        {
            cout << "Nothing to delete" << endl;
            return;
        }
        arr[1] = arr[size]; // store last element at top position
        size--;             // root replaced

        int i = 1;
        // Fix the entire tree now with new element as root
        while (i < size)
        {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;
            if (leftIndex < size && arr[leftIndex] > arr[i] && arr[leftIndex] > arr[rightIndex]) // if left index grestest among the three
            {
                swap(arr[i], arr[leftIndex]); // swap inserted node with left, and this leftindex is the new index of the deleted value element
                i = leftIndex;
            }
            else if (rightIndex < size && arr[i] < arr[rightIndex] && arr[leftIndex] < arr[rightIndex]) // if right index greatest among the three
            {
                swap(arr[i], arr[rightIndex]); // swap inserted node with right, and this rightindex is the new index of the deleted value element
                i = rightIndex;
            }
            else // if this newly is greatest among the 3 then it is at right place
            {
                return;
            }
        }
    }
};

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
void callHeapify()
{
    // leaf nodes in array from n/2 +1 to n, so there are heap in itself so no need to check
    int arr[6] = {-1, 54, 55, 53, 52, 50};
    int n = 5;
    print(arr, n);
    for (int i = n / 2; i > 0; i--)
    {
        heapify(arr, n, i);
    }
    print(arr, n);
}
int main()
{
    heap h;
    // h.size = 5;
    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.insert(52);
    h.insert(54);
    // // callHeapify(h.arr, h.size);
    // h.print();
    // h.deleteFromHeap();
    // h.print();

    callHeapify();
    return 0;
}