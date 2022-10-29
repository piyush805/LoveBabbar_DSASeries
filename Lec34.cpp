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

// Recusrive Function for insertion sort
void recInsertionSort(int *arr, int n)
{
    if (n == 1 || n == 0)
    {
        return;
    }
    // Algo : Work from i = 1 and inserting it to left sorted array

    recInsertionSort(arr, n - 1);

    // Insert last element at its correct position
    // in sorted array.
    int last = arr[n - 1];
    int j = n - 2;

    /* Move elements of arr[0..i-1], that are
    greater than key, to one position ahead
    of their current position */
    while (j >= 0 && arr[j] > last)
    {
        // until current element is smaller and not reached start of array, keeping shifting left element to one right
        arr[j + 1] = arr[j];
        j--;
    }
    // insert ahead of first smaller element then current element
    arr[j + 1] = last;
}

// Recursive Function for Selection sort
void recSelectionSort(int *arr, int n)
{
    if (n == 0 || n == 1)
    {
        return;
    }
    int minIndex = 0;
    // Find the smallest and place it at 0th index
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < arr[minIndex])
        {
            minIndex = i;
        }
    }
    swap(arr[minIndex], arr[0]);
    // Recursion for 1st to n-1th, placing ith smallest in ith place in each turn, moving forward and size decrasing by one for each call
    recSelectionSort(arr + 1, n - 1);
}

// Recursive Function for bubble sort
void recBubbleSort(int *arr, int n)
{
    if (n == 0 || n == 1)
    {
        // Base case: last element or none: fully sorted
        return;
    }
    // Solve one case: brings largest element to right most in the array
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            swap(arr[i], arr[i + 1]);
        }
    }
    // Recursion calls sort array upto (n-i)th element in ith round
    recBubbleSort(arr, n - 1);
}

// Recursive function to caulculate pow(a,b)
int recExponentiation(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return a;
    }
    int ans = recExponentiation(a, b / 2);
    if (b % 2 == 0)
    {
        return ans * ans;
    }
    else
    {
        return a * ans * ans; // odd power, multiple extra with for b+1: because all b we divided by 2
    }
}

// Recusrive function to check is char string is palindrome
bool checkPalindromeRec(string s, int i, int j)
{
    if (i > j)
    {
        // reached middle, all palindrome entire.
        return 1;
    }
    if (s[i++] != s[j--])
    {
        // if first and last don't match.
        return 0;
    }
    else
    {
        // check for the remaining middle string.
        return checkPalindromeRec(s, i, j);
    }
}

// Reversing a string using recursions
void reverseStrRec(string &str, int i, int j)
{
    if (i > j)
    {
        return;
    }

    swap(str[i++], str[j--]);

    reverseStrRec(str, i, j);
}

int main()
{
    // string str = "abcdefghi ihgfedcba";
    // // reverseStrRec(str, 0, str.length() - 1);
    // cout << checkPalindromeRec(str, 0, str.length() - 1) << endl;

    // int a, b;
    // cout << "Enter a and b for a^b: ";
    // cin >> a >> b;
    // cout << "The value of " << a << "^" << b << ": " << recExponentiation(a, b) << endl;

    int arr[] = {2, 4, 3, 5, 7, 6};
    int size = 6;
    cout << "Given array: ";
    print(arr, size);
    // recBubbleSort(arr, size);
    // recSelectionSort(arr, size);
    recInsertionSort(arr, size);
    cout << "Sorted array: ";
    print(arr, size);
    return 0;
}