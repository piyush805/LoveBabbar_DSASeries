#include <iostream>
#include <queue>
using namespace std;
//===================== Height of Tree ===========================
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

// Function to calculate height/depth of tree
int heightOfTree(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left = heightOfTree(root->left);
    int right = heightOfTree(root->right);
    int ans = max(left, right) + 1;
    return ans;
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
            q.push(temp->right);
        }
    }
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "Height: " << heightOfTree(root) << endl;

    return 0;
}