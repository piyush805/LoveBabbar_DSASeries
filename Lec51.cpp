#include <iostream>
#include <vector>
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

// Reverse given LL and return new head
Node *reverseLL(Node *head)
{
    Node *curr = head;
    Node *next = NULL;
    Node *prev = NULL;
    while (curr != NULL)
    {
        next = curr->next; // save  remaining list
        curr->next = prev; // reverse current pointer
        // move forward
        prev = curr;
        curr = next;
    }
    return prev;
}

// inserts unit digit after adding two digits into ans LL
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

// Performs addition from left to right in singly LL
Node *add_1(Node *first, Node *second)
{
    Node *ansHead = NULL;
    Node *ansTail = NULL;
    int carry = 0;
    // Until any of 2 LL over, keep adding to tail of ans
    while (first != NULL && second != NULL)
    {
        int sum = carry + first->data + second->data;
        int digit = sum % 10;

        insertAtTail(ansHead, ansTail, digit);
        carry = sum / 10;
        first = first->next;
        second = second->next;
    }
    // If first reamining after addition, add to sum
    while (first != NULL)
    {
        int sum = carry + first->data;
        int digit = sum % 10;
        insertAtTail(ansHead, ansTail, digit);
        carry = sum / 10;
        first = first->next;
    }
    // if second remaining after addition, add to sum
    while (second != NULL)
    {
        int sum = carry + second->data;
        int digit = sum % 10;
        insertAtTail(ansHead, ansTail, digit);
        carry = sum / 10;
        second = second->next;
    }
    // if carry reamins in the end, add it
    while (carry != 0)
    {
        int sum = carry;
        int digit = sum % 10;
        insertAtTail(ansHead, ansTail, digit);
        carry = sum / 10;
    }
    return ansHead;
}

Node *add_2(Node *first, Node *second)
{
    Node *ansHead = NULL;
    Node *ansTail = NULL;
    int carry = 0;

    while (first != NULL || second != NULL || carry != 0)
    {
        int val1 = 0, val2 = 0;
        if (first != NULL)
        {
            val1 = first->data;
            // update later because we want to perform operation first
        }
        if (second != NULL)
        {
            val2 = second->data;
            // update later because we want to perform operation first
        }

        int sum = carry + val1 + val2;
        int digit = sum % 10;
        insertAtTail(ansHead, ansTail, digit);
        carry = sum / 10;
        // move first and second to next (if exist) after performing the operation
        if (first != NULL)
        {
            first = first->next;
        }
        if (second != NULL)
        {
            second = second->next;
        }
    }
    return ansHead;
}
// Function to make function calls and return sum
Node *addTwoNumbers(Node *first, Node *second)
{
    // reverse both because we add from right to left
    first = reverseLL(first);
    second = reverseLL(second);
    Node *ans = add_2(first, second);
    // reverse because the addition is reversed
    ans = reverseLL(ans);
    return ans;
}

int main()
{
    int arr1[] = {3, 8, 4};
    int size = 3;
    Node *first = createLinkedList(arr1, size);
    cout << "First:  ";
    print(first);

    int arr2[] = {4, 5};
    size = 2;
    Node *second = createLinkedList(arr2, size);
    cout << "Second: ";
    print(second);

    Node *sum = addTwoNumbers(first, second);
    cout << "Sum:    ";
    print(sum);

    return 0;
}