#include <iostream>
#include <stack>
using namespace std;
// Implenting stack using Linked List
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

class Stack
{
public:
    Node *head;
    Node *top;
    // Constructor
    Stack()
    {

        this->head = new Node(-1);
        this->top = head;
    }

    void push(int element)
    {
        // Stack never over flows
        Node *insert = new Node(element);
        top->next = insert;
        top = insert;
    }

    void pop()
    {
        if (head == top)
        {
            cout << "Stack underflow" << endl;
            return;
        }
        Node *temp = head;
        // traverse upto one before before top
        while (temp->next != top)
        {
            temp = temp->next;
        }
        // new top
        top = temp;
        temp->next = NULL;
    }

    void peek()
    {
        if (top == head)
        {
            cout << "Stack Empty" << endl;
            return;
        }
        cout << top->data << endl;
    }

    bool isEmpty()
    {
        if (top == head)
        {
            return true;
        }
        return false;
    }
};

// recusrive function to print values in stack from top towards head
void printStack(Node *head)
{
    if (head == NULL)
    {
        return;
    }
    printStack(head->next);
    cout << head->data << " ";
}
// Function to check if stack empty else call recursive print
void print(Stack st)
{
    if (st.isEmpty())
    {
        cout << "Stack Empty" << endl;
        return;
    }
    cout << "Stack: ->";
    printStack(st.head->next);
    cout << endl;
}
int main()
{
    // Implenting stack using Linked List
    Stack st; // initialised with dummy node -1
    st.push(5);
    st.push(6);
    st.push(7);
    st.push(8);

    print(st);

    st.pop(); // pop 8
    print(st);

    st.peek(); // top = 7

    st.pop(); // pop 7
    st.pop(); // pop 6
    print(st);

    st.pop();  // pop 5
    print(st); // empty

    st.peek(); // empty
    st.pop();  // underflow

    return 0;
}