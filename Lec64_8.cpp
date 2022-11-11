#include <iostream>
#include <map>
#include <queue>
using namespace std;
//============= Diagonal Traversal of a Binary tree ===============
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

// Diagonal view: from top right to bottom left: /
// Just vertical order traversal, on going left [hd] value be kept same
vector<int> diagonalTraversal(node *root)
{
    // Map: [hd]-->[[lvl]-->[nodes]]
    map<int, map<int, vector<int>>> nodes;
    // Queue: <Node*, <hd, lvl> >
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
            // on going left, left node until end to be saved at same [hd] in map
            q.push(make_pair(frontNode->left, make_pair(hd, lvl + 1)));
        }

        if (frontNode->right)
        {
            // going right, all nodes to be saved at new [hd] level in map
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
    // o/p: 1 2 4 | 3 5 6 | 7 8 | 9
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    cout << "Diagnoal Traversal: ";
    vector<int> diagonal = diagonalTraversal(root);
    for (int i = 0; i < diagonal.size(); i++)
    {
        cout << diagonal[i] << " ";
    }
    cout << endl;

    return 0;
}