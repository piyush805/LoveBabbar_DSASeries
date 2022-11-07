#include <bits/stdc++.h>
using namespace std;

void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

class NStack
{
public:
    // Initialize your data structure.
    int *arr;  // where stack values goes
    int *top;  // n size array keeps track of tops of each stack- o indexed
    int *next; // keeps tracking of next freespot after each index in pushing and gets updated with freespot when popping
    int n, s;  // n = number of stacks to be implements
    // s = size of array in which n stacks to be implemented
    int freespot;
    NStack(int N, int S)
    {
        n = N;
        s = S;
        arr = new int[s];
        top = new int[n]; // n tops for n stacks
        next = new int[s];
        // top initialize
        for (int i = 0; i < n; i++)
        {
            top[i] = -1;
        }
        // stores values of next free slot after each index
        for (int i = 0; i < s; i++)
        {
            next[i] = i + 1;
        }
        // last inddex of mext = -1 indicating, array stack is full and there is no more space
        next[s - 1] = -1;

        // to indicate where is next free slot or where to go to next[] when a new element comes to be pushed
        freespot = 0;
        cout << "Top:";
        print(top, n);
        cout << "Next: ";
        print(next, s);
        cout << "freespot: " << freespot << endl;
    }

    // Pushes 'X' into the Mth stack. Returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x, int m)
    {
        if (freespot == -1) // freeslot gets updated from next so when next indidicates that array becaomes full in last time then freespot must have been updated to caontain -1
        // Hence check whether stack is full
        { // check overflow
            return false;
        }
        // new element will go to this freeslot
        int index = freespot;

        // next[index] contains info of next freespot afte this index, so update new freespot by referring to next[]
        freespot = next[index];
        // insert element into array stack at this index
        arr[index] = x;
        // after pushing next[index] contains info of where top of array was before push, so that in pop() we can backtrack
        next[index] = top[m - 1];
        // now that new element is pushed top for this [mth 0 indexed] stack gets updated
        top[m - 1] = index;
        cout << "Arr: ";
        print(arr, s);
        cout << "Top:";
        print(top, n);
        cout << "Next: ";
        print(next, s);
        cout << "freespot: " << freespot << endl;
        return true;
    }

    // Pops top element from Mth Stack. Returns -1 if the stack is empty, otherwise returns the popped element.
    int pop(int m)
    {

        if (top[m - 1] == -1)
        {
            // whether top of this mth stack contains -1=> this stack empty
            return -1;
        }
        // where top indicates is where pop will happen
        int index = top[m - 1];
        // top goes one position down, next[index] contains where top was previosly when this push() occured, so now it can be referred to go back to the positon top was at before this element was pushed
        top[m - 1] = next[index];
        // freepot that was to be used for freespot is the freeslot that's available when this element is there, so that will be freespot when element is pushed into this index again
        next[index] = freespot;
        // this index becomes new freespot in array stack, to be used in next push
        freespot = index;
        // return the element popped
        cout << "Arr: ";
        print(arr, s);
        cout << "Top:";
        print(top, n);
        cout << "Next: ";
        print(next, s);
        cout << "freespot: " << freespot << endl;
        return arr[index]; // values remains intect, just all next and top and freespot gets updates such that it can be overwritten in next push elements
    }
};

int main()
{
    NStack s(3, 6);
    s.push(10, 1);                          // 10 XX XX XX XX XX
    s.push(30, 1);                          // 10 30 XX XX XX XX
    s.push(20, 2);                          // 10 30 20 XX XX XX
    cout << "Popped: " << s.pop(1) << endl; // 10 30 20 XX XX XX
    s.push(45, 2);                          // 10 45 20 XX XX XX
    cout << "Popped: " << s.pop(2) << endl; // 10 45 20 XX XX XX
    s.push(35, 2);                          // 10 35 20 XX XX XX
    s.push(45, 1);                          // 10 35 20 45 XX XX
    // Stack 1 [10 45<--
    // Stack 2 [20 45<--
    // Stack 3 [<--
    return 0;
}