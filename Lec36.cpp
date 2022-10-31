#include <iostream>
using namespace std;
void print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}



int partition(int *arr, int s, int e)
{
    int pivot = arr[s]; // take any element we are taking first
    int cnt = 0;
    // count all the smaller or equal elements ahead of pivot
    for (int i = s + 1; i <= e; i++)
    {
        if (arr[i] <= pivot)
        {
            cnt++;
        }
    }
    // cnt = place at which pivot should be at, ahead of its current position s
    int pivotIndex = s + cnt; // find right place
    // place pivot at that position
    swap(arr[pivotIndex], arr[s]); // shift pivot to correct place

    // Now swap all bigger than pivot element on left of pivot with smaller than pivot element on right of pivot [only between s and e, not the entire array]
    int i = s, j = e;
    // when either reach pivot i.e until either side is done
    // i.e either all elements on left are smaller AND all element on right are bigger = thats how they should be after all swappings
    while (i < pivotIndex && j > pivotIndex)
    {
        while (arr[i] <= pivot)
        {
            // skip smaller elements AND EQUAL on left(because we counted equal elements as well in cnt i.e pivot should be ahead of those and theyre already on its left therefore correct) and check next
            // stop at bigger element
            i++;
        }
        while (arr[j] > pivot)
        {
            // skip all bigger elements on the right and check next leftward
            // stop at smaller element
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            // swap bigger elements on the left with smaller elements on the right
            swap(arr[i], arr[j]);
            // check next
            i++;
            j--;
        }
    }
    return pivotIndex;
}

void quickSort(int *arr, int s, int e)
{
    // base case
    if (s >= e)
    {
        return;
    }
    // partition
    int p = partition(arr, s, e);
    // Recursion calls
    quickSort(arr, s, p - 1);
    quickSort(arr, p + 1, e);
}

int main()
{
    int arr[] = {6, 6, -6, -2, -4, -6, 2, -6 };
    int size = 8;

    cout << "Given array: ";
    print(arr, size);

    quickSort(arr, 0, size - 1);

    cout << "Sorted array: ";
    print(arr, size);
    return 0;
}