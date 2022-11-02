#include <iostream>
using namespace std;
//######################  SINGLY CIRCULAR LINKED LIST  ######################## 
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
void print(Node *&tail)
{
    if (tail == NULL)
    {
        cout << "Empty" << endl;
        return;
    }
    // single node
    if (tail->next == tail)
    {
        cout << tail->data << "-> ";
        cout << endl;
        return;
    }
    // more than one node
    Node *temp = tail;
    if (temp->next != NULL)
    {
        temp = temp->next;
        do
        {
            cout << temp->data << "-> ";
            temp = temp->next;
        } while (temp != tail);
        cout << temp->data << "-> "; // print tail node
        cout << endl;
    }
}

// insert node at tail
void insertAtEnd(Node *&tail, int d)
{
    Node *insert = new Node(d);
    // if no node in the LL
    if (tail == NULL)
    {
        insert->next = insert;
        tail = insert;
        return;
    }
    Node *temp = tail;
    // traverse upto node before tail node
    while (temp->next != tail)
    {
        temp = temp->next;
    }
    insert->next = tail;
    temp->next = insert;
    tail = insert; // newly inserted element is the new tail
}

// inseting a node at start
void insertAtStart(Node *&tail, int d)
{
    Node *insert = new Node(d);
    // if no node in the LL
    if (tail == NULL)
    {
        tail = insert;
        tail->next = tail;
        return;
    }
    // if tail node already present
    insert->next = tail->next;
    tail->next = insert;
}

// insert node after matching first element
void insertAfterNode(Node *&tail, int element, int d)
{
    if (element == tail->data)
    {
        // inserting after tail => inserting at head
        // Tail reamins same
        insertAtStart(tail, d);
        return;
    }
    Node *temp = tail;
    while (temp->data != element)
    {
        temp = temp->next;
    }

    Node *insert = new Node(d);
    insert->next = temp->next;
    temp->next = insert;
    if (temp == tail)
    {
        tail = insert;
    }
}

// deleting a node from ith position (1 indexed)
void deleteNodeAtPos(Node *&head, int pos)
{
    if (pos < 1)
    {
        cout << "Invalid node position given" << endl;
        return;
    }
    if (pos == 1)
    {
        // no need to traverse to delete head node
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    else
    {
        Node *current = head;
        Node *prev = NULL;
        int cnt = 1;
        // reach the position, (1 indexing)
        // when cnt<pos, in the loop, current points at node at pos
        // next time cnt++ so it comes out, pointing at current node
        while (cnt < pos)
        {
            prev = current;
            if (prev->next == NULL)
            {
                cout << "Invalid node pos given" << endl;
                return;
            }
            current = current->next;
            cnt++;
        }

        prev->next = current->next;
        current->next = NULL; // before delettion, node should not be poiting to any of node of out linked list;
        delete current;
    }
}

// delete first node with given value
void deleteNode(Node *&tail, int val)
{

    if (tail->next == tail && val == tail->data)
    {
        // only single node
        if (val == tail->data)
        {
            delete tail;
            tail = NULL;
        }
        else
        {
            cout << "WARNING: Value not in LL" << endl;
        }
        return;
    }
    //else traverse
    Node *current = tail->next;
    Node *prev = tail;

    // reach the position
    while (val != current->data)
    {

        prev = current;
        current = current->next;

        if (prev == tail) // when full circle complete = value not found
        {
            cout << "WARNING: Value not in LL" << endl;
            return;
        }
    }
    // delete current node
    prev->next = current->next;
    tail = prev;
    current->next = NULL; // before delettion, node should not be poiting to any of node of out linked list;
    delete current;
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
    previous->next = head;
    Node *tail = previous;
    return tail;
}

int main()
{

    int arr[2] = {6, 4};
    int size = 2;
    Node *tail = createLinkedList(arr, size);
    print(tail);

    int value1 = 7;
    cout << "Insert at head " << value1 << endl;
    insertAtStart(tail, value1);
    print(tail);
    cout << endl;

    value1 = 5;
    cout << "Insert at tail " << value1 << endl;
    insertAtEnd(tail, value1);
    print(tail);
    cout << endl;

    int element = 5, value3 = 11;
    cout << "Insert " << value3 << " after " << element << endl;
    insertAfterNode(tail, element, value3);
    print(tail);
    cout << endl;

    int val = 5;
    cout << "Deleting node value " << val << endl;
    deleteNode(tail, val);
    print(tail);
    cout << endl;

    return 0;
}