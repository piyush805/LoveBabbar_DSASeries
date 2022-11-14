#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ============ Merge Two BST: using inorder vectors ==============
/*
    1. Calculate inorder from both BST
    2. Merge sort the inorders to get inorder for new BST
    3. Create BST from new inorder

TC->O(m+n)
SC -> O(m+n) //storing both inorders
Can we do it in SC O(h1 + h2)
In place flattening the BST to linked list
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

// Recursive function to seach where to insert the new element then insert it at that leaf;
Node *insertIntoBST(Node *root, int d)
{
    if (root == NULL)
    {
        root = new Node(d);
        return root;
    }
    if (d > root->data)
    {
        root->right = insertIntoBST(root->right, d);
    }
    else
    {
        root->left = insertIntoBST(root->left, d);
    }
    return root;
}

// Function to keep taking node inputs for BST and call funciton to insert node
void takeInput(Node *&root)
{
    int data;
    cin >> data;
    while (data != -1)
    {
        root = insertIntoBST(root, data);
        cin >> data;
    }
}
void printV(vector<int> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
// Find in_order
void inorder(Node *root, vector<int> &in)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}

//
vector<int> mergeArray(vector<int> a, vector<int> b)
{
    vector<int> ans(a.size() + b.size(), 0); // ans array
    int i = 0, j = 0, k = 0;
    while (i < a.size() && j < b.size())
    {
        if (a[i] < b[j])
        {
            ans[k++] = a[i++];
        }
        else
        {
            ans[k++] = b[j++];
        }
    }
    // if a inorder finished first
    while (i < a.size())
    {
        ans[k++] = a[i++];
    }

    // if b inorder finished first
    while (j < b.size())
    {
        ans[k++] = b[j++];
    }
    return ans;
}

//
Node *inorderToBST(int s, int e, vector<int> &in)
{
    if (s > e)
    {
        return NULL;
    }
    int mid = (s + e) / 2; // inorder sorted so no need to check left and right, all left values goes into left subtree, all right values go into right subtree
    Node *root = new Node(in[mid]);
    root->left = inorderToBST(s, mid - 1, in);
    root->right = inorderToBST(mid + 1, e, in);
    return root;
}

Node *mergeBST(Node *root1, Node *root2)
{
    // 2 vector inorder
    vector<int> bst1, bst2;
    inorder(root1, bst1);
    inorder(root2, bst2);
    // merge inorder
    vector<int> mergedArray = mergeArray(bst1, bst2);

    int s = 0, e = mergedArray.size() - 1;
    // BST from new inorder
    return inorderToBST(s, e, mergedArray);
}

int main()
{
    Node *root1 = NULL;
    cout << "Enter data: " << endl;
    // 50 40 60 70 -1
    takeInput(root1);
    Node *root2 = NULL;
    cout << "Enter data: " << endl;
    // 55 45 65 35 47 -1
    takeInput(root2);
    Node *root3 = mergeBST(root1, root2);

    cout << "Merged BST is:" << endl;
    levelOrderTraversal_line(root3);
    /*
              50
            /   \
           40    60
         /  \   /  \
        35  45 55  65
             \       \
              47     70
   */

    return 0;
}