#include <iostream>
#include <queue>
using namespace std;
//================ Check if Tree is a balanced tree ======================
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

pair<bool, int> isSum(node *root)
{
    if (root == NULL)
    {
        // left, right og balanced at leaf
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }

    if (root->left == NULL && root->right == NULL)
    {
        //data at leaf node
        pair<bool, int> p = make_pair(true, root->data);
        return p;
    }
    pair<int, int> leftAns = isSum(root->left);
    pair<int, int> rightAns = isSum(root->right);
    
    bool left = leftAns.first;//whether left subtree is sum tree
    bool right = rightAns.first;//whether right subtree is sum tree
    //is it sum tree upto this node
    bool condition = root->data == leftAns.second + rightAns.second;

    pair<bool, int> ans;

    if (left && right && condition)
    {
        ans.first = true; 
        ans.second =root->data + left.second + right.second;
    }
    else
    {
        ans.first = false;
    }
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
    // Balanced: 1 3 5 7 11 17 -1 -1 -1 -1 -1 -1 -1
    // Un Balanced: 1 2 -1 3 4 6 5 -1 -1 -1 -1 -1 -1
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "Is balanced: " << isBalanced_2(root).first << endl;

    return 0;
}