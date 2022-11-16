#include <iostream>
#include <limits.h>
#include <queue>
using namespace std;

//===================== Smallest Range in k list ========================
/*
Approach 1:
    -   (n*k) elements, find all ranges,
    -   For every element, compare with (n*k other elements) to check the range
    -   so TC O((n*k)^2)
    -   Check everylist difference and store the smallest
*/

/*
Approach 2:
    -   Push first element of each linked list into a data structure sort it, it will be potential answer range
    -   Now to reduce range to find minimum, we can either increase [start...] or decrease[...end].
    -   We cannt decrease end, because then last and many other rows will be left, as there element might not be included
    -   So we only move forward the start node, and find [start, end ] again and check if end-start i.e. the range is smaller then previous
    -   Do this until lists are exhausted, at the end we have smallest range [start, end] as the answer

    Pseudo Code:
    -   push all first elements into structure
    -   Find min max
    -   Move forward start
    -   until lists over
            Move forward start
                if new max-min < earlier max - min
                    ans = new max- min

    traversing all elements n*k
    In this finding min/max requires O(k) every time
    TC = O(n*k^2), SC = O(k), storing all k row elements
*/

/*
Approach 3: Find min using Heap
    -   We can use minHeap for min element and can track max with variable,
    -   Pushing into heap takes O(log k)
    -   Push first k lements  into k size minHeap
            Track min
            track max
    -   Heap nodes contain info of data, row, col of that element so that we can move forward in that list
    -   Move forward min, and if range is small, update the ans
    -   until lists are exhausted

*/
class Node
{
public:
    int data;
    int row;
    int col;
    Node(int d, int r, int c)
    {
        data = d;
        row = r;
        col = c;
    }
};
// custom comparator for Node* type minHeap
class compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->data > b->data;
    }
};

int kSorted(vector<vector<int>> &a, int k, int n)
{
    int mini = INT_MAX, maxi = INT_MIN;
    priority_queue<Node *, vector<Node *>, compare> minHeap;
    // Push all first k nodes into minHeap
    for (int i = 0; i < k; i++)
    {
        int element = a[i][0];
        mini = min(mini, element); // update mini
        maxi = max(maxi, element); // update max
        minHeap.push(new Node(element, i, 0));
    }
    // intial potential answer range [start, end]
    int start = mini, end = maxi;

    while (!minHeap.empty())
    {
        Node *temp = minHeap.top(); // smallest of the k elements anytime at the top
        minHeap.pop();
        mini = temp->data;

        if (maxi - mini < end - start)
        {
            // new range is smaller than earlier, update range
            start = mini;
            end = maxi;
        }
        // if there are more elements in this list
        if (temp->col + 1 < n)
        {
            // update max, just in case
            maxi = max(maxi, a[temp->row][temp->col + 1]);
            // push into heap
            minHeap.push(new Node(a[temp->row][temp->col + 1], temp->row, temp->col + 1));
        }
        else // any list exhausted
        {
            break;
        }
    }
    // the range we're left with
    return end - start + 1;
}

int main()
{

    return 0;
}