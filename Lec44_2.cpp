#include <iostream>
using namespace std;
// ##################  DOUBLY LINKED LIST  ###########################3 
class Node
{
public:
    int data;
    Node *next;
    Node *prev;
    // constructor
    Node(int d)
    {
        this->data = d;
        this->next = NULL;
        this->prev = NULL;
    }
};

// travese and print all node data of list
void print(Node *&head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "X";
    cout << endl;
}

// insert a node at head
void insertAtHead(Node *&head, int d)
{
    Node *temp = new Node(d);
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void insertAtTail(Node *&head, int d)
{
    Node *insert = new Node(d);
    Node *temp = head;
    // traverse upto tail
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = insert;
    insert->prev = temp;
}

void insertAtPos(Node *&head, int pos, int d)
{
    if (pos == 1)
    {
        insertAtHead(head, d);
        return;
    }
    Node *temp = head;
    int cnt = 1;
    // traverse temp upto before pos where to insert
    while (cnt < pos - 1)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            cout << "WARNING: Invalid position " << endl;
            return;
        }
        cnt++;
    }
    // if reached end
    if (temp->next == NULL)
    {
        insertAtTail(temp, d);
        return;
    }
    // if inserting at intermidiate pos: all 4 pointer to corrent place
    Node *nodeToInsert = new Node(d);
    nodeToInsert->next = temp->next;
    temp->next->prev = nodeToInsert;
    temp->next = nodeToInsert;
    nodeToInsert->prev = temp;
}

// helper function of both delete fucntion:
//  Delete a particular node
void deleteNode(Node *&temp)
{
    Node *prev = temp->prev; // store the previous node
    temp->next->prev = prev; // a<--b<--c == a<--c
    prev->next = temp->next; // a-->b-->c == a-->c
    temp->next = NULL;       // free pointers of node to delete
    temp->prev = NULL;
    delete temp; // temp point to node to delete
}

// deleting a node from ith position (1 indexed)
void deletionAtPos(Node *&head, int pos)
{
    Node *temp = head;
    if (pos == 1)
    {
        // delete head node
        head = temp->next; // new head
        head->prev = NULL; // free pointers of old head
        temp->next = NULL;
        delete temp; // temp points to old head; delete it
        return;
    }
    int cnt = 1;
    // traverse to before pos where to delete the node(1 indexed)
    while (cnt < pos)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            cout << "WARNING: Invalid position " << endl;
            return;
        }
        cnt++;
    }

    if (temp->next == NULL)
    {
        // deleting tail node
        temp->prev->next = NULL;
        temp->prev = NULL;
        delete temp;
        return;
    }
    deleteNode(temp);
}

// delete first node with given value
void deletionWithVal(Node *&head, int val)
{
    Node *temp = head;
    if (head->data == val)
    {
        // delete head node
        head = temp->next; // new head
        head->prev = NULL; // free pointers of old head
        temp->next = NULL;
        delete temp; // temp points to old head; delete it
        return;
    }
    // traverse to node where value match
    while (temp->data != val)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            cout << "WARNING: Value not in list " << endl;
            return;
        }
    }

    if (temp->next == NULL)
    {
        // deleting tail node
        temp->prev->next = NULL; // make 2nd last as tail
        temp->prev = NULL;       // free pointer of node to delete
        delete temp;             // temp pointing to last node, delete it
        return;
    }
    // Some middle node
    deleteNode(temp);
}

// create linked list of size n with given array of numbers
Node *createLinkedList(int arr[], int n)
{

    Node *head = new Node(arr[0]);
    Node *previous = head;
    int i = 1;
    while (i < n)
    {
        Node *current = new Node(arr[i]);
        previous->next = current;
        current->prev = previous;
        previous = previous->next;
        i++;
    }
    previous->next = NULL;
    return head;
}

int main()
{
    int arr[1] = {1};
    int size = 1;
    Node *head = createLinkedList(arr, size);
    cout << "Doubly linked list:" << endl;
    print(head);

    // insert at head
    int val = 2;
    cout << "Inserting " << val << " at head" << endl;
    insertAtHead(head, val);
    print(head);

    // insrt at tail
    val = 3;
    cout << "Inserting " << val << " at tail" << endl;
    insertAtTail(head, val);
    print(head);

    int pos = 2;
    val = 11;
    cout << "Inserting " << val << " at position " << pos << endl;
    insertAtPos(head, pos, val);
    print(head);

    pos = 2;
    cout << "Deleting node at position " << pos << endl;
    deletionAtPos(head, pos);
    print(head);

    val = 1;
    cout << "Deleting node with value " << val << endl;
    deletionWithVal(head, val);
    print(head);
    return 0;
}