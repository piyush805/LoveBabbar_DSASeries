#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ========== Flatten a binary tree into linked list ===========

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

//Function to traverse and print nodeData of linked list
void print(Node *&head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->right;
    }
    cout << "X";
    cout << endl;
}

/*
    1st iteration: rightmost node of left subtree points to rightsubtree. and right of root point to left node. Thus root and its left become LL.
    2nd. 
        each time move to this newly formed node of LL on left(now right points to it), if none, go to next in right side
        and keep going towards its right until end, and 
        point that end to right subtree to curr node, and
        point curr right to its left, this now right pointer points to newly formed LL node
*/
void flatten(Node *root)
{
    Node *curr = root;
    while (curr != NULL)
    {
        if (curr->left)
        {
            Node *pred = curr->left;
            while (pred->right)
            {
                pred = pred->right;
            }
            // cout << "Pred null found at: " << pred->data << " points to " << curr->right->data << endl;
            pred->right = curr->right;
            // cout << "Curr points to : " << curr->left->data << endl;
            curr->right = curr->left; 
        }
        // move forward in new node of LL
        curr = curr->right;
        if (curr->right)
        {
            // cout << "new Current now: " << curr->data << endl;
        }
    }
    curr = root;
    while (curr != NULL)
    {
        curr->left = NULL;
        curr = curr->left;
    }
}

int main()
{
    Node *root = NULL;
    buildFromLevelOrder(root);
    // i/p: 1 2 3 4 5 -100 6 -100 -100 7 8 -100 9 -100 -100 -100 -100 -100 10 -100 -100
    /*
            1
          /  \
         2    3
       /  \    \
      4    5    6
         /  \    \
        7    8    9
                   \
                   10
    o/p: 1->2->4->5->7->8->3->6->9->10->X
    */
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    flatten(root);
    print(root);

    return 0;
}