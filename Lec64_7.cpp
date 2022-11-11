#include <iostream>
#include <map>
#include <queue>
using namespace std;
//================ Right View of Binary Tree ==================
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

vector<int> rightView(node *root)
{
    // Level order traversal with first node at each level stored wrt level
    queue<pair<node *, int>> q;
    vector<int> ans;
    map<int, int> rightNodeMap; //[lvl]->[leftNode data]
    q.push(make_pair(root, 0));
    while (!q.empty())
    {
        pair<node *, int> temp = q.front();
        // For each node in a level, push its left and right node in that order
        // So each level ill be printed from left to right
        node *rightNode = temp.first;
        int lvl = temp.second;
        // if entry for this leve does not exist then make entry moving from left to right in each level

        rightNodeMap[lvl] = rightNode->data; // entry only once, only left node stored for each level

        q.pop();

        if (rightNode->left != NULL)
        {
            q.push(make_pair(rightNode->left, lvl + 1));
        }
        if (rightNode->right != NULL)
        {
            q.push(make_pair(rightNode->right, lvl + 1));
        }
    }
    for (auto i : rightNodeMap)  // for each [hd]->[nodedata]
        ans.push_back(i.second); // push in [leftNode data]

    return ans;
}

void rightView_2(node *root, vector<int> &ans, int level)
{
    if (root == NULL)
        return;
    // ans size = lvl + 1
    //so on moving to right node first, level increased and becomes equal ans.size , so right node data pushed, and no other entry made for tht level
    if (level == ans.size()) 
        ans.push_back(root->data);
    //traverse right node first->if new level then make entry
    rightView_2(root->right, ans, level + 1);
    rightView_2(root->left, ans, level + 1);
}
int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // i/p: 1 2 3 4 5 6 7 -1 -1 -1 -1 -1 8 -1 9 -1 -1 -1 -1
    /*
            1           <--
           / \
          2   3         <--
        / \  / \
       4   56   7       <--
            \    \
             8    9     <--
    */
    // o/p: 1 3 7 9
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "Right view top to bottom: ";
    vector<int> ans;
    rightView_2(root, ans, 0);
    // vector<int> right = rightView(root);
    // for (int i = 0; i < right.size(); i++)
    // {
    //     cout << right[i] << " ";
    // }
    // cout << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}