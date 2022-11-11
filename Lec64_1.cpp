#include <iostream>
#include <queue>
using namespace std;
//================ Zig Zag traversal balanced tree ======================
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

vector<int> zigZagTraversal(node *root)
{
    vector<int> result;
    if (root == NULL)
    {
        return result;
    }
    queue<node*> q; // stores are nodes of a level in right order
    q.push(root);
    bool leftToRight = true; // toggle variable for checking left to right or right to left
    while (!q.empty())
    {
        int size = q.size();
        vector<int> ans(size); // stores in right order for each level

        for (int i = 0; i < size; i++) // for all nodes of this level
        {
            node *frontNode = q.front();
            q.pop();
            // where to insert from left end or right end
            int index = leftToRight ? i : size - i - 1;
            ans[index] = frontNode->data;
            // insert this node's left
            if (frontNode->left)
                q.push(frontNode->left);
            // insert this node's right
            if (frontNode->right)
                q.push(frontNode->right);
        }
        // Toggle variable
        leftToRight = !leftToRight;
        // push current ans values into result as it is
        for (auto i : ans)
        {
            result.push_back(i);
        }
    }
    return result;
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
    // Balanced: 1 3 5 7 11 17 -1 -1 -1 -1 -1 -1 -1
    // Un Balanced: 1 2 -1 3 4 6 5 -1 -1 -1 -1 -1 -1
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "ZigZagTraversal: ";
    vector<int> zigZag = zigZagTraversal(root);
    for (int i = 0; i < zigZag.size(); i++)
    {
        cout << zigZag[i] << " ";
    }
    cout << endl;

    return 0;
}