#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ========= Normal BST to a balanced BST ============
// Balanced: height of 2 subtrees of every noe differs by no more than 1
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

// Level order traversal of a given binary tree
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

// Create a normal binary tree out of given values
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

// inorder of a given binary tree
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
// Creates a BST out of a given inorder
Node *inorderToBST(int s, int e, vector<int> &in)
{
    if (s > e)
    {
        return NULL;
    }
    int mid = (s + e) / 2;          // find mid
    Node *root = new Node(in[mid]); // new node
    // since inorder already sorted so no need to check greater smaller, we know that left part will have all smaller and right part will have all greater elements
    root->left = inorderToBST(s, mid - 1, in);  // attach on left, left part
    root->right = inorderToBST(mid + 1, e, in); // attach on right, right part
    return root;
}
// Function to get inoder and pass inorder to creating BST
Node *balancedBST(Node *root)
{
    // Find in order
    vector<int> inorder_val;
    inorder(root, inorder_val);

    return inorderToBST(0, inorder_val.size() - 1, inorder_val); // pass it to BST making
}

int main()
{
    Node *root = NULL;
    cout << "Enter data: " << endl;
    // 50 30 60 20 40 -100 70 -100 -100 -100 -100 -100 80 -100 -100
    /*
    i/p->       50
               /  \
             30   60
            /  \    \
           20  40   70
                     \
                     80
    inorder: 20 30 40 50 60 70 80
    i/p->       50
              /   \
             30    70
            / \   / \
           20 40 60  80
    inorder: 20 30 40 50 60 70 80

    */
    buildFromLevelOrder(root);
    cout << "Given level order of binary tree:" << endl;
    levelOrderTraversal_line(root);

    root = balancedBST(root);
    /*
        get the inorder of given BT
        Create BST out of given inorder: creating node left and write

    */
    cout << "Balanced BST:" << endl;
    levelOrderTraversal_line(root);

    return 0;
}