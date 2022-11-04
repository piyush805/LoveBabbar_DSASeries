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

// Approach 1: Copy all nodes into vector check if it is palindrome
bool checkPalindrome_1(Node *head, int n)
{
    vector<int> arr;
    Node *temp = head;
    while (temp != NULL)
    {
        arr.push_back(temp->data);
        temp = temp->next;
    }
    int i = 0;
    int j = n - 1;
    while (i < j)
    {
        if (arr[i] != arr[j])
        {
            return false;
        }
        i++;
        j--;
    }
    return true;
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

// reverse the LL, from next of middle
Node *reverse(Node *head)
{
    Node *curr = head;
    Node *prev = NULL;
    Node *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }
    return prev;
}

// reverse LL after middle node and compare 1st and 2nd halves is equal
bool checkPalindrome_2(Node *head, int n)
{
    if (head->next == NULL)
    {
        return true;
    }
    Node *middle = getmiddle(head);
    Node *temp = middle->next;
    middle->next = reverse(temp); // head of reverse 2nd half LL

    Node *head1 = head;         // pointer to traverse 1st half
    Node *head2 = middle->next; // pointer to traverse 2nd half
    while (head2 != NULL)
    {
        if (head1->data != head2->data) // when two are unequal == not palindrome
        {
            // reverse changes made before returning false
            temp = middle->next;
            middle->next = reverse(temp);

            return false;
        }
        // else move both forward
        head1 = head1->next;
        head2 = head2->next;
    }
    // reverse 2nd half again to keep i/p LL same
    temp = middle->next;
    middle->next = reverse(temp);
    // came out of while loop == palindrom == return true
    return true;
}

int main()
{
    int arr[] = {3, 5, 1, 3, 3};
    int size = 5;
    Node *head = createLinkedList(arr, size);
    print(head);
    
    bool isPalindrome = checkPalindrome_2(head, size);
    cout << isPalindrome << endl;
    return 0;
}