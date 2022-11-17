#include <iostream>
#include <vector>
using namespace std;
// ================== BackTracking Day 1 || Rat in a maze =================

bool isSafe(int x, int y, vector<vector<int>> visited,
            vector<vector<int>> &m, int n)
{
    if ((x >= 0 && x < n) && (y >= 0 && y < n) && (visited[x][y] == 0) && (m[x][y] == 1))
    {
        // tile be within array & tile be not visited & tile be allowed to be visited
        return true;
    }
    else
    {
        return false;
    }
}

void solve(int x, int y, vector<vector<int>> &arr, int n, vector<string> &ans, vector<vector<int>> &vis, string path)
{
    if (x == n - 1 && y == n - 1)
    {
        // push this path string into ans when reached destination
        ans.push_back(path);
        return; // backtrack for the reamining paths ways
    }
    vis[x][y] = 1; // make current cell visited

    /*
    Enter the tile that first satisfies the contd and go into it, rest of paths from this tile will be checked in backtracking when retuning and marking each tile as unvisited*/
    // Down
    if (isSafe(x + 1, y, vis, arr, n))
    {
        solve(x + 1, y, arr, n, ans, vis, path + 'D');
    }
    // Left
    if (isSafe(x, y - 1, vis, arr, n))
    {
        solve(x, y - 1, arr, n, ans, vis, path + 'L');
    }
    // Right
    if (isSafe(x, y + 1, vis, arr, n))
    {
        solve(x, y + 1, arr, n, ans, vis, path + 'R');
    }
    // Up
    if (isSafe(x - 1, y, vis, arr, n))
    {
        solve(x - 1, y, arr, n, ans, vis, path + 'U');
    }
    vis[x][y] = 0;
}

vector<string> searchMaze(vector<vector<int>> &arr, int n)
{
    vector<string> ans;
    if(arr[0][0] == 0){
        return ans;
    }
    // visited array of the same size as 2D vector
    vector<vector<int>> visited(n, vector<int>(n, 0)); // bool or int
    string path = "";
    solve(0, 0, arr, n, ans, visited, path);
    return ans;
}
/*

TC = 4 ^(m  x n ) = O(4 ^(n^2))//4 movemnets possible for every block so 4 into no. of blocks
SC = O(m x n) = O(n^2);
*/
int main()
{
    // Create maze 2D vector
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

    vector<string> ans = searchMaze(m, n);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
}