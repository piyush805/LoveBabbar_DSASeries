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

void printMerge(int *arr, int s, int e)
{
    for (int i = s; i <= e; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void merge(int *arr, int s, int e)
{
    // Like code of merging two sorted arrays
    int mid = s + (e - s) / 2;
    int len1 = mid - s + 1;
    int len2 = e - mid;
    // to make 2 new half size arrays out of current array
    int *first = new int[len1];
    int *second = new int[len2];

    int mainArrayIndex = s;
    // Copy first half elements in 1st array
    for (int i = 0; i < len1; i++)
    {
        first[i] = arr[mainArrayIndex++];
    }
    // Copy second half element in 2nd array
    for (int i = 0; i < len2; i++)
    {
        second[i] = arr[mainArrayIndex++];
    }

    int index1 = 0, index2 = 0;
    mainArrayIndex = s; // third index
    // Sort the elements of 2 arrays and copy them into mainArray
    while (index1 < len1 && index2 < len2)
    {
        if (first[index1] < second[index2])
        {
            arr[mainArrayIndex++] = first[index1++];
        }
        else
        {
            arr[mainArrayIndex++] = second[index2++];
        }
    }
    // if first array was bigger, copy its element as they are
    while (index1 < len1)
    {
        arr[mainArrayIndex++] = first[index1++];
    }
    // if second array was longer copy its element as they are
    while (index2 < len2)
    {
        arr[mainArrayIndex++] = second[index2++];
    }
    // delete the dynamically allocated first and second arrays
    delete[] first;
    delete[] second;
}

void recMergeSort(int *arr, int s, int e)
{
    // cout << "Incoming overall: ";
    // printMerge(arr, s, e);
    if (s >= e)
    {
        // Equal means single element remains = already sorted
        return;
    }
    int mid = s + (e - s) / 2;

    // cout << "Incoming for left: ";
    // printMerge(arr, s, mid);
    // Sort left half
    recMergeSort(arr, s, mid);
    // cout << "Left: ";
    // printMerge(arr, s, mid);

    // Sort right half
    // cout << "Incoming for Right: ";
    // printMerge(arr, mid + 1, e);
    recMergeSort(arr, mid + 1, e);
    // cout << "Right: ";
    // printMerge(arr, mid + 1, e);

    // merge 2 sorted arrays
    merge(arr, s, e);
    // cout << "Merge: ";
    // printMerge(arr, s, e);
}

int main()
{
    int arr[] = {2, 4, 3, 5, 7, 6, 12, -5};
    int size = 8;

    cout << "Given array: ";
    print(arr, size);

    recMergeSort(arr, 0, size - 1);

    cout << "Sorted array: ";
    print(arr, size);

    return 0;
}