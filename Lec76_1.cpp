#include <iostream>
#include <queue>
using namespace std;

//===================== kth largest sum array ===========================
/*
Approach 1:
    -   i upto n
            j upto n
                sum all store in a vector
sort and find kth largest
TC = O(n^2 Log n)
SC = O(n^2)
*/

/*
Approach 2:
    -   Optimize using minheap SC = O(k)
    -   no vector
*/

int getKthLength(vector<int> arr, int k)
{
    // minheap top is smallest element is at the top
    priority_queue<int, vector<int>, greater<int>> min;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += arr[j];
            // push elements only upto k at a time
            // cout<<"sum now: "<<sum<<endl;
            if (min.size() < k)
            {
                min.push(sum);
            }
            else
            {
                // kth largest element logic
                if (sum > min.top())
                {
                    min.pop();
                    min.push(sum);
                }
            }            
        } // second for loop
    }     // first for loop
    // at the end mini heap will contain k number of sums,
    //  with smallest at the top, so that will be kth largest
    return min.top();
}

int main()
{
    vector<int> arr{3, -2, 5};
    int k = 2;
    int ksum = getKthLength(arr, k);
    cout << ksum << endl;
    return 0;
}