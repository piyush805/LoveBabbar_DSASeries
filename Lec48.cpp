#include <iostream>
#include <map>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    // constructor
    Node(int data)
    {
        this->data = data;
        this->next - NULL;
    }
};

// Traversing and printing elements
void print(Node *&head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << "-> ";
        temp = temp->next;
    }
    cout << "X";
    cout << endl;
}

Node *uniqueSortedList(Node *head)
{
    if (head == NULL)
    {
        return head;
    }
    // Write your code here.
    Node *temp = head;
    while (temp->next != NULL)
    {
        //        cout<<"checking next of "<<temp->data<<endl;
        if (temp->data == temp->next->data)
        {
            Node *next_next = temp->next->next;
            Node *nodeToDelete = temp->next;
            temp->next = next_next;
            delete nodeToDelete;
        }
        else
        {
            temp = temp->next;
        }
    }
    return head;
}

Node *uniqueUnsortedList1(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        // no or only single node then no duplicates
        return head;
    }
    // for each node, traverse the subsequent LL for duplicates and delete them
    Node *i = head;
    while (i->next != NULL)
    {
        Node *j = i;
        while (j->next != NULL)
        {
            if (i->data == j->next->data)
            {
                // duplicate found
                // save further LL
                Node *next_next = NULL;
                if (j->next->next != NULL)
                {
                    next_next = j->next->next;
                }
                Node *nodeToDelete = j->next; // the duplicate
                delete nodeToDelete;
                j->next = next_next; // now j point to next to deleted one
            }
            else
            {
                j = j->next;
            }
        }
        if (i->next == NULL)
        {
            // If all deletions no further node remains the out
            break;
        }
        i = i->next;
    }

    return head;
}

Node *uniqueUnsortedList2(Node *head)
{
    // Sort the LL
    // Use uniqueSortedList
    return head;
}

Node *uniqueUnsortedList3(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        // no or only single node then no duplicates
        return head;
    }
    map<int_fast8_t, bool> visited;
    Node *temp = head;
    Node *prev = temp;
    while (temp != NULL)
    {
        if (visited[temp->data])
        {
            // temp on duplicate node
            Node *next_next = temp->next; // save reamining LL
            Node *nodeToDelete = temp;
            prev->next = next_next; // attach to reamining
            delete nodeToDelete;    // this duplicate
            temp = prev->next;      // move temp to this new attached node
        }
        else
        {
            // mark this node as visited
            visited[temp->data] = true;
            prev = temp; // move prev forward
            // Cant move forward if already on last node
            if (temp->next == NULL)
            {
                break;
            }
            //else move forward temp
            temp = temp->next;
        }
    }
    return head;
}

// create linked list of size n with given array of numbers
Node *createLinkedList(int arr[], int n)
{
    if (n == 0)
    {
        return NULL;
    }
    Node *head = new Node(arr[0]);
    Node *previous = head;
    int i = 1;
    while (i < n)
    {
        Node *current = new Node(arr[i]);
        previous->next = current;
        previous = previous->next;
        i++;
    }
    previous->next = NULL;
    return head;
}

int main()
{
    int arr[] = {5,2,1,5,2,7,1,8,3,2,1};
    int size = 11;
    Node *head = createLinkedList(arr, size);
    print(head);

    head = uniqueUnsortedList3(head);
    print(head);

    return 0;
}