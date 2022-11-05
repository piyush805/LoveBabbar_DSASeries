#include <iostream>
#include <stack>
using namespace std;

void printStack(stack<int> s)
{
    cout << "Stack-> ";
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "]" << endl;
}

// Function to find min no. brackets to be reversed to make bracket pairs valid
int findMinimumCost(string str)
{
    if (str.length() % 2 == 1)
    {
        // If odd length string then there can never be valid pairs
        return -1;
    }

    stack<char> s;
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        if (ch == '{')
        {
            s.push(ch); // push open parenthesis into stack
        }
        else
        {
            if (!s.empty() && s.top() == '{')
            {
                s.pop(); // balanced parenthesis popped out
            }
            else
            {
                s.push(ch); // unbalanced pushed
            }
        }
    }
    // Now with all balances pairs removed, stack only has unbalances ones
    int a = 0, b = 0; // a = count of '{', b = count of '}'
    while (!s.empty())
    {
        if (s.top() == '{')
        {
            b++; // count open brackets
        }
        else // close brackets
        {
            a++;
        }
        s.pop();
    }
    int ans = ((a + 1) / 2) + ((b + 1) / 2);
    return ans;
}

// Function to check any unnecessary redundant brackets in given mathematical expression
bool findRedundantBrackets(string &s)
{
    stack<int> st;
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        // push open bracket and operators into stack
        if (ch == '(' || ch == '+' || ch == '-' || ch == '/' || ch == '*')
        {
            st.push(ch);
        }
        else
        {
            // ignore other variables, when encounter a closing bracket, check if stack has operators until an open bracket
            // until an open bracket is found
            // check if next top is an operator(isRedundant = false) and pop it
            // if no operator and directly open bracket is present then it IS Redundant and return  true
            // NO redundant bracket until open bracket then pop it and move to next character in string
            if (ch == ')')
            {
                bool isRedundant = true; // flag to check if there is operator present between before matching open bracket of this pair
                while (st.top() != '(')
                {
                    char top = st.top();
                    // if after a close bracket, no operator is present before open bracket is found, then there is no operator between close and open, hence these are redundant
                    if (top == '+' || top == '-' || top == '/' || top == '*')
                    {
                        isRedundant = false;
                    }
                    st.pop(); // keep popping until open bracket found
                }
                // check if there was redundant bracket then no checking further
                if (isRedundant == true)
                {
                    return true;
                }
                st.pop(); // pop the '(' if pair was not redundant and check further
            }
        }
    }
    // no redundant until end of expression
    return false;
}

// Function to push an element to place where it fits
void sortedInsert(stack<int> &stack, int num)
{
    if (stack.empty() || (stack.top() < num))
    {
        // push element when it fits at top of the stack and for each call, rest of the stack will already be sorted, so we check one by one each time by popping does the element fits at top now
        // stack may become emoty in the process and hence element was smallest element
        stack.push(num);
        return;
    }

    int n = stack.top();
    stack.pop();

    sortedInsert(stack, num);
    stack.push(n);
}
// Function to sort stack using recursion
void sortStack(stack<int> &stack)
{
    if (stack.empty())
    {
        return;
    }
    int num = stack.top();
    stack.pop();

    sortStack(stack);
    // stack emptied then, in return, push each element where it fits
    sortedInsert(stack, num);
}

// Function to push element x at bottom of given stack
void pushAtBottom(stack<int> &s, int x)
{
    if (s.empty())
    {
        // when stack becomes empty push this element so it is at the bottom
        s.push(x);
        return;
    }
    // store element at top for pushing at return of recursive call
    int num = s.top();
    s.pop();
    // stack with one less element in the next
    pushAtBottom(s, x);
    // stack returned with x at bottom, push now element which was removed and stored before call
    s.push(num);
}

// Function to reverse elements in stack using pushAtBottom function
void reverseStack(stack<int> &stack)
{
    // Logic: empty the stack and push subsequent elements to the bottom in reverse order of pop
    if (stack.empty())
    {
        // empty the stack
        return;
    }
    int num = stack.top();
    stack.pop();
    reverseStack(stack);
    // last item pushed to bottom, then 2nd last item pushed to bottom, then third and so on...at last 1st element that was removed gets pushed at the bottom
    pushAtBottom(stack, num);
}

// Function to verify ({[]}) are balanced in an only bracket expression
bool isValidParenthesis(string expression)
{
    // Write your code here.
    stack<char> s;
    for (int i = 0; i < expression.length(); i++)
    {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[')
        {
            s.push(ch);
        }
        else
        {
            if (!s.empty())
            {
                char top = s.top();
                if ((ch == ')' && top == '(') || (ch == '}' && top == '{') || (ch == ']' && top == '['))
                {
                    s.pop();
                }
                else
                {
                    // if bracket not matching
                    return false;
                }
            }
            else
            {
                // is stack found empty
                return false;
            }
        }
    }
    // stack empty at the end of expression
    if (s.empty())
    {
        return true;
    }
    return false;
}

// Function to delete middle element of given stack of size N
void deleteMiddle(stack<int> &s, int count, int size)
{
    if (count == size / 2)
    {
        s.pop();
        return;
    }
    int num = s.top();
    s.pop();
    deleteMiddle(s, count + 1, size);
    s.push(num);
}

// Function to reverse a string using stack
string reverseString(string str)
{
    stack<char> s;
    for (int i = 0; i < str.length(); i++)
    {
        s.push(str[i]);
    }
    string output = "";
    while (!s.empty())
    {
        output.push_back(s.top());
        s.pop();
    }
    return output;
}

int main()
{
    // string input;
    // cout << "Enter string: ";
    // cin >> input;
    // cout << "Reversed String: " << reverseString(input) << endl;

    stack<int> s;
    s.push(5);
    s.push(4);
    s.push(2);
    s.push(3);
    s.push(1);
    s.push(3);
    s.push(2);
    printStack(s);
    // deleteMiddle(s, 0, 7);
    // pushAtBottom(s, 15);
    sortStack(s);
    printStack(s);

    cout << "Enter bracket expression: ";
    string exp;
    cin >> exp;
    // cout << isValidParenthesis(exp) << endl;
    // cout << findRedundantBrackets(exp) << endl;
    cout << findMinimumCost(exp) << endl;

    return 0;
}