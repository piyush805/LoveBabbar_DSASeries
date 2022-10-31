#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int x, int y, int n, vector<vector<int>> visited,
            vector<vector<int>> &m)
{
    if ((x >= 0 && x < n) && (y >= 0 && y < n) && (visited[x][y] == 0) && (m[x][y] == 1))
    {
        //tile be within array, tile be not visited, tile be allowed to be visited 
        return true;
    }
    else
    {
        return false;
    }
}

void solve(vector<vector<int>> &m, int n, vector<string> &ans,
           int x, int y, vector<vector<int>> visited, string &path)
{
    
    if (x == n - 1 && y == n - 1)
    {
        //reached destination, store the path so far
        ans.push_back(path);
        return;
    }
    // mark this x,y as visited
    visited[x][y] = 1;
    
    // down
    int newx = x + 1;
    int newy = y;
    if (isSafe(newx, newy, n, visited, m))
    {
        path.push_back('D');
        solve(m, n, ans, newx, newy, visited, path);
        path.pop_back();//backtrack
    }
    
    // left
    newx = x;
    newy = y - 1;
    if (isSafe(newx, newy, n, visited, m))
    {
        path.push_back('L');
        solve(m, n, ans, newx, newy, visited, path);
        path.pop_back();//backtrack
    }
    
    // right
    newx = x;
    newy = y + 1;
    if (isSafe(newx, newy, n, visited, m))
    {
        path.push_back('R');
        solve(m, n, ans, newx, newy, visited, path);
        path.pop_back();//backtrack
    }

    // up
    newx = x - 1;
    newy = y;
    if (isSafe(newx, newy, n, visited, m))
    {
        path.push_back('U');
        solve(m, n, ans, newx, newy, visited, path);
        path.pop_back();//backtrack
    }
    
    visited[x][y] = 0; // make visited 0 as we track back
}

vector<string> findPath(vector<vector<int>> &m, int n)
{
    // Your code goes here

    vector<string> ans;
    if (m[0][0] == 0)//if first tile itself not allowed to ve visited
    {
        return ans;
    }
    int srcx = 0;
    int srcy = 0;
    vector<vector<int>> visited = m;
    //make visited array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = 0;
        }
    }

    string path = "";//all paths to store
    solve(m, n, ans, srcx, srcy, visited, path);

    sort(ans.begin(), ans.end());

    return ans;
}

int main()
{

    vector<int> m1 = {1, 0, 0, 0};
    vector<int> m2 = {1, 1, 0, 1};
    vector<int> m3 = {1, 1, 0, 0};
    vector<int> m4 = {0, 1, 1, 1};
    vector<vector<int>> m;
    m.push_back(m1);
    m.push_back(m2);
    m.push_back(m3);
    m.push_back(m4);

    int n = 4;
    vector<string> ans = findPath(m, n);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}