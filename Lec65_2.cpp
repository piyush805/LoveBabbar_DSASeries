#include <iostream>
#include <map>
#include <queue>
using namespace std;
//========= Lowest Common Ancestor of 2 given nodes in a Binary tree ===========
class node
{
public:
    int data;
    node *left;
    node *right;
    node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

void levelOrderTraversal_line(node *root)
{
    queue<node *> q;
    q.push(root);
    q.push(NULL); // 1st level completed at root itself
    while (!q.empty())
    {
        node *temp = q.front();
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

void buildFromLevelOrder(node *&root)
{
    queue<node *> q;
    cout << "Enter root data: " << endl;
    int data;
    cin >> data;
    root = new node(data);
    q.push(root);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        // Take and attach left node
        // cout << "Enter the left node for " << temp->data << ":" << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1)
        {
            temp->left = new node(leftData);
            q.push(temp->left);
        }
        // take and attach right node
        // cout << "Enter the right node for " << temp->data << ":"<<endl;
        int rightData;
        cin >> rightData;
        if (rightData != -1)
        {
            temp->right = new node(rightData);
            q.push(temp->right);
        }
    }
}

// Appraoch 1: Find path upto n1 and n2, go back from the end which one is the first common element
// requires 2 times traversal and 2 times storing data

// Appraoch 2: Recursion
node *LCA(node *root, int n1, int n2)
{
    if (root == NULL)
    {
        // cout << "NULL" << endl;
        return NULL;
    }

    // start from root and check left-right until one of the node data is found
    if (root->data == n1 || root->data == n2)
    {
        // cout << "Found eqv" << endl;
        return root;
    }
    if (root->left)
    {
        // cout << "Going left into " << root->left->data << endl;
    }

    node *leftAns = LCA(root->left, n1, n2);
    if (root->right)
    {
        // cout << "Going right into " << root->right->data << endl;
    }
    node *rightAns = LCA(root->right, n1, n2);

    // We have both leftAns and rightAns present even if one has been found earlier, later found one reamins null
    // so we have to check contd for both
    if (leftAns != NULL && rightAns != NULL) // if both branches have non null
    {
        // cout << "'Both found in same call" << endl;
        return root;
    }
    else if (rightAns != NULL) // return !NULL answer
    {
        // cout << "Found right: " << rightAns->data << endl;
        return rightAns;
    }
    else if (leftAns != NULL) // return !NULL answer
    {
        // cout << "Found left " << leftAns->data << endl;
        return leftAns;
    }
    // cout << "Return both null" << endl;
    return NULL; // both null, no common
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // i/p: 1 2 3 6 -1 4 5 -1 8 -1 -1 21 -1 -1 -1 -1 -1
    /*
            1
           / \
          2   3
        /    / \
       6   4    5
        \      /
         8    21
    */
    // o/p: LCA 4, 21 ->3
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    int n1 = 2;
    int n2 = 21;
    cout << "LCA for: " << n1 << " " << n2 << " is: ";
    node *lca = LCA(root, n1, n2);
    cout << lca->data << endl;
    return 0;
}