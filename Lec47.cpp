#include <iostream>
#include <map>
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

// loop present if encountered a visited node while traversing till end
// Works to only detect loop in single LL and not detect cirucular LL
bool detectLoop(Node *head)
{
    if (head == NULL)
    {
        // no loops in empty list
        return false;
    }
    map<Node *, bool> visited;
    Node *temp = head;
    while (temp != NULL)
    {
        if (visited[temp] == true)
        { // if visited node encountered in singly then loop present
            return true;
        }
        visited[temp] = true;
        temp = temp->next;
    }
    return false; // no visited node was encountered
}

// Return intersection of 2 pointers inside loop if loop present else NULL
Node *floydDetectionLoop(Node *head)
{
    if (head == NULL)
    {
        return head;
    }
    // 2 pointer approach
    Node *slow = head;
    Node *fast = head;
    while (slow != NULL && fast->next != NULL)
    {
        fast = fast->next;
        if (fast->next != NULL)
        {
            // fast + 2;
            fast = fast->next;
        }
        // slow + 1;
        slow = slow->next;
        if (slow == fast)
        { // if fast and slow pointer ever cross then loop is present
            return slow;
        }
    }
    // end of loop was reached without crossing
    return NULL;
}

// Find starting node of loop using intersection of 2 pointers inside the loop
Node *getStartingNode(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    // intersection of two pointers inside loop
    Node *intersection = floydDetectionLoop(head);
    if (intersection == NULL)
    {
        // if no loop present then no point detecting starting node of loop
        return NULL;
    }
    Node *slow = head;
    // start moving slow pointer from head and intersection pointer inside loop at same pace
    // they will intersection at the starting point of the loop: Mathematically
    while (slow != intersection)
    {
        slow = slow->next;
        intersection = intersection->next;
    }
    // when they meet return either intersection or slow
    return slow;
}
// Function to remove loop once starting node of loop is found
Node *removeLoop(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    // get starting node of loop
    Node *startOfLoop = getStartingNode(head);
    if(startOfLoop== NULL){
        //if no loop present, then simply return head
        return head;
    }
    Node *temp = startOfLoop;
    // traverse inside loop until loop complete
    while (temp->next != startOfLoop)
    {
        temp = temp->next;
    }
    // when temp reaches to previous of startpoint: make that pointer null
    // thus loop removes and LL becomes straight singly LL
    temp->next = NULL;
    // head of LL
    return head;
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
        previous = previous->next;
        i++;
    }
    previous->next = NULL;
    return head;
}

// Traversing and printing elements
// If loop is present this will go on infinite because no NULL encountered
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

// create loop in singly LL, where end connect to node temp in given LL
void createLoop(Node *head, int x)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }
    // store node to which end has to be connected
    Node *temp = head->next;
    Node *connect = head;
    while (temp->next != NULL)
    {
        if (temp->data == x) // find and store where node will point to
        {
            connect = temp;
        }
        temp = temp->next;
    }
    // when reach last node, point it to loop node
    temp->next = connect;
}


int main()
{
    int arr[5] = {1, 4, 3, 6, 2};
    int size = 5;
    Node *head = createLinkedList(arr, size);
    print(head);

    int x = 1;
    createLoop(head, x);
    // Print gives infinite loop: thats how we know loop is present
    
    removeLoop(head);
    print(head); // print successfully like intiial so we know loop has been removed

    return 0;
}
