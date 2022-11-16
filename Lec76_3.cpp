#include <iostream>
#include <queue>
using namespace std;

//===================== Merge k sorted Linked Lists ========================
/*
Approach 1:
    -   Traverse all, insert into one ans vector
    -   sort ans array
    -   make linked list from array
    -   TC = O(n*k log (n*k));
Here time complexisty , and no use of fact that they are sorted
But no extra space allowed
*/

/*
Approach 2:
    -   1st element of all lists into minHeap- using head and tail, because no extra space
    -   minHeap sorts and pushed smallest element at top each time, so pop the top and push it into answer LL and of the same linked list
    -   everytime smallest is pushed to top so we pop it and push into answer
    -   until minheap size becomes zero, then all the linked lists have been traversed and pushed into answer linked list
*/
template <typename T>
class Node
{
public:
    T data;
    Node *next;

    Node(T data)
    {
        next = NULL;
        this->data = data;
    }

    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
    }
};

class compare
{
public:
    bool operator()(Node<int> *a, Node<int> *b)
    {
        return a->data > b->data;
    }
};
/*
    TC = klogk + O(n*k log k) ==> Nlog N
    SC = O(k)
*/

// i/p : vector containing all heads of linked list
Node<int> *merge(vector<Node<int> *> &listArray)
{
    // greater used to compare <int> type minHeap, here we writecustom comparator to compare node* data and create minHeap
    priority_queue<Node<int> *, vector<Node<int> *>, compare> minHeap; // minHeap of type Node*
    int k = listArray.size();                                          // since k is not given
    if (k == 0)
        return NULL;
    // Push all k linked lists first element into LL
    for (int i = 0; i < k; i++)
    {
        if (listArray[i] != NULL)
        {
            minHeap.push(listArray[i]);
        }
    }
    // Head and tail of new merged linked list
    Node<int> *head = NULL;
    Node<int> *tail = NULL;

    while (minHeap.size() > 0)
    {
        Node<int> *top = minHeap.top(); // smallest element at top of minHeap
        minHeap.pop();                  // pop it
        if (top->next != NULL)          // if the linked list to whch this element belongs is not over yet
        {
            minHeap.push(top->next); // push next element into minHeap, it is already a node so no need to make a new one
        }
        // if its the first element
        if (head == NULL)
        {
            head = top;
            tail = top;
        }
        else // not first element
        {
            tail->next = top; // attach new element to tail
            tail = top;       // move tail forward
        }
    }
    return head; // after all the element, return the head of merged linked list
}

int main()
{

    return 0;
}