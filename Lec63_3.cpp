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

bool isBalanced_1(node *root)
{
    if (root == NULL)
    {
        return true;
    }
    bool left = isBalanced_1(root->left);   // if left subtree balanced at root
    bool right = isBalanced_1(root->right); // if right subtree balance at this root
    // if diff betwee height of both is <=1 then there is balance at this root
    bool diff = abs(heightOfTree(root->left) - heightOfTree(root->right)) <= 1;

    if (left && right && diff)
    {
        return true;
    }
    return false;
}

pair<bool, int> isBalanced_2(node *root)
{
    if (root == NULL)
    {
        //balanced at leaf
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }
    pair<int, int> left = isBalanced_2(root->left);
    pair<int, int> right = isBalanced_2(root->right);
    //3 values reqd: whether left balanced, right balanced, and height difference
    bool leftAns = left.first;
    bool rightAns = right.first;

    //check height diff at this node
    bool diff = abs(left.second - right.second) <= 1;

    pair<bool, int> ans;

    ans.second = max(left.second, right.second) + 1;
    if (leftAns && rightAns && diff)
    {
        ans.first = true; // balanced at this node can be determined after diff is known
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