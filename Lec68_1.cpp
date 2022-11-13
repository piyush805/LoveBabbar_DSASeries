#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ====== Morris Traversal | Flatten a binary tree into linked list =======
/*
                    TC      SC
    Level order     O(n)    O(n)
    In order        O(n)    O(n)
    Pre order       O(n)    O(n)
    Post Order      O(n)    O(n)

    Morris          O(n)    O(1) <---
    because without using other DS. we make temporary links and erase them in next subsequent steps
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

// Preorder traversal without recursion and without stack
void morrisTraversalPreorder(Node *root)
{
    while (root)
    {
        // If left child is null, print the current node data. Move to
        // right child.
        if (root->left == NULL)
        {
            // cout << "Left null found" << endl;
            cout << root->data << " ";
            root = root->right;
            // cout << "Now root is: " << root->data << endl;
        }
        else
        {
            // cout << root->left->data << " Left non null, finding predecessor" << endl;
            // Find inorder predecessor
            Node *current = root->left;
            while (current->right && current->right != root)
            {
                // cout << "Current: " << current->right->data << endl;
                current = current->right;
            }

            // If the right child of inorder predecessor already points to
            // this node
            if (current->right == root)
            {
                // cout <<"Temp link exists from "<<current->data<<" to "<<root->data << endl;
                current->right = NULL;
                // cout<<"Removed link"<<endl;
                root = root->right;
                // cout << "Now root is: " << root->data << endl;
            }

            // If right child doesn't point to this node, then print this
            // node and make right child point to this node
            else
            {
                // cout << "current->right got NULL " << endl;
                cout << root->data << " ";
                // cout << current->data << " --->" << root->data << endl;
                current->right = root;

                root = root->left;
                // cout << "Now root is: " << root->data << endl;
            }
        }
    }
    cout << endl;
}

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
            pred->right = curr->right;
            curr->right = curr->left;
            curr = root;
            while (curr != NULL)
            {
                curr->left = NULL;
                curr = curr->left;
            }
        }
        curr = curr->right;
    }
}

int main()
{
    Node *root = NULL;
    buildFromLevelOrder(root);
    // i/p: 1 2 3 4 5 -100 6 -100 7 -100 8 -100 -100 -100 -100 -100 -100
    /*
            1
          /  \
         2    3
       /  \    \
      4    5    6
       \    \
        7   8

    */
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    morrisTraversalPreorder(root);

    return 0;
}