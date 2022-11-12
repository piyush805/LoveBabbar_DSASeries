#include <iostream>
#include <map>
#include <queue>
using namespace std;
//========= No. of paths which have nodes summing upto value K ===========
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
        if (leftData != -100)
        {
            temp->left = new node(leftData);
            q.push(temp->left);
        }
        // take and attach right node
        // cout << "Enter the right node for " << temp->data << ":"<<endl;
        int rightData;
        cin >> rightData;
        if (rightData != -100)
        {
            temp->right = new node(rightData);
            q.push(temp->right);
        }
    }
}

// Appraoch 2: 
void sumK(node *root, int k, int &count, vector<int> path)
{
    if (root == NULL)//until leaf node
    {
        return;
    }
    path.push_back(root->data);//add this node to path
    sumK(root->left, k, count, path);
    sumK(root->right, k, count, path);
    int sum = 0;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        sum += path[i];
        if (sum == k)
        {
            count++;
        }
    }
    path.pop_back();
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // i/p: 1 3 -1 2 1 4 5 -100 -100 1 -100 1 2 -100 6 -100 -100 -100 -100 -100 -100 -100 -100 -100
    /*
            1
           / \
          3  -1
        / \  / \
       2  1 4   5
         / / \   \
        1 1  2    6
    k =5 
    o/p: 
        1 3 2
        1 3 1 1
        1 3 1
        1 -1 4 1
        1 -1 4 1
        1 -1 4 2
        1 -1 5
        1 -1 5
        Count: 8*/
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    vector<int> path;
    int count = 0;
    int k = 5;
    sumK(root, k, count, path);
    cout << "Count: " << count << endl;
    return 0;
}