#include <iostream>
#include <queue>
using namespace std;
//========= Kth Ancestor of a node in a tree ===========
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
        if (leftData != -100)
        {
            temp->left = new node(leftData);
            q.push(temp->left);
        }
        // take and attach right node
        // cout << "Enter the right node for " << temp->data << ":"<<endl;
        int rightData;
        cin >> rightData;
        if (rightData != -100)
        {
            temp->right = new node(rightData);
            q.push(temp->right);
        }
    }
}

// Appraoch 1: trace path from root to node x and store in vector
// for kth ancestor, traverse vector from end towards start and count k

// Appraoch 2: Find the node and return in backward, all while keeping count of ancestor
// when returning decrement k upto 0
node *kthAncestor(node *root, int &k, int x)
{
    if (root == NULL)
    {
        // node x not found
        return NULL;
    }
    if (root->data == x)
    {
        // node found
        cout<<"Node found"<<endl;
        return root;
    }
    // else go left and right
    node *leftAns = kthAncestor(root->left, k, x);
    node *rightAns = kthAncestor(root->right, k, x);

    if (leftAns != NULL && rightAns == NULL) // x found in left substree
    {
        k--;
        if (k <= 0) // when k == 0, this is the kth ancestor
        {
            k = INT_MAX; // set MAX so that on further decrement, k can never become 0 again, so it keeps returning leftAns, otherwise it will become equal to 'root' of that recusrive call stack
            cout<<"This is the ancestor "<<root->data<<endl;
            return root;
        }
        // else this is not the ancestor returning node by node
        cout<<"Returning left "<<leftAns->data<<endl;
        return leftAns;
    }
    // or when node found in
    if (leftAns == NULL && rightAns != NULL) // x found in right subtree
    {
        k--;
        if (k <= 0) // when k == 0, this is the kth ancestor
        {
            k = INT_MAX; // set MAX so that on further decrement, k can never become 0 again, so it keeps returning rightAns, otherwise it will become equal to 'root' of that recusrive call stack
            cout<<"This is the ancestor "<<root->data<<endl;
            return root;
        }
        // else this is not the ancestor returning node by node
        cout<<"Returning left "<<rightAns->data<<endl;
        return rightAns;
    }
    // when node in neither left or right
    cout<<"This is the ancestor NULL"<<endl;
    return NULL;
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // i/p: 10 12 5 3 8 9 4 1 7 -100 -100 -100 -100 -100 -100 -100 -100 -100 -100
    /*
    2 4
10 12 5 3 8 9 4 1 7
            1
           / \
          2   3
        / \
       4  5
    k = 2, x = 2
    o/p: 1
        */
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    int k = 2;
    int x = 4;
    node *ans = kthAncestor(root, k, x);
    if (ans == NULL || ans->data == x) // if kth ancestor of x is node itself
    // so cant go further up
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << "Ancestor of " << x << " is " << ans->data << endl;
    }

    return 0;
}