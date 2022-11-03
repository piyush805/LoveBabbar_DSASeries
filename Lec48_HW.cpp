#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

void print(Node *&head)
{
    Node *temp = head;
    Node *curr = head;
    while (temp->next != curr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << temp->data << " ";
    cout << endl;
}

int getLength(Node *&head)
{
    Node *temp = head;
    int count = 1;
    while (temp->next != head)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

Node *splitList(Node *&head, int count)
{

    Node *temp = head;
    // even number of nodes
    int val = 0;
    if (count % 2 == 0)
    {
        val = 1;
    }
    int count2 = val;
    while (count2 < count / 2)
    {

        temp = temp->next;
        count2++;
    }
    cout << "Second" << endl;
    // 2nd part LL
    Node *restPart = temp->next; // variable to traverse 2nd part till the end
    temp->next = head;           // make end of 1st, point to head to make it circular

    Node *restPartNode = restPart; // Store head of 2nd LL
    while (restPart->next != head)
    {
        restPart = restPart->next;
        cout<<restPart->data<<endl;
    }
    // reached the end pf LL
    restPart->next = restPartNode; // Last node point to head of 2nd LL
    return restPartNode;
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

    return head;
}

int main()
{
    int arr[] = {12, 31, 15, 1, 6, 9, 17};
    int size = 7;
    Node *head = createLinkedList(arr, size);
    print(head);

    int count = getLength(head);
    Node *restPart = splitList(head, count); // return head of 2nd LL
    print(head);                             // LL modified with its head same as head
    print(restPart);                         // 2nd LL head is at restPart

    return 0;
}