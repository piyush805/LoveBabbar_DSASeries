#include <iostream>
#include <vector>
using namespace std;

void solvePhoneKey(string digits, string output, int index, vector<string> &ans, string mapping[])
{
    // Base case atleast one mapping of last digit over, then index+1 makes it go out the digits string
    if (index >= digits.length())
    {
        // output combination formed so far is one of the combination
        ans.push_back(output);
        return;
    }

    int number = digits[index] - '0'; // get the number from char to int
    string value = mapping[number];   // get string mapping for this int
    // for each alphabet mapping for this int
    for (int i = 0; i < value.length(); i++)
    {
        output.push_back(value[i]);                             // add current alphabet into the string
        solvePhoneKey(digits, output, index + 1, ans, mapping); //

        output.pop_back(); // backtracking: pop current so that in next turn with a new previous, all next combinations can be formed
        // if no backtracking then for example:
        // digits = "23"
        // 2-->"abc", 3-->"def"
        // first output becomes "a" then "ad" then index > digit length
        // on return output is "ad" and without pop_back(), d will not be removed and "e" will be added to this output making "ade", which correctly should be "ad" so on return remove the last added character before going for the next
        // Similarly after "ad","ae","af" are done, out will be "a", we want empty sting before adding "b": so pop_back() removes 'a'
    }
}

vector<string> phoneKeyPad(string digits)
{
    vector<string> ans; // store combinations
    string output;      // each combination to be stored
    int index = 0;      // traverse digit string
    string mapping[] = {"",
                        "",
                        "abc",
                        "def",
                        "ghi",
                        "jkl",
                        "mno",
                        "pqrs",
                        "tuv",
                        "wxyz"};
    solvePhoneKey(digits, output, index, ans, mapping);

    // Print ans vector
    // for (int i = 0; i < ans.size(); i++)
    // {
        
    //     for (int j = 0; j < ans[i].length(); j++)
    //     {
    //         cout << ans[i][j];
    //     }
    //     cout << ", ";
    // }
    // cout<<endl;
    return ans;
}

int main()
{
    vector<string> str = phoneKeyPad("89");
    return 0;
}