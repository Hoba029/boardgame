#ifndef FOURINAROW_H
#define FOURINAROW_H

#include <iostream>
#include <vector>
using namespace std;

class FourInARow
{
    vector<vector<char>> board;

public:
    FourInARow() : board(6, vector<char>(7, '.')) {}

    void displayBoard()
    {
        for (const auto& row : board)
        {
            for (char cell : row)
                cout << cell << " ";
            cout << endl;
        }
        cout << "0 1 2 3 4 5 6\n";
    }

    bool dropPiece(int col, char player)
    {
        if (col < 0 || col >= 7 || board[0][col] != '.')
            return false;

        for (int i = 5; i >= 0; --i)
        {
            if (board[i][col] == '.')
            {
                board[i][col] = player;
                return true;
            }
        }
        return false;
    }

    bool checkWin(char player)
    {
        for (int r = 0; r < 6; ++r)
        {
            for (int c = 0; c < 7; ++c)
            {
                if (c + 3 < 7 && board[r][c] == player && board[r][c + 1] == player &&
                    board[r][c + 2] == player && board[r][c + 3] == player)
                    return true;

                if (r + 3 < 6 && board[r][c] == player && board[r + 1][c] == player &&
                    board[r + 2][c] == player && board[r + 3][c] == player)
                    return true;

                if (r + 3 < 6 && c + 3 < 7 && board[r][c] == player && board[r + 1][c + 1] == player &&
                    board[r + 2][c + 2] == player && board[r + 3][c + 3] == player)
                    return true;

                if (r + 3 < 6 && c - 3 >= 0 && board[r][c] == player && board[r + 1][c - 1] == player &&
                    board[r + 2][c - 2] == player && board[r + 3][c - 3] == player)
                    return true;
            }
        }
        return false;
    }
};



#endif // FOURINAROW_H
