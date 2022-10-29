#include <iostream>
#include <vector>
using namespace std;

// Funtion by Recursion
void digitRec(int num, string digit[])
{
    if (num == 0)
    {
        // Single digit/10 = 0; so all digits exhausted
        return;
    }
    // Recusrion call for next quotient 412-->41-->4-->4
    digitRec(num / 10, digit);
    // Print after recusion in return, for order-->
    // 4 % 10--> 41 % 10 --> 412 % 10
    // Four ---> One---> Two
    cout << digit[num % 10] << " ";
}

// Function by Recursion
void sayDigit(int n, string digit[])
{

    vector<int> ans; // Store digits in from right to left because %
    while (n > 0)
    {
        ans.push_back(n % 10);
        n = n / 10;
    }
    // print word for each digit in reveres order to get order same as original number
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        cout << digit[ans[i]] << " ";
    }
    cout << endl;
}

int main()
{
    int num;
    string digit[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};

    cout << "Enter number: ";
    cin >> num;
    // sayDigit(num, digit);
    digitRec(num, digit);
    cout << endl;
    return 0;
}