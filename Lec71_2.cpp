#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ====== BST to a sorted linked list ===========

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

// Appraoch 2:find inorder->sorted and convert array element to linked list
Node *BSTsortedList(Node *root)
{
    vector<int> inorder_val;
    inorder(root, inorder_val); // find inorder, it will be sorted order
    int n = inorder_val.size();
    Node *newRoot = new Node(inorder_val[0]);
    Node *curr = newRoot;

    for (int i = 1; i < n; i++)
    {
        Node *temp = new Node(inorder_val[i]);
        curr->left = NULL;
        curr->right = temp;
        curr = temp;
    }
    curr->left = NULL;
    curr->right = NULL;
    return newRoot;
}

void print(Node *&head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << "-> ";
        temp = temp->right;
    }
    cout << "X";
    cout << endl;
}

int main()
{
    Node *root = NULL;
    cout << "Enter data: " << endl;
    // 10 6 12 2 8 11 15 -1 -1 -1 -1 -1 -1 -1 -1
    takeInput(root);
    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);

    root = BSTsortedList(root);
    print(root);
    return 0;
}