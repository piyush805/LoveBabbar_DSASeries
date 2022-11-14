#include <iostream>
#include <map>
#include <queue>
using namespace std;
// ============ Merge Two BST : inplace using linked lists==============
/*
    1. Flatten both BST to Linked lists
    2. Merge sort both linked lists
    3. Sorted Linked list to Balanced BST, making sure SC <  O(h1+h2)


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

void printV(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->right;
    }
    cout << "X" << endl;
}

void convertedIntoSortedDLL(Node *root, Node *&head)
{
    /*
        1.  Convert right subtree to DLL by recursion->return head of DLL
        2.  root->right = head;
            head ->left = root;
            head = root
        3. convert left subtree into DLL->return head of DLL

    */
    if (root == NULL)
    {
        return;
    }
    convertedIntoSortedDLL(root->right, head); // right BST into LL
    root->right = head;                        // root->head
    if (head != NULL)
    {
        head->left = root; // had->root
    }
    // ^ Doubly logic
    head = root;                              // move head forward
    convertedIntoSortedDLL(root->left, head); // Left BST in LL
}

Node *mergeLinkedList(Node *head1, Node *head2)
{
    // Pointers of 3rd new linked list
    Node *head = NULL;
    Node *tail = NULL;
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data < head2->data) // 1st LL element smaller
        {
            if (head == NULL) // 1st first element
            {
                head = head1;
                tail = head1;
                head1 = head1->right;
            }
            else
            {
                tail->right = head1; // smaller element at end of this LL
                head1->left = tail;
                tail = head1;         // this element is the new tail
                head1 = head1->right; // point to next in 1st LL to compare next time
            }
        }
        else // 2nd LL element smaller
        {
            if (head == NULL) // 1f first element
            {
                head = head2;
                tail = head2;
                head2 = head2->right;
            }
            else
            {
                tail->right = head2; // smaller element at end of this LL
                head2->left = tail;
                tail = head2;         // this element is the new tail
                head2 = head2->right; // point to next in 1st LL to compare next time
            }
        }
    }
    // 1f 1st LL pointer not reach the end
    while (head1 != NULL)
    {
        tail->right = head1;
        head->left = tail;
        tail = head1;
        head1 = head1->right;
    }
    // 1st second LL pointer not reach the end
    while (head2 != NULL)
    {
        tail->right = head2;
        head2->left = tail;
        tail = head2;
        head2 = head2->right;
    }
    // tail->right = NULL;

    // return head of this new merged DLL
    return head;
}

int countNodes(Node *head)
{
    int cnt = 0;
    Node *temp = head;
    while (temp != NULL)
    {
        cnt++;
        temp = temp->right;
    }
    return cnt;
}

Node *sortedLLtoBST(Node *&head, int n)
{
    if (n <= 0 || head == NULL)
    {
        return NULL;
    }
    Node *left = sortedLLtoBST(head, n / 2); // returns root of left BST

    Node *root = head;
    root->left = left;
    head = head->right;

    root->right = sortedLLtoBST(head, n - n / 2 - 1); // returns root of right BST

    return root;
}

Node *merge(Node *root1, Node *root2)
{
    // Step 1 : convert both to sorted DLL
    Node *head1 = NULL;
    convertedIntoSortedDLL(root1, head1);
    head1->left = NULL;

    Node *head2 = NULL;
    convertedIntoSortedDLL(root2, head2);
    head2->left = NULL;

    // Step 2: merge 2 sorted DLL
    Node *head = mergeLinkedList(head1, head2);
    // Step 3: sorted LL to BST
    return sortedLLtoBST(head, countNodes(head));
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
    Node *root3 = merge(root1, root2);

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