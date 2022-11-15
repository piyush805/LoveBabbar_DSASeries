#include <iostream>
#include <queue>
using namespace std;

//===================== Min Cost of Ropes ============================

long long minCost(long long arr[], long long n)
{
    /*
    Each time pick out 2 min elements, add them and push into pq until size is 1
    */
    priority_queue < long long, vector<long long>, greater<long long>> pq;
    for (long long i = 0; i < n; i++)
    {
        pq.push(arr[i]);
    }
    long long cost = 0;
    while (pq.size() > 1)
    {
        long long a = pq.top();
        pq.pop();
        long long b = pq.top();
        pq.pop();

        long long sum = a + b;
        cost += sum;

        pq.push(sum);
    }
    return cost;
}

int main()
{
    long long arr[] = {4, 3, 2, 6};
    long long n = 4;
    cout << minCost(arr, n) << endl;

    return 0;
}