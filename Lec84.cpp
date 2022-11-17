#include <iostream>
#include <vector>
using namespace std;
// ================== BackTracking Day 3 || Sudoku Problem Solver =================
/*
    -   A number exactly once in a row
    -   A number excatly once in column
    -   A number exactly once in a 3x3 grid
TC: 9^m
SC: O(1)

*/
bool isSafe(int row, int col, vector<vector<int>> &board, int val)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (board[row][i] == val) // this val should not be in entire row
        {
            return false;
        }
        if (board[i][col] == val) // this value should not be in entire col
        {
            return false;
        }
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == val) // 3x3 grid check
        {
            return false;
        }
    }
    return true;
}

bool solve(vector<vector<int>> &board)
{
    int n = board.size();
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board[row][col] == 0) // for this empty cell
            {
                for (int val = 1; val <= 9; val++) // try each number
                {
                    if (isSafe(row, col, board, val)) // Does this value fit here?
                    {
                        board[row][col] = val;        // if safe to insert, insert
                        bool solution = solve(board); // recursive call until all cells filled,
                        // if fills entire then
                        if (solution)
                        {
                            // true follows the backtrack chain
                            return true;
                        }
                        else
                        {

                            board[row][col] = 0;
                        }
                    }
                }
                return false; // if any of 1-9 not possible, then value of bool solutuion is false, and it backtracks with fillin in previous filled cells
            }
        }
    }
    // this true returned when last recursive call is successful in filling last value thus filling enrire board, thus it returns true in the backtrack in all values of bool solution
    // else
    return true;
}

void solveSudoku(vector<vector<int>> &sudoku)
{
    solve(sudoku);
}
/*
    For (i 0 to 9)
        For (j 0 to 9)
            if cell empty
                for num 1 to 9
                    if possible
                        board[i][j] = num
            else
                not possible- backtrack
                board[i][j] = 0
*/
int main()
{
    return 0;
}