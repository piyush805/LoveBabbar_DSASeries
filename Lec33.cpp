#include <iostream>
using namespace std;

//Recursive function for binary Search
int binaryRec(int arr[], int s, int e, int k)
{
    if (s > e)
    {
        // array over
        return -1;
    }
    int mid = s + (e - s) / 2;
    if (arr[mid] == k)
    {
        // found
        return mid;
    }
    if (arr[mid] < k)
    {
        // find on right: modify s
        return binaryRec(arr, mid + 1, e, k);
    }
    else
    {
        // find on left: modify e
        return binaryRec(arr, s, mid - 1, k);
    }
}

// Recursive function for linear search
bool linearRec(int arr[], int n, int key)
{
    if (n == 0)
    {
        // end of the array without having found the element
        return false;
    }
    // Logic: Check if first element of array is key else check in rest of the array...until the size = 0
    if (arr[0] == key)
    {

        return true;
    }
    else
    {
        bool remain = linearRec(arr + 1, n - 1, key);
        return remain;
    }
}

// Recursive function to calculate sum of the array
int sumRec(int arr[], int n)
{
    if (n == 1)
    {
        // return last element when size remains 1: that is the sum
        return arr[0];
    }
    // Sum of n element = sum of first + rest n-1 elements
    // add element from right to left on each return of sumRec
    int sum = arr[0] + sumRec(arr + 1, n - 1);
    return sum;
}

// Recursive function to check if an array is sorted
bool isSorted(int arr[], int n)
{

    if (n == 0 || n == 1)
    {
        // reached and of array hence sorted
        return 1;
    }
    if (arr[0] > arr[1])
    {
        // For new array, if i and i+1 not sorted then no further calls, return false from here itself
        return 0;
    }
    else
    {
        // check for further values until end sorted upto i
        bool result = isSorted(arr + 1, n - 1);
        // return back whatever result from i+1 to end
        return result;
    }
}

int main()
{
    int array[] = {2, 5, 7, 8, 9, 12, 16, 18, 26};
    int size = 9;
    // if (isSorted(array, size))
    // {
    //     cout << "Sorted" << endl;
    // }
    // else
    // {
    //     cout << "Not sorted" << endl;
    // }

    // cout << "The sum of array is " << sumRec(array, size) << endl;

    cout << "Is element present int the array? " << binaryRec(array, 0, 8, 18) << endl;
    return 0;
}