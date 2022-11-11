#include <iostream>
#include <map>
#include <queue>
using namespace std;
//================ Left View of Binary Tree ==================
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

vector<int> leftView(node *root)
{
    // Level order traversal with first node at each level stored wrt level
    queue<pair<node *, int>> q;
    vector<int> ans;
    map<int, int> leftNodeMap; //[lvl]->[leftNode data]
    q.push(make_pair(root, 0));
    while (!q.empty())
    {
        pair<node *, int> temp = q.front();
        // For each node in a level, push its left and right node in that order
        // So each level ill be printed from left to right
        node *leftNode = temp.first;
        int lvl = temp.second;
        // if entry for this leve does not exist then make entry moving from left to right in each level
        if (leftNodeMap.find(lvl) == leftNodeMap.end())
        {
            leftNodeMap[lvl] = leftNode->data; // entry only once, only left node stored for each level
        }
        q.pop();

        if (leftNode->left != NULL)
        {
            q.push(make_pair(leftNode->left, lvl + 1));
        }
        if (leftNode->right != NULL)
        {
            q.push(make_pair(leftNode->right, lvl + 1));
        }
    }
    for (auto i : leftNodeMap)   // for each [hd]->[nodedata]
        ans.push_back(i.second); // push in [leftNode data]

    return ans;
}

void leftView_2(node *root, vector<int> &ans, int level)
{
    if (root == NULL)
        return;
    // ans size = lvl + 1
    // so on moving to left node first, level increased and becomes equal ans.size , so left node data pushed, and no other entry made for tht level
    if (level == ans.size()) // if new level entered  push first node into ans
        ans.push_back(root->data);
    // traverse left node first->if new level then  push node data
    leftView_2(root->left, ans, level + 1);
    leftView_2(root->right, ans, level + 1);
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // i/p: 1 2 3 4 5 6 7 -1 -1 -1 -1 -1 8 -1 9 -1 -1 -1 -1
    /*
            1
           / \
          2   3
        / \  / \
       4   56   7
            \    \
             8    9
    */
    // o/p: 1 2 4 8
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "Left view top to bottom: ";
    vector<int> ans;
    leftView_2(root, ans, 0);
    // vector<int> left = leftView(root);
    // for (int i = 0; i < left.size(); i++)
    // {
    //     cout << left[i] << " ";
    // }
    // cout << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}