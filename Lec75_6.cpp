#include <iostream>
#include <queue>
using namespace std;

//===================== Convert BST to minHeap ============================
/*
    contitions that:
        1: Is should be min heap : N < L, R
        2: for all N, L < R
    combining these contd become: N < L < R -> preorder like
    But the one giving NLR in such sorted order is inorder

    So we find inorder of given BST, it is already complete

    And traverse BST, fill N, and make recursive call for L then R, because first L value to be filled with smaller sorted inorder value than R

*/

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

void levelOrderTraversal_line(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(NULL); // 1st level completed at root itself
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        // temp = root, pop root, push root->left, root right
        // temp = NULL, pop NULL, push null,(prvious level over)
        // temp = root->left, pop root->left, push its left and right
        // temp = root->right, pop root->right push its left and right
        // temp = NULL, pop NULL, push NULL(previous level over)
        // continues...

        if (temp == NULL) //
        {
            cout << endl;
            if (!q.empty()) // if there are still elements then these are that of next level->so now push a separator again
            {
                q.push(NULL);
            }
        }
        else
        {
            // print data and push its left and right
            cout << temp->data << " ";
            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}

// Recursive function to seach where to insert the new element then insert it at that leaf;
Node *insertIntoBST(Node *root, int d)
{
    if (root == NULL)
    {
        root = new Node(d);
        return root;
    }
    if (d > root->data)
    {
        root->right = insertIntoBST(root->right, d);
    }
    else
    {
        root->left = insertIntoBST(root->left, d);
    }
    return root;
}

// Function to keep taking node inputs for BST and call funciton to insert node
void takeInput(Node *&root)
{
    int data;
    cin >> data;
    while (data != -1)
    {
        root = insertIntoBST(root, data);
        cin >> data;
    }
}

// Funciton to find inorder of given BST
void inorder(Node *root, vector<int> &in)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}

void fillPreOrder(Node *root, vector<int> &in, int &index)
{
    if (root == NULL)
        return;
    // N < L < R
    root->data = in[index++]; // Fill N

    fillPreOrder(root->left, in, index);  // Call for L
    fillPreOrder(root->right, in, index); // Call for R
}

int main()
{
    Node *root = NULL;
    cout << "Enter data: " << endl;
    // 4 2 6 1 3 5 7 -1 -1 -1 -1 -1 -1 -1 -1
    /*
    i/p->    4
           /  \
          2    6
        / \   / \
       1  3  5   7

    o/p->    1
           /  \
          2    5
        / \   / \
       3  4  6   7

    */
    takeInput(root);
    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);

    vector<int> in;
    inorder(root, in);
    int i = 0;
    fillPreOrder(root, in, i);
    // Heapified BST
    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);

    return 0;
}