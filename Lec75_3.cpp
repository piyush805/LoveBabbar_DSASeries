#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        this->data = val;
        this->right = NULL;
        this->left = NULL;
    }
};
//================== Is given Binary tree a heap? =========================
/*
In BST we did isBST for a binary tree by recusrion on left and right until NULL and then returning true false and node value to check make sure every node subtree is a BST, returning the same info pair above for further check

We do similar check for Is Heap: maxHeap
    -   Complete Binary Tree
    -   Root > left and right

Check CBT and maxOrder
-   if any indexing greater than node count then missing nodes hence not CBT
-       Need to find count of nodes first

Check maxOrder
-   leaf node -> true
-   left child only , check that node data greater this left child -> true;
-       Cannot  have only right child, because then it would not be CBT
        Only left child means, traversal in 2nd last level
-   Both left and right child present
        root > right data and root > left data -> true;

TC = O(n) + O(n) + O(n) ... 
Same for space: Pq
 
*/
void buildFromLevelOrder(Node *&root)
{
    queue<Node *> q;
    cout << "Enter root data: " << endl;
    int data;
    cin >> data;
    root = new Node(data);
    q.push(root);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        // Take and attach left node
        // cout << "Enter the left node for " << temp->data << ":" << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1)
        {
            temp->left = new Node(leftData);
            q.push(temp->left);
        }
        // take and attach right node
        // cout << "Enter the right node for " << temp->data << ":"<<endl;
        int rightData;
        cin >> rightData;
        if (rightData != -1)
        {
            temp->right = new Node(rightData);
            q.push(temp->right);
        }
    }
}

// Function to check that BT is maxHeap after being complete binary tree
/*
    - leaf nodes are maxHeap
    - single left child data be smaller than node
    - if two child, both be smaller than node
*/
bool isMaxOrder(Node *root)
{
    if (root->left == NULL && root->right == NULL) // single node
        return true;
    if (root->right == NULL) // single child case
    {
        return (root->data > root->left->data);
    }
    else // both children
    {
        bool left = isMaxOrder(root->left);
        bool right = isMaxOrder(root->right);
        return (left && right &&
                (root->data > root->left->data) &&
                (root->data > root->right->data));
    }
}

// Function to check is BT is complete or not
bool isCBT(Node *root, int index, int count)
{
    if (root == NULL)
    {
        return true;
    }

    if (index >= count) // index of element > number of nodes => missing nodes before this element
    {
        return false;
    }
    else
    {
        bool left = isCBT(root->left, 2 * index + 1, count); // 0 based indexing in Binary Tree
        bool right = isCBT(root->right, 2 * index + 2, count);

        return left && right; // true CBT until this node if both left and right are CBT
        // return from leaf towards root
    }
}
// Function to count number of nodes in the BT
int countNodes(Node *root)
{
    if (root == NULL)
        return 0;

    // count up from the NULL
    int ans = 1 + countNodes(root->left) + countNodes(root->right);
    return ans;
}

bool isHeap(Node *root)
{
    int index = 0;
    int totalCount = countNodes(root);
    // Binary Tree be complete and be Max Heap for it to be Heap
    if (isCBT(root, index, totalCount) && isMaxOrder(root))
    {
        return true;
    }
    return false;
}

int main()
{
    Node *root = NULL;
    buildFromLevelOrder(root);
    // 54 52 53 51 50 -1 -1 -1 -1 -1 -1
    // 54 53 52 51 50 -1 -1 -1 -1 -1 -1
    // 54 52 53 -1 51 50 -1 -1 -1 -1 -1
    // 54 65 53 -1 50 51 -1 -1 -1 -1 -1
    /*
            54        isHeap = 1
           /  \
         52   53
       /  \
      51  50

             54       isHeap = 1
           /  \
         53   52
       /  \
      51  50

            54         isHeap = 0
           /  \
         52   53
             /  \
            51  50

            54         isHeap = 0
           /  \
         65   53
        /  \
      51  50

    */
    cout << "is Heap? " << isHeap(root) << endl;
    return 0;
}