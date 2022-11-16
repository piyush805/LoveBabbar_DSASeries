#include <iostream>
#include <queue>
using namespace std;

//===================== Merge k sorted arrays ========================
/*
Approach 1:
    -   Traverse all, insert into one ans array
    -   sort ans array
    -   TC = O(n*k log (n*k));
Here time complexisty , and no use of fact that they are sorted
*/
class Node
{
public:
    int data;
    int i;
    int j;
    Node(int data, int row, int col)
    {
        this->data = data;
        i = row;
        j = col;
    }
};

class compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        return a->data > b->data;
    }
};

vector<int> merge(vector<vector<int>> &kArrays, int k)
{
    priority_queue<Node *, vector<Node *>, compare> minHeap; // minHeap of type Node*
    vector<int>ans;
    for (int i = 0; i < k; i++)                              // All arrays first elements inserted
    {
        Node *tmp = new Node(kArrays[i][0], i, 0);
        minHeap.push(tmp);
    }
    while (minHeap.size() > 0)
    {
        Node *tmp = minHeap.top(); // smallest element at top
        ans.push_back(tmp->data);  // push that into ans
        minHeap.pop();             // pop this smallest
        int i = tmp->i;
        int j = tmp->j;
        if (j + 1 < kArrays[i].size()) // check if next element of the array exisis
        {
            Node *next = new Node(kArrays[i][j + 1], i, j + 1); // then create a new node with this element
            minHeap.push(next);                                 // push it into heap
        }
    }
    return ans;
}

int main()
{
    //2D vector of int
    return 0;
}