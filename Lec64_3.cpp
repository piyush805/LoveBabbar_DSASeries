#include <iostream>
#include <queue>
#include <map>
using namespace std;
//================ Vertical order traversal ==================
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

vector<int> verticalOrderTraversal(node *root)
{
    //[hd]-->[[lvl]-->[nodes]]
    map<int, map<int, vector<int>>> nodes;
    //[<Node*, <hd, lvl> >
    queue<pair<node *, pair<int, int>>> q;
    vector<int> ans;
    if (root == NULL)
        return ans;
    q.push(make_pair(root, make_pair(0, 0)));
    while (!q.empty())
    {
        pair<node *, pair<int, int>> temp = q.front();
        q.pop();
        // temp [node*]->
        node *frontNode = temp.first;
        int hd = temp.second.first;
        int lvl = temp.second.second;

        nodes[hd][lvl].push_back(frontNode->data);
        
        if (frontNode->left)
        {
            // hd - 1 and lvl + 1 on moving left substree
            q.push(make_pair(frontNode->left, make_pair(hd - 1, lvl + 1)));
        }

        if (frontNode->right)
        {
            // hd + 1 and lvl + 1 on moving right subtree
            q.push(make_pair(frontNode->right, make_pair(hd + 1, lvl + 1)));
        }
    }
    for (auto i : nodes) // for each map entry [hd-->[[lvl]->[nodes]]]
    {
        for (auto j : i.second) // for each vector<int> nodes in [[lvl]->[nodes]]
        {
            for (auto k : j.second) // for each node in vector<int> nodes
            {
                ans.push_back(k); // push node into answer
            }
        }
    }

    return ans;
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // Balanced: 1 2 3 4 5 6 7 -1 -1 -1 -1 -1 8 -1 9 -1 -1 -1 -1
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "Vertical order traversal: ";
    vector<int> boundry = verticalOrderTraversal(root);
    for (int i = 0; i < boundry.size(); i++)
    {
        cout << boundry[i] << " ";
    }
    cout << endl;

    return 0;
}