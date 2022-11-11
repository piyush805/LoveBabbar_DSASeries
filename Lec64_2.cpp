#include <iostream>
#include <queue>
using namespace std;
//================ Boundry Trversal of binary tree ==================
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

void traverseLeft(node *root, vector<int> &ans)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return; // no NULL and no leaf node included

    ans.push_back(root->data);//Include this left nodes on left boundry
    if (root->left)
        traverseLeft(root->left, ans); 
    else
        traverseLeft(root->right, ans);//if left over then traverse left in the right subtree
}
///Traverse leaf nodes and include them only in answer
void traverseLeaf(node *root, vector<int> &ans)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        ans.push_back(root->data); // include leaf nodes
        return;
    }
    // no left or right included
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
}


void traverseRight(node *root, vector<int> &ans)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return;//no NULL or leaf node included

    if (root->right)
        traverseRight(root->right, ans);
    else
        traverseRight(root->left, ans);
    ans.push_back(root->data);// 
}


vector<int> boundryTraversal(node *root)
{
    vector<int> ans;
    if (root == NULL)
    {
        return ans;
    }
    ans.push_back(root->data);
    traverseLeft(root->left, ans);
    
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
    
    traverseRight(root->right, ans);
    return ans;
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

    cout << "Boundry traversal: ";
    vector<int> boundry = boundryTraversal(root);
    for (int i = 0; i < boundry.size(); i++)
    {
        cout << boundry[i] << " ";
    }
    cout << endl;

    return 0;
}