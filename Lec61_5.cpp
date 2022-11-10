#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// ================== Circular Tour ==================

// function to print the queue
void printQueue(queue<char> q)
{
    // printing content of queue
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

/*  Approach 1:
    checking starting from each index, where is it possible to complete the tour: TC O(n^2)
*/

/*  Approach 2:

    1.  if(petrol - distance) >=0 at ith station and travel to next is possible -> rear++;
    2.  Repeating this if front == rear then tour complete
    3. if
        (start->next) possible then rear++
    4. else
        front = rear +1;
        start = front;
        rear = front;
    5. If starting from ith index, it not possible to move beyond some jth index because balance went negative then going from any indices in between i and j to j will also not be possible => Because for each next station balance is carried forward, so start from i+1, i+2 will only cause lesser balance to reamin when reaching j and because balance from previous journeys was not contributed. So next point we check starting from (j+1)th index.
    6. Worst case: May require to visit each node twice.
*/

/*  Approach 3:

    From start, let balance become -k at ith index, then from i+1th index to 0[start], check if balance >= k, then it balances out earlier deficit. So then tour is possible from (i+1)th index.

*/
int cicularTour(int petrol[], int distance[], int n)
{
    int deficit = 0;
    int balance = 0;
    int start = 0;
    for (int i = 0; i < n; i++)
    {
        balance += petrol[i] - distance[i];
        if (balance < 0)
        {
            deficit += balance;
            start = i + 1;
            balance = 0;
        }
    }
    if (deficit + balance >= 0)
    {
        return start;
    }
    return -1;
}

int main()
{

    int petrol[] = {4, 6, 7, 4};
    int distance[] = {6, 5, 3, 5};
    int ans = cicularTour(petrol, distance, 4);
    cout << ans << endl;
    return 0;
}