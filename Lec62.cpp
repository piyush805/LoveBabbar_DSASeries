#include <iostream>
#include <queue>
using namespace std;

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

node *buildTree(node *root)
{
    cout << "Enter the data: " << endl;
    int data;
    cin >> data;
    root = new node(data);
    if (data == -1)
    {
        return NULL;
    }
    cout << "Enter data for inserting on left: " << endl;
    root->left = buildTree(root->left);

    cout << "Enter data for inserting on right: " << endl;
    root->right = buildTree(root->right);

    return root;
}

void levelOrderTraversal(node *root)
{
    queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *temp = q.front();
        // For each node in a level, push its left and right node in that order
        // So each level ill be printed from left to right
        cout << temp->data << " ";
        q.pop();
        if (temp->left != NULL)
        {
            q.push(temp->left);
        }
        if (temp->right != NULL)
        {
            q.push(temp->right);
        }
    }
}

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
// L N R
void inOrder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}
// L R N
void postOrder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}
// N L R
void preOrder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void buildFromLevelOrder(node *&root)
{
    queue<node *> q;
    cout << "Enter root data:" << endl;
    int data;
    cin >> data;
    root = new node(data);
    q.push(root);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        // Take and attack left node
        cout << "Enter the left node for " << temp->data << ":" << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1)
        {
            temp->left = new node(leftData);
            q.push(temp->left);
        }
        // take and attack right node
        cout << "Enter the left node for: " << temp->data << endl;
        int rightData;
        cin >> rightData;
        if (rightData != -1)
        {
            temp->right = new node(rightData);
            q.push(temp->right);
        }
    }
}

void countLeafNodes(node *root, int &count)
{
    if (root == NULL)
    {
        return;
    }
    countLeafNodes(root->left,count);
    if (root->left == NULL && root->right == NULL)
    {
        count++;
    }
    countLeafNodes(root->right,count);
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    int count = 0;
    countLeafNodes(root, count);
    cout << "No of leaf nodes: " << count << endl;
    cout << "Preorder: ";
    preOrder(root);
    cout << endl;

    cout << "In order: ";
    inOrder(root);
    cout << endl;

    cout << "Post order: ";
    postOrder(root);
    cout << endl;

    return 0;
}