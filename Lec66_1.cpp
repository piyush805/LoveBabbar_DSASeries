#include <iostream>
#include <map>
#include <queue>
using namespace std;
//============== Build Binarytree using preorder and inorder ==================
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

// Find position of root element in inorder
int findPosition(int in[], int element, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (in[i] == element)
        {
            return i;
        }
    }
    return -1;
}

Node *buildTree(int in[], int pre[], int &index, int inOrderStart, int inOrderEnd, int size, map<int, int> nodeToIndex)
{
    if (index >= size || inOrderStart > inOrderEnd)
    {
        //start increase and end decreased in each call so they shouldnt cross each other 
        //index should be withing prOrder array size
        return NULL;
    }
    int element = pre[index++];//each step, next element becomes root at that step
    Node *root = new Node(element);

    // int position = findPosition(in, element, size);
    int position = nodeToIndex[element];

    root->left = buildTree(in, pre, index, inOrderStart, position - 1, size, nodeToIndex);

    root->right = buildTree(in, pre, index, position + 1, inOrderEnd, size, nodeToIndex);

    return root;
}

// Function to create mapping for in order LNR elements to index,
// to optimise having  to finf root index each time by linear search
void createInOrderMapping(int in[], map<int, int> &nodeToIndex, int n)
{
    for (int i = 0; i < n; i++)
    {
        nodeToIndex[in[i]] = i;
    }
}
int main()
{
    int pre[] = {0, 1, 3, 4, 2, 5};
    int in[] = {3, 1, 4, 0, 5, 2};
    int n = 6;
    int preOrderIndex = 0;//The root at each step of tree is at 0th of that preOrder
    /*
        1. PreOrder = take index 0 as root element because N-L-R
        2. POS = Find index of this root element in inOrder ->[...L...] N [...R...]
        3. Root left recursion  from [0, pos - 1] = L
        4. Root right recursion from [pos + 1, end] = R
        Left call first because preorder N-L-R so left first then right
    Optimisation:
        Finding each time index of root element in inOrder, can be optimised using initially creating map, and passing it to build function
        T.C -  O(n Log n)
    */
    map<int, int> nodeToIndex;
    createInOrderMapping(in, nodeToIndex, n);//create inorder element mapping to their index
    //build tree and return its root
    Node *ans = buildTree(in, pre, preOrderIndex, 0, n - 1, n, nodeToIndex);
    
    cout << "Level order traversal: " << endl;
    levelOrderTraversal_line(ans);
    return 0;
}