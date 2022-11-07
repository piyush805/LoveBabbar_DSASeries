#include <iostream>
#include <stack>
#include <vector>
using namespace std;
//========================== Stack Celebrity Problem =====================================

int celebrity(vector<vector<int>> &M, int n)
{
    stack<int> s;
    // Push all elements
    for (int i = 0; i < n; i++)
    {
        s.push(i);
    }
    // until size 1, pop 2 elements
    while (s.size() > 1)
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        // check if anyone knows anyone else
        if (M[a][b] == 1) // A knows B(a maybe regular, B celebrity)
        {
            s.push(b);
        }
        else // A does not know B (a maybe celebrity, b regular)
        {
            s.push(a);
        }
    }
    // potential candidate
    int ans = s.top();

    // rowCheck = true means he does not know anyone
    bool rowCheck = false;
    int zeroCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (M[ans][i] == 0) // he doesnt know ith in row
        {
            zeroCount++;
        }
    }
    if (zeroCount == n) // he doesnt know anyone
    {
        rowCheck = true;
    }

    // colCheck = true means everyone Knows him
    bool colCheck = false;
    int oneCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (M[i][ans] == 1) // ith  person knows him
        {
            oneCount++;
        }
    }
    if (oneCount == n - 1) // all know him(obviously he knows him so n-1 count only)
    {
        colCheck = true;
    }
    // Both true == he doesnot know anyone && everyone knows him
    if (rowCheck && colCheck)
    {
        return ans; // is a celebrity
    }
    else
    {
        return -1;
    }
}



int main()
{
    vector<int> v1{0, 1, 0};
    vector<int> v2{0, 0, 0};
    vector<int> v3{0, 1, 0};
    vector<vector<int>> M;
    M.push_back(v1);
    M.push_back(v2);
    M.push_back(v3);
    int n = 3;
    cout << "Celebrity index: " << celebrity(M, n) << endl;
    return 0;
}