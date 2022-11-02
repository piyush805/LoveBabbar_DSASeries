#include <iostream>
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

// insert a node at the head
void inserAtHead(Node *&head, int x)
{
    Node *temp = new Node(x);
    temp->next = head;
    head = temp;
}

// inseting a node at tail
void inserAtTail(Node *&head, int x)
{
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    Node *insert = new Node(x);
    temp->next = insert;
    insert->next = NULL;
}

// insert at a given ith position(1 indexed)
void insertAtPosition(Node *&head, int pos, int x)
{
    if (pos == 1)
    {
        inserAtHead(head, x);
        return;
    }
    // traverse upto that position
    Node *temp = head;
    int cnt = 1;
    while (cnt < pos - 1)
    {
        temp = temp->next;
        cnt++;
    }
    // if that position is tail
    if (temp->next == NULL)
    {
        inserAtTail(head, x);
        return;
    }
    Node *nodeToInsert = new Node(x);
    nodeToInsert->next = temp->next;
    temp->next = nodeToInsert;
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

//delete first node with given value
void deleteNodeAtVal(Node *&head, int val)
{
    if (val == head->data)
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

        // reach the position
        while (val != current->data)
        {
            prev = current;
            if (prev->next == NULL)
            {
                cout << "Value does not exist in Linked List" << endl;
                return;
            }
            current = current->next;
        }
        // delete current node
        prev->next = current->next;
        current->next = NULL; // before delettion, node should not be poiting to any of node of out linked list;
        delete current;
    }
}

//create linked list of size n with given array of numbers
Node *createLinkedList(int arr[], int n)
{

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

    int arr[5] = {1, 4, 3, 6, 2};
    int size = 5;
    Node *head = createLinkedList(arr, size);
    print(head);
    int value1 = 5;
    cout << "Insert " << 5 << " at head" << endl;
    inserAtHead(head, value1);
    print(head);
    cout << endl;

    int value2 = 8;
    cout << "Insert " << value2 << " at tail" << endl;
    inserAtTail(head, value2);
    print(head);
    cout << endl;

    int position = 3, value3 = 11;
    cout << "Insert " << value3 << " at position " << position << endl;
    insertAtPosition(head, position, value3);
    print(head);
    cout << endl;

    int pos = 7;
    cout << "Deleting node at position " << pos << endl;
    deleteNodeAtPos(head, pos);
    print(head);
    cout << endl;

    int val = 1;
    cout << "Deleting node with value " << val << endl;
    deleteNodeAtVal(head, val);
    print(head);
    cout << endl;

    return 0;
}