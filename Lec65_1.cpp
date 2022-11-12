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

// Bloodline: sum of nodes on longest path from root to leaf node
void longestBloodLine(node *root, int sum, int &maxSum, int len, int &maxLen)
{
    if (root == NULL) // reached below leaf node in a path
    {
        if (len > maxLen) // update maxLen and maxSum
        {
            maxLen = len;
            maxSum = sum;
        }
        else if (maxLen == len) // if two path of equal lengths then update maxSum as greater or smaller of the two
        {
            maxSum = max(sum, maxSum);
        }
        return;
    }
    sum = sum + root->data; // add this node

    // go to left and right for each node until lead node encountered, len increase by 1
    longestBloodLine(root->left, sum, maxSum, len + 1, maxLen);
    longestBloodLine(root->right, sum, maxSum, len + 1, maxLen);
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
    // o/p: 1 + 3 + 7 + 9 = 20
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;
    
    int len =0;
    int maxLen = 0;
    int sum =0;
    int maxSum = INT_MIN;
    longestBloodLine(root, sum, maxSum, len, maxLen);
    cout<<"max len: "<<maxLen<<" max Sum: "<<maxSum<<endl;
    // return maxSum

    return 0;
}