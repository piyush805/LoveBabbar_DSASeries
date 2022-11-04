//{ Driver Code Starts
#include <bits/stdc++.h>

using namespace std;
/* Link list Node */
struct Node
{
    int data;
    Node *next;
    Node *arb;

    Node(int x)
    {
        data = x;
        next = NULL;
        arb = NULL;
    }
};

// } Driver Code Ends

//===================================================================================
class Solution
{
public:
    void insertAtTail(Node *&head, Node *&tail, int value)
    {
        Node *temp = new Node(value); // node to insert
        if (head == NULL)             // if no node, new node = head = tail
        {
            head = temp;
            tail = temp;
            temp->next = NULL;
            return;
        }
        // else add it next to tail
        tail->next = temp;
        temp->next = NULL;
        tail = temp; // new node is new tail
    }

    // without use of MAP:  S.C = O(1)
    Node *copyList(Node *head)
    {
        Node *cloneHead = NULL;
        Node *cloneTail = NULL;
        Node *temp = head;
        // Step 1: Create Clone list
        while (temp != NULL)
        {
            insertAtTail(cloneHead, cloneTail, temp->data);
            temp = temp->next;
        }

        // Step 2: Clone Nodes add in between original Nodes
        Node *originalNode = head;
        Node *cloneNode = cloneHead;
        while (originalNode != NULL && cloneNode != NULL)
        {
            Node *next = originalNode->next; // store remaining org LL
            originalNode->next = cloneNode;  // pointing from original to cloneNode
            originalNode = next;             // org move forward

            next = cloneNode->next;         // store reamaining of clone LL
            cloneNode->next = originalNode; // pointing from clone to next Original node
            cloneNode = next;               // move forward in cloneList
        }

        // Step 3: Random pointers copy
        temp = head;
        // traversing original List
        while (temp != NULL)
        {
            if (temp->next != NULL) // temp->next means correspoding node in cloneList with same value
            {
                temp->next->arb = temp->arb ? temp->arb->next : temp->arb;
                /*  If random pointer of node in original Node exist
                        temp->arb will go to that random node in original List
                        temp->arb->next will be correspoding random node in cloneList with same value
                    Else If random pointer of this node in original list is NULL
                        then random of node in clonelist be also NULL
                    */
            }
            temp = temp->next->next; // Because original and clone List nodes are alterate set
            // temp ->next  will be same value node in clone List
            // temp->next->next will ne next node in origninal list
        }

        // Step 4: Revert connection changes done in step 2
        originalNode = head;
        cloneNode = cloneHead;
        while (originalNode != NULL && cloneNode != NULL)
        {
            originalNode->next = cloneNode->next; // Each clone node points to next node in original List
            // so above step will set original list correctly
            originalNode = originalNode->next; // move to next node in original LL

            if (originalNode != NULL) // if each original node points downward to next node in clone List
            {
                cloneNode->next = originalNode->next; // this will set clone list correctly
            }
            cloneNode = cloneNode->next; // move to next node in clone LL
        }
        // Step 5: return ans
        return cloneHead;
    }

    // With use of map SC =O(n)
    Node *copyList_2(Node *head)
    {
        // Write your code here
        unordered_map<Node *, Node *> oldToNew;
        Node *cloneHead = NULL;
        Node *cloneTail = NULL;
        Node *temp = head;

        while (temp != NULL)
        {
            insertAtTail(cloneHead, cloneTail, temp->data);
            oldToNew[temp] = cloneTail;
            // each original Node point to newly formed cloneNode with same value in clone LL
            temp = temp->next;
        }

        Node *originalNode = head;
        Node *cloneNode = cloneHead;

        while (originalNode != NULL)
        {

            cloneNode->arb = oldToNew[originalNode->arb];
            // values of originalNode->arb and those in mapping is same but address is different
            // simply doing originalNode->arb makes clone->random point to that node in orginal list
            // To appraoch same value node in clone we use mapping of original->Node to reach same clone value in cloneList
            originalNode = originalNode->next;
            cloneNode = cloneNode->next;
        }
        return cloneHead;
    }
};

//================================================================================
//{ Driver Code Starts.

void print(Node *root)
{
    Node *temp = root;
    while (temp != NULL)
    {
        int k;
        if (temp->arb == NULL)
            k = -1;
        else
            k = temp->arb->data;
        cout << temp->data << " " << k << " ";
        temp = temp->next;
    }
}

void append(Node **head_ref, Node **tail_ref, int new_data)
{

    Node *new_node = new Node(new_data);
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
    }
    else
        (*tail_ref)->next = new_node;
    *tail_ref = new_node;
}

bool validation(Node *head, Node *res)
{

    Node *temp1 = head;
    Node *temp2 = res;

    int len1 = 0, len2 = 0;
    while (temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    /*if lengths not equal */

    if (len1 != len2)
        return false;

    temp1 = head;
    temp2 = res;
    map<Node *, Node *> a;
    while (temp1 != NULL)
    {

        if (temp1 == temp2)
            return false;

        if (temp1->data != temp2->data)
            return false;
        if (temp1->arb != NULL and temp2->arb != NULL)
        {
            if (temp1->arb->data != temp2->arb->data)
                return false;
        }
        else if (temp1->arb != NULL and temp2->arb == NULL)
            return false;
        else if (temp1->arb == NULL and temp2->arb != NULL)
            return false;
        a[temp1] = temp2;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    temp1 = head;
    temp2 = res;
    while (temp1 != NULL)
    {

        if (temp1->arb != NULL and temp2->arb != NULL)
        {
            if (a[temp1->arb] != temp2->arb)
                return false;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

int main()
{

    int T, i, n, l, k;
    Node *generated_addr = NULL;
    /*reading input stuff*/
    cin >> T;
    while (T--)
    {
        generated_addr = NULL;
        struct Node *head = NULL, *tail = NULL;
        struct Node *head2 = NULL, *tail2 = NULL;
        cin >> n >> k;
        for (i = 1; i <= n; i++)
        {
            cin >> l;
            append(&head, &tail, l);
            append(&head2, &tail2, l);
        }
        for (int i = 0; i < k; i++)
        {
            int a, b;
            cin >> a >> b;

            Node *tempA = head;
            Node *temp2A = head2;
            int count = -1;

            while (tempA != NULL)
            {
                count++;
                if (count == a - 1)
                    break;
                tempA = tempA->next;
                temp2A = temp2A->next;
            }
            Node *tempB = head;
            Node *temp2B = head2;
            count = -1;

            while (tempB != NULL)
            {
                count++;
                if (count == b - 1)
                    break;
                tempB = tempB->next;
                temp2B = temp2B->next;
            }

            // when both a is greater than N
            if (a <= n)
            {
                tempA->arb = tempB;
                temp2A->arb = temp2B;
            }
        }
        /*read finished*/

        generated_addr = head;
        Solution ob;
        struct Node *res = ob.copyList(head);
        if (validation(head2, res) && validation(head, res))
            cout << validation(head2, res) << endl;
        else
            cout << 0 << endl;
    }
    return 0;
}
// } Driver Code Ends