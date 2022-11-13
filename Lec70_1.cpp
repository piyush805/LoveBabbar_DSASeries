#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ====== Validate a Binary Tree as BST ===========

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
        if (leftData != -100)
        {
            temp->left = new Node(leftData);
            q.push(temp->left);
        }
        // take and attach right node
        // cout << "Enter the right node for " << temp->data << ":"<<endl;
        int rightData;
        cin >> rightData;
        if (rightData != -100)
        {
            temp->right = new Node(rightData);
            q.push(temp->right);
        }
    }
}
// Appraoch 1: BST in order trversal is sorted
// so find inorder of given tree and check if sorted

// Approach 2: BST every node, left be smaller and right be greater
// i.e. there is bound on value: left = [... root value] & right = [root value ....]
bool isBST(Node *root, int min, int max)
{
    if (root == NULL) // reached end wihout returning false in between
    {
        return 1;
    }
    if (root->data > min && root->data < max)
    {
        bool left = isBST(root->left, min, root->data);
        bool right = isBST(root->right, root->data, max);
        return left & right;
    }
    return 0;
}

int main()
{
    Node *root = NULL;
    cout << "Enter data: " << endl;
    // i/p: 100 50 110 25 70 -100 120 -100 -100 60 -100 115 -100 -100 -100 -100 -100
    // o/p: 1
    // i/p: 10 12 5 3 8 9 4 1 7 -100 -100 -100 -100 -100 -100 -100 -100 -100 -100
    // o/p : 0
    buildFromLevelOrder(root);
    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);

    cout << "Given tree is a BST? " << isBST(root, INT_MIN, INT_MAX) << endl;
    return 0;
}