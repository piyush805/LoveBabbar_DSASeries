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

void insertAtTail(Node *&tail, Node *ptr)
{
    cout << "Inserting at tail: " << ptr->data << endl;
    tail->next = ptr;
    tail = ptr;
}
// Appraoch_1: Count 0,1,2 and change node data
void sort012_1(Node *head)
{
    if (head == NULL)
    {
        return;
    }
    Node *temp = head;
    int count0 = 0, count1 = 0, count2 = 0;
    while (temp != NULL)
    {
        if (temp->data == 0)
        {
            count0++;
        }
        else if (temp->data == 1)
        {
            count1++;
        }
        else
        {
            count2++;
        }
        temp = temp->next;
    }

    temp = head;
    // traverse and change data to all 0s then 1s then 2s
    while (temp != NULL)
    {

        if (count1 == 0 && count2 != 0)
        {
            temp->data = 2;
            count2--;
        }
        if (count0 == 0 && count1 != 0)
        {
            temp->data = 1;
            count1--;
        }
        if (count0 != 0)
        {
            temp->data = 0;
            count0--;
        }
        temp = temp->next;
    }
}

// Appraoch2: make 3 linked lists of 0s, 1s and 2s and merge them
Node *sort012_2(Node *&head)
{
    Node *zeroHead = new Node(-1);
    Node *zeroTail = zeroHead;
    Node *oneHead = new Node(-1);
    Node *oneTail = oneHead;
    Node *twoHead = new Node(-1);
    Node *twoTail = twoHead;

    Node *curr = head;
    while (curr != NULL)
    {
        int value = curr->data;
        if (value == 0)
        {
            insertAtTail(zeroTail, curr);
        }
        if (value == 1)
        {
            insertAtTail(oneTail, curr);
        }
        if (value == 2)
        {
            insertAtTail(twoTail, curr);
        }
        curr = curr->next;
    }

    if (oneHead != oneTail)
    {
        // LL one has some element
        zeroTail->next = oneHead->next;
    }
    else
    {

        zeroTail->next = twoHead->next;
    }
    oneTail->next = twoHead->next;
    twoTail->next = NULL;
    head = zeroHead->next;

    delete zeroHead;
    delete oneHead;
    delete twoHead;

    return head;
}

Node *mergeSortedLL(Node *first, Node *second)
{
    if (first->next == NULL)
    {
        // when 1st has only one node
        first->next = second;
        return first;
    }

    Node *curr1 = first;
    Node *next1 = curr1->next;
    Node *curr2 = second;
    Node *next2 = curr2->next;
    //Traversing first LL while checking where 2nd LL nodes fit in first
    //if first gets over sooner. attach 2nd as it is
    //if second gets over, then 1st gets traversed till the end
    while (next1 != NULL && curr2 != NULL)
    {

        if ((curr1->data <= curr2->data) && (curr2->data <= next1->data))
        {
            // curr1 <= curr2 <= next1
            curr1->next = curr2; // curr1->curr2
            next2 = curr2->next; // save remaining of second LL
            curr2->next = next1; // curr2->next1

            // Move pointers forward
            curr1 = curr2; // curr1 becomes newly attached node in first LL
            curr2 = next2; // curr2 become first of remaninig second LL
        }
        else
        {
            curr1 = next1;       // curr1 move forward
            next1 = next1->next; // next1 move forward
            if (next1 == NULL)
            {
                // When first LL over, attach remaining of second LL as it is
                curr1->next = curr2;
            }
        }
    }
    return first;
}

Node *callMerge(Node *first, Node *second)
{
    if (first == NULL)
    {
        return second;
    }
    if (second == NULL)
    {
        return first;
    }

    if (first->data <= second->data)
    {
        return mergeSortedLL(first, second);
    }
    else
    {
        return mergeSortedLL(second, first);
    }
}
int main()
{

    // int arr[] = {0, 0, 0, 1};
    // int size = 4;
    // Node *head = createLinkedList(arr, size);
    // print(head);
    // head = sort012_2(head);
    // print(head);

    int arr1[] = {1, 3, 6, 8, 10};
    int size1 = 5;
    int arr2[] = {3, 5, 7, 9, 14};
    int size2 = 5;
    Node *first = createLinkedList(arr1, size1);
    Node *second = createLinkedList(arr2, size2);

    first = callMerge(first, second);
    print(first);
    return 0;
}