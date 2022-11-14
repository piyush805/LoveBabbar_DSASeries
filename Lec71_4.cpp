#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ============ Pre order to BST ==============

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

/*
Approach 1: traverse vector and check for each node where to insert -> O(n^2)
    - Not making use of fact that it is preorder, we're simply processing it as random numbers
*/

/*
Approach 2: In Binary tree, we created tree out of preorder and inorder
    - here we can obtain inorder by sorting preorder
    - we know how to create tree now
    - O(n log n)
*/

/*
Approach 3: Preorder N L R
    1. start from range INT_MIN to INT_MAX
    2. with each node- > insert a node, now left can have range [INT_MIN, node->data], and right has range from [node->data, INT_MAX], check and insert next node
    3.   Repeat
*/

Node *createBST(vector<int> &preorder, int mini, int maxi, int &i)
{
    if (i >= preorder.size())
    {
        return NULL;
    }
    if (preorder[i] < mini || preorder[i] > maxi)
    {
        // no. out of range for potential node value
        return NULL;
    }
    Node *root = new Node(preorder[i]); // N
    i++;                                // next num

    root->left = createBST(preorder, mini, root->data, i);  // L
    root->right = createBST(preorder, root->data, maxi, i); // R

    return root;
}

Node *preorderToBST(vector<int> &preorder)
{
    int mini = INT_MIN;
    int maxi = INT_MAX;
    int i = 0; // 0th is the chief root of BST
    return createBST(preorder, mini, maxi, i);
}

int main()
{
    Node *root = NULL;
    // cout << "Enter data: " << endl;
    // // 10 6 12 2 8 11 15 -1 -1 -1 -1 -1 -1 -1 -1
    // takeInput(root);
    // cout << "Level order traversal line by line:" << endl;
    // levelOrderTraversal_line(root);
    vector<int> preorder{20, 10, 5, 15, 13, 35, 30, 42};
    /*
                20
               /  \
             10   35
            / \   / \
           5  15 30  42
             /
            13
    level order traversal:
    20
    10 35
    5 15 30 42
    13

    */
    root = preorderToBST(preorder);

    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);
    return 0;
}