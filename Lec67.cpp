#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ====== Minimum Time to burn an entire binary tree starting from a given node =======

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

// Function to return target 'Node' and create mapping of all nodes with their parent node
Node *createParentMapping(Node *root, int target, map<Node *, Node *> &nodeToParent)
{
    // Traverse with queue and create map of parent to its left and right
    Node *res = NULL; // Target node will be stored in this
    queue<Node *> q;

    q.push(root);
    nodeToParent[root] = NULL; // no parent of root node;

    while (!q.empty())
    {
        Node *front = q.front();
        q.pop();

        if (front->data == target)
        {
            // target node found
            res = front;
        }

        // front Node is parent of both its left and right node
        if (front->left)
        {
            nodeToParent[front->left] = front;
            q.push(front->left);
        }
        if (front->right)
        {
            nodeToParent[front->right] = front;
            q.push(front->right);
        }
    }
    return res;
}

int burnTree(Node *root, map<Node *, Node *> &nodeToParent)
{
    map<Node *, bool> burnt;
    queue<Node *> q;

    q.push(root);
    burnt[root] = true; // mark target node visited

    int time = 0;

    while (!q.empty()) // traverse node by node unvisited nodes and increment timer
    {
        bool flag = 0; // mark if some element pushed into queue i.e. if some more nodes are burned in left, right, or parent direction

        int size = q.size();

        for (int i = 0; i < size; i++)
        {
            Node *front = q.front();
            if (front->data)
            {
            }
            q.pop();
            // If current node has unburnt left node
            if (front->left && !burnt[front->left])
            {
                flag = 1;               // neighbour node burnt at this node
                q.push(front->left);    // to traverse
                burnt[front->left] = 1; // mark burnt
            }
            // If current node has unburnt right node
            if (front->right && !burnt[front->right])
            {
                flag = 1;                // neighbour node burnt at this node
                q.push(front->right);    // to traverse
                burnt[front->right] = 1; // mark burnt
            }

            Node *parent = nodeToParent[front];
            // if current node has an unburnt parent node
            if (parent && !burnt[parent])
            {
                flag = 1;          // neighbour node burnt at this node
                q.push(parent);    // to traverse
                burnt[parent] = 1; // mark burnt
            }
        }
        // if atleast one neigbouring node was burnt at this level->timer increment;

        if (flag == 1)
        {
            time++;
        }
    }
    // return whene q empty i.e. entire tree traversed
    return time;
}

// Function for function calls
int minTime(Node *root, int target)
{
    map<Node *, Node *> nodeToParent;
    Node *targetNode = createParentMapping(root, target, nodeToParent);

    int ans = burnTree(targetNode, nodeToParent);

    return ans;
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
        for target node 7,8-> time = 7 seconds
        for target noe 6, time = 5 seconds
        */
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    int target = 6;

    cout << "Time to burn tree starting from target node " << target << " is " << minTime(root, target) << " seconds" << endl;
    
    return 0;
}