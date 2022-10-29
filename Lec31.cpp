#include <iostream>
using namespace std;
// Factorial by Recursion
long long int factorial(int num)
{
    if (num == 0)
    {
        return 1;
    }
    return num * factorial(num - 1);
}

// Print count in ascending
void countingAsc(int num)
{
    if (num == 0)
    {
        return;
    }
    //Call recusrion upto 1 first then print on return least to first number calling recusrion i.e. 6
    countingAsc(num - 1);
    cout << num << " ";
}
// Print count in descending
void countingDsc(int num)
{
    if (num == 0)
    {
        return;
    }
    //Print the number first and then call the recusion for next lesser number
    cout << num << " ";
    countingDsc(num - 1);
    
    
}
int main()
{
    // int num;
    // cout << "Enter the number to find factroial of: ";
    // cin >> num;
    // cout << "The factorial of the number is " << factorial(num) << endl;

    countingAsc(6);
    cout<<endl;
    countingDsc(6);
    cout<<endl;
    return 0;
}
