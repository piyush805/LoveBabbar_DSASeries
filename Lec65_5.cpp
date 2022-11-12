#include <iostream>
#include <queue>
using namespace std;
//============== Max Sum of NON adjacent nodes ==================
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

/* Approach: <a,b>
    a = max sum by including nodes at current level
    b = max sum by excluding nodes at current level
    calculate both sum on returning from leaf nodes
*/
pair<int, int> getMaxSum(node *root)
{
    if (root == NULL)
    {
        pair<int, int> p = make_pair(0, 0); // sum obtained at leaf node
        return p;
    }
    pair<int, int> left = getMaxSum(root->left);
    pair<int, int> right = getMaxSum(root->right);

    pair<int, int> ans;
    // first = including current + sum on excluding its left and right
    ans.first = root->data + left.second + right.second;
    // second = exclude current + max sum from left and right on including and excluding
    // because maximising sum is imp, elements may also be -ve
    ans.second = max(left.first, left.second) + max(right.first, right.second);

    return ans;
}

int main()
{
    node *root = NULL;
    // root = buildTree(root);
    buildFromLevelOrder(root);
    // i/p: 1 2 3 4 -100 5 6 -100 -100 -100 -100 -100 -100
    /*
            1
           / \
          2   3
        /    / \
       4    5   6
    sum1 = 1(root) + 1 + 4 + 5 = 11
    sum2 = 2 + 3 = 5
    max = 11

    At, 1, 4, 5: Sum = <0,0>, send above (4, 0), (5, 0), (6, 0)
    At 2: <2, 4>
        including 2: cant include 4: <2,0>
        excluding 2: can include 4: <4,0>
    At 3: <3, 11>
        including 3: cant including 4,5: = 3
        excluding 3: include 4,5: 5+6 = 11
    At 1: <16,15>
        including 1: exclude 2, 3: 1 + 4(when excluded 2) + 11(when excluded 3) = 16
        excluding 1: include or not include 2, 3: max of include and exclude of both:
                    max(2, 4) + max(3, 11) = 4 + 11 = 15
    max at sum become = max(16, 15) = 16
        */
    cout << endl;
    cout << "Level order traversal:" << endl;
    levelOrderTraversal_line(root);
    cout << endl;

    pair<int, int> p = getMaxSum(root);
    cout << "Max sum is: " << max(p.first, p.second) << endl;

    return 0;
}