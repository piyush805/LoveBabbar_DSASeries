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

// Get middle node of LL
Node *getmiddle(Node *head)
{
    Node *slow = head;
    Node *fast = head->next;
    while (fast != NULL && fast->next != NULL)
    {
        // Fast reaches null when odd list, Fast reaches last node when even LL
        fast = fast->next->next;
        slow = slow->next;
    }
    // slow we be at middle
    return slow;
}

Node *merge(Node *left, Node *right)
{
    // If either of half is null, simply return other list
    if (left == NULL)
    {
        return right;
    }
    if (right == NULL)
    {
        return left;
    }
    // dummy node to attach sorted nodes to
    Node *ans = new Node(-1);
    Node *temp = ans; // traverse sorted list
    while (left != NULL && right != NULL)
    {
        if (left->data < right->data)
        {
            temp->next = left; // attach smaller left node
            temp = left;       // move forward temp
            left = left->next; // move forward left
        }
        else
        {
            temp->next = right;  // attach smaller right node
            temp = right;        // move forward temp
            right = right->next; // move forward right
        }
    }
    // if left half list is not over, attach it entirely
    if (left)
    {
        temp->next = left;
    }
    // if right half list is not over, attach it entirely
    if (right)
    {
        temp->next = right;
    }
    // first node was dummy node
    Node *dummy = ans;
    ans = ans->next; // actual sorted list start from one forward
    delete dummy;    // delete dummy node

    return ans;
}

Node *mergeSort(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        // if 0 or 1 node  then already sorted
        return head;
    }
    Node *mid = getmiddle(head); // find mid
    Node *left = head;           // head of left half
    Node *right = mid->next;     // head of right half
    mid->next = NULL;            // left half over at mid

    left = mergeSort(left);
    right = mergeSort(right);

    Node *result = merge(left, right);

    return result;
}

int main()
{
    int arr1[] = {3, 5, 1, 2, 3, 7, 9, 1, 12, 0};
    int size1 = 10;
    Node *head = createLinkedList(arr1, size1);
    cout << "Original: ";
    print(head);
    cout << "Sorted:   ";
    Node *merged = mergeSort(head);
    print(merged);
    return 0;
}