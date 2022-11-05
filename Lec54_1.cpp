#include <iostream>
#include <stack>
using namespace std;

class Stack
{
public:
    int *arr, top, size;
    // Constructor
    Stack(int size)
    {
        this->size = size;
        arr = new int[size];
        top = -1;
    }
    void push(int element)
    {
        if (size - top > 1)
        {
            top++;
            arr[top] = element;
            return;
        }
        cout << "Stack overflow" << endl;
    }

    void pop()
    {
        if (top == -1)
        {
            cout << "Stack underflow" << endl;
            return;
        }
        top--;
    }
    // see top value of stack
    void peek()
    {
        if (top == -1)
        {
            cout << "Stack empty" << endl;
            return;
        }
        cout << arr[top] << endl;
    }

    bool isEmpty()
    {
        if (top == -1)
        {
            return true;
        }
        return false;
    }
    void print(Stack s)
    {
        
        
        while (!s.isEmpty())
        {
            s.peek();
            s.pop();
        }
        cout <<endl;
    }
};

void printStack(stack<int> s)
{
    cout << "...";
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "]" << endl;
}

void stackUsingSTL()
{
    stack<int> stack;
    stack.push(21);
    stack.push(22);
    stack.push(25);
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    printStack(stack);
}
int main()
{
    // stackUsingSTL();

    // Implenting stack using Array
    Stack st(5);
    st.push(21);
    st.push(22);
    st.push(25);
    st.peek();
    // st.pop();
    // st.peek();
    cout<<"Stack: "<<endl;
    st.print(st);



    return 0;
}