#include <iostream>
#include <vector>
using namespace std;
// ================== BackTracking Day 2 || N Queens Problem =================
/*Placing N queens on NXN chess board so that no 2 queens attack each other
    -   Every row 1 queen
    -   Every Col 1 col
    -   No two queen attack each other(not on same diagonal)
*/
bool isSafe(int row, int col, vector<vector<int>> &board, int n)
{
    int x = row;
    int y = col;
    // check for row
    while (y >= 0)
    {
        // for this row, from this [col] to intialcol
        // check if any of the col cell is filled, the that queen can attack
        if (board[x][y] == 1)
        {
            return false; // cannot place here so return false
        }
        y--;
    }

    x = row;
    y = col;
    // From cell to NW direction, all cells be empty else queen can attack diagnonal downward
    while (x >= 0 && y >= 0)
    {
        // if any cell is filled, then cannot place in x,y
        if (board[x][y] == 1)
        {
            return false;
        }
        y--;
        x--;
    }

    x = row;
    y = col;
    // From cell to SW direction, all cells be empty else queen can attack diagnonal upward
    while (x < n && y >= 0)
    {
        // if any cell filled, then cannot place it here
        if (board[x][y] == 1)
        {
            return false;
        }
        y--;
        x++;
    }
    // if that row  && diagnoal 1 and diagonal 2 is safe then can place here, and we're going column by column itself so no need to check column
    return true;
}
void addSolutions(vector<vector<int>> &ans, vector<vector<int>> &board, int n)
{
   
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            temp.push_back(board[i][j]);//entire solution added to single vector<int>
        }
    }
    ans.push_back(temp); // posible solution added
}
/*
    From col 0 to col n, for each column check if a row cell is safe to place queen, and backtrack for other possibilities, until all rows of all column are done
*/
void solve(int col, vector<vector<int>> &ans, vector<vector<int>> &board, int n)
{
    if (col == n) // When column reaches end, => all queens placed, then this is a possible solution
    {
        addSolutions(ans, board, n);
        return;
    }
    // solve 1 case & rest recursion will take care
    for (int row = 0; row < n; row++)
    {
        if (isSafe(row, col, board, n)) // for a col, it is safe to place because no queen in that row and is safe along both diagonals from that x,y
        {
            board[row][col] = 1;           // place
            solve(col + 1, ans, board, n); // recursive call for next col
            board[row][col] = 0;           // back track
        }
    }
}
/*
Approach:
    -   For col 0 to n-1
    -       if issafe(no queen in same fow earlier, or any diagnoal)
    -           Place queen there
                Recursive call for next col
        if reached last column, this is one posible ans, so return
        backtrack steps  [ and check other possibilities for all the rows cell for each column]

Approach:- Checking issafe with while loop can be optimised using hashmaps, i.e. true or false for all cells using extra space <int, bool> for cells
    -   when a queen is place all not possible cells become false
    -   so when cell is true only place next queen there
*/
vector<vector<int>> nQueens(int n)
{
    vector<vector<int>> board(n, vector<int>(n, 0)); // initialisze entire board with zero, and a cell =1 when a queen is place and will be 0 again on backtracking from a solution
    vector<vector<int>> ans;
    int colStart = 0;
    solve(colStart, ans, board, n);
    return ans;
}
int main()
{
    int n = 4;
    vector<vector<int>> queens = nQueens(n);

    return 0;
}