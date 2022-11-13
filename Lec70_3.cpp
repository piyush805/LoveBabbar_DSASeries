#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ====== Kth smallest element in BST===========

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

int kthLargestElement(Node *root, int &i, int k, int n)
{
    if (root == NULL)
    {

        return -1;
    }
    int right = kthLargestElement(root->left, i, k, n);
    if (right != -1)
    {
        return right;
    }
    i++;
    if (i == n - k + 1)
    {
        return root->data;
    }
    return kthLargestElement(root->right, i, k, n);
}

int main()
{
    Node *root = NULL;
    cout << "Enter data: " << endl;
    // 100 50 110 25 70 120 60 115 -1
    takeInput(root);
    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);

    int i = 0;
    cout << kthLargestElement(root, i, 3, 8) << endl;
    return 0;
}