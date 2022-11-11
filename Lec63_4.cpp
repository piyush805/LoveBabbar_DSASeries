#include <iostream>
#include <queue>
using namespace std;
//================ Check if trees identical ======================
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

bool isIdentical(node *r1, node *r2)
{
    if (r1 == NULL && r2 == NULL) // both NULL
    {
        return true;
    }
    // one NULL, other is not
    if ((r1 != NULL && r2 == NULL) || (r1 == NULL && r2 != NULL))
    {
        return false;
    }

    bool left = isIdentical(r1->left, r2->left);    // left subtree identical at this node
    bool right = isIdentical(r1->right, r2->right); // right subtree---
    bool value = r1->data == r2->data;              // node value

    if (left && right && value)
    {
        return true; // all 3, then idenitcal upto this node
    }
    return false;
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

void buildFromLevelOrder(node *&root)
{
    queue<node *> q;
    // cout << "Enter root data:" << endl;
    int data;
    cin >> data;
    root = new node(data);
    q.push(root);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        // Take and attack left node
        // cout << "Enter the left node for " << temp->data << ":" << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1)
        {
            temp->left = new node(leftData);
            q.push(temp->left);
        }
        // take and attack right node
        // cout << "Enter the left node for: " << temp->data << endl;
        int rightData;
        cin >> rightData;
        if (rightData != -1)
        {
            temp->right = new node(rightData);
            q.push(temp->left);
        }
    }
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // Balanced: 1 3 5 7 11 17 -1 -1 -1 -1 -1 -1 -1
    // Un Balanced: 1 2 -1 3 4 6 5 -1 -1 -1 -1 -1 -1
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "Is balanced: " << isBalanced_2(root).first << endl;

    return 0;
}