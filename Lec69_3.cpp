#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ====== BST: Implementation || Deletion ===========

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

Node *minVal(Node *root)
{
    Node *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

Node *maxVal(Node *root)
{
    Node *temp = root;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;
}

Node *deleteFromBST(Node *root, int val)
{
    if (root == NULL)//val not found in BST
    {
        return root;//return BST as it is
    }
    if (root->data == val) // when node found
    {
        // Node is leaf node, 0 child
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        // Node has only left child
        if (root->left != NULL && root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        // Node has only right child
        if (root->left == NULL && root->right != NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        // Node has both children
        if (root->left != NULL && root->right != NULL)
        {
            // Node can either be replaced by max in left subtree or min in right subtree (i.e. just smaller or greater value)

            int mini = minVal(root->right)->data;           // find min value in right subtree
            root->data = mini;                              // replace
            root->right = deleteFromBST(root->right, mini); // delete duplicate from right sub
            return root;

            // int maxi = maxVal(root->left)->data;//find max in left subtree
            // root->data = maxi;//replace
            // root->left = deleteFromBST(root->left, mini)//delete duplicate from left subtree
            // return root;
        }
    }
    if (root->data > val) // search in left
    {
        root->left = deleteFromBST(root->left, val);
        return root;
    }
    else // search in right
    {
        root->right = deleteFromBST(root->right, val);
        return root;
    }
}

int main()
{
    Node *root = NULL;
    cout << "Enter data: " << endl;
    // 100 50 110 25 70 120 60 115 -1
    takeInput(root);
    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);

    int val = 23;
    cout<<"Deleting "<<val<<" from BST"<<endl;
    root = deleteFromBST(root, val);
    //After deleting
    cout << "Level order traversal line by line:" << endl;
    levelOrderTraversal_line(root);

    return 0;
}