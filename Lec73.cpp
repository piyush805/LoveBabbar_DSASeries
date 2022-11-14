#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ============== Nodes in Largest BST in a given Binary Tree ==================
/*
Approach 1:
    1.  At every node from bottom, check if it is valid BST and store size
    2. track max size
    3. Return max size on tree exhausted


Approach 2:
    1. Donot revisit balanced ones, just track if left and right are balanced, by keeping track of bool balanced at each node
    Contd for BST:
        - Left subtree valid BST
        - Right subtree valid BST
        - root->left->data < root->data < root->right->data
    In valid BST question we did use pair to return from every node on recursion

    On every node-  int max
                    int min
                    bool isBST
                    size[left size + right size + 1]
*/
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

class info
{
public:
    int maxi;
    int mini;
    bool isBST;
    int size;
};
//Function to print data members of this info object
void printObj(info c)
{
    cout << "{" << c.maxi << ", " << c.mini << ", " << c.isBST << ", " << c.size << "}" << endl;
}

//Function to find largest bst nodes
info solve(Node *root, int &ans)
{
    if (root == NULL)
    {
        return {INT_MIN, INT_MAX, 1, 0};
    }
    info left = solve(root->left, ans);
    info right = solve(root->right, ans);
    // cout << "Left: ";
    // printObj(left);
    // cout << "Right: ";
    // printObj(right);

    info currNode;//on retuning from NULL nodes, size = 0 + 0 + 1
    currNode.size = left.size + right.size + 1; 
    currNode.maxi = max(root->data, right.maxi); //right maxi set to INT_MIN 
    currNode.mini = min(root->data, left.mini); //left mini set to INT_MAX 
    
    //contd for being a BST
    if (left.isBST && right.isBST &&
        root->data > left.maxi &&
        root->data < right.mini)
    {
        currNode.isBST = true;
    }
    else
    {
        currNode.isBST = false;
    }

    if (currNode.isBST)//If this is bst at current node then count no of nodes at this point, and take greater of this or earlier greater bst as ans
    {
        ans = max(ans, currNode.size);
    }
    // cout << "Curr Node at " << root->data << endl;
    // printObj(currNode);
    // cout << "ans: " << ans << endl;
    // cout << endl;
    
    return currNode;//return info at this currNode next upper node's left or right to proces further
}

// Level order traversal of a given binary tree
void levelOrderTraversal_line(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(NULL); // 1st level completed at root itself
    while (!q.empty())
    {
        Node *temp = q.front();
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

// Create a normal binary tree out of given values
void buildFromLevelOrder(Node *&root)
{
    queue<Node *> q;
    cout << "Enter root data: " << endl;
    int data;
    cin >> data;
    root = new Node(data);
    q.push(root);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        // Take and attach left node
        // cout << "Enter the left node for " << temp->data << ":" << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -100)
        {
            temp->left = new Node(leftData);
            q.push(temp->left);
        }
        // take and attach right node
        // cout << "Enter the right node for " << temp->data << ":"<<endl;
        int rightData;
        cin >> rightData;
        if (rightData != -100)
        {
            temp->right = new Node(rightData);
            q.push(temp->right);
        }
    }
}

// inorder of a given binary tree

int main()
{
    Node *root = NULL;
    cout << "Enter data: " << endl;
    // 1 2 3 4 -100 5 6 -100 7 -100 -100 -100 -100 -100 -100
    /*
    i/p->        1
               /  \
              2    3
            /    /  \
           4    5    6
            \
             7
    o/p-> largest bst of 2 nodes
        4      and 5 and 6
         \
          7

    */
    buildFromLevelOrder(root);
    cout << "Given level order of binary tree:" << endl;
    levelOrderTraversal_line(root);
    int ans = 0;
    solve(root, ans);
    cout << "Largest BST in given BT contains: " << ans << " nodes" << endl;

    return 0;
}