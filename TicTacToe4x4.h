#ifndef TICTACTOE4X4_H
#define TICTACTOE4X4_H

#include <iostream>
#include <vector>
using namespace std;

class TicTacToe4x4
{
    vector<vector<char>> board;

public:
    TicTacToe4x4() : board(4, vector<char>(4, '.')) {}

    void displayBoard()
    {
        for (const auto& row : board)
        {
            for (char cell : row)
                cout << cell << " ";
            cout << endl;
        }
    }

    bool isMoveValid(int curRow, int curCol, int newRow, int newCol, char player)
    {
        if (curRow < 0 || curRow >= 4 || curCol < 0 || curCol >= 4 ||
            newRow < 0 || newRow >= 4 || newCol < 0 || newCol >= 4)
            return false;

        if (board[curRow][curCol] != player || board[newRow][newCol] != '.')
            return false;

        if (abs(newRow - curRow) + abs(newCol - curCol) != 1)
            return false;

        return true;
    }

    void makeMove(int curRow, int curCol, int newRow, int newCol, char player)
    {
        board[curRow][curCol] = '.';
        board[newRow][newCol] = player;
    }

    bool checkWin(char player)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j <= 1; ++j)
            {
                if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player)
                    return true;
            }
        }
        return false;
    }
};


#endif // TICTACTOE4X4_H
