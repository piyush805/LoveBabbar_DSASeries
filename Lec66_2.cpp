#include <iostream>
#include <map>
#include <queue>
using namespace std;
//============== Build Binarytree using postorder and inorder ==================
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

Node *buildTree(int in[], int post[], int &index, int inOrderStart, int inOrderEnd, int size, map<int, int> nodeToIndex)
{
    if (index < 0 || inOrderStart > inOrderEnd)
    {
        // start increase and end decreased in each call so they shouldnt cross each other
        // index should be withing postOrder array size
        return NULL;
    }
    int element = post[index--]; // each step, next element becomes root at that step
    Node *root = new Node(element);
    // int position = findPosition(in, element, size);
    int position = nodeToIndex[element];
    // right call first: because postorder LRN, moving from last towards 0th, because each time index-- in postorder is the root that that level/left-right, so right call first then left call
    root->right = buildTree(in, post, index, position + 1, inOrderEnd, size, nodeToIndex);

    root->left = buildTree(in, post, index, inOrderStart, position - 1, size, nodeToIndex);

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
    int in[] = {4, 8, 2, 5, 1, 6, 3, 7};   // L-N-R
    int post[] = {8, 4, 5, 2, 6, 7, 3, 1}; // L-R-N
    int n = 8;
    int postOrderIndex = n - 1; // The root initially n-1 at  of that postOrder
    /*
        1. PostOrder = take index last as root element because N-L-R
        2. POS = Find index of this root element in inOrder ->[...L...] N [...R...]
        3. Root left recursion  from [0, pos - 1] = L
        4. Root right recursion from [pos + 1, end] = R
        Right call first because postorder L-R-N so right first then left
    Optimisation:
        Finding each time index of root element in inOrder, can be optimised using initially creating map, and passing it to build function
        T.C -  O(n Log n)
    */
    map<int, int> nodeToIndex;
    createInOrderMapping(in, nodeToIndex, n); // create inorder element mapping to their index
    // build tree and return its root
    Node *ans = buildTree(in, post, postOrderIndex, 0, n - 1, n, nodeToIndex);

    cout << "Level order traversal: " << endl;
    levelOrderTraversal_line(ans);
    return 0;
}