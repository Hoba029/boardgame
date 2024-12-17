#ifndef NUMERICALBOARD_H
#define NUMERICALBOARD_H


   #include <iostream>
#include <vector>
#include <string>
using namespace std;

class NumericalBoard
{
    vector<vector<int>> board;
    vector<bool> usedNumbers;

public:
    NumericalBoard() : board(3, vector<int>(3, 0)), usedNumbers(10, false) {}

    void display()
    {
        for (const auto& row : board)
        {
            for (int cell : row)
                cout << (cell ? to_string(cell) : ".") << ' ';
            cout << endl;
        }
    }

    bool placeNumber(int r, int c, int number, int player)
    {
        if (r < 0 || r >= 3 || c < 0 || c >= 3 || board[r][c] != 0 || usedNumbers[number])
            return false;

        if ((player == 0 && number % 2 == 0) || (player == 1 && number % 2 != 1))
        {
            return false;
        }

        board[r][c] = number;
        usedNumbers[number] = true;
        return true;
    }

    bool checkWin()
    {
        for (int i = 0; i < 3; ++i)
        {
            if (sumRow(i) == 15 || sumCol(i) == 15)
                return true;
        }
        return sumDiag() == 15 || sumAntiDiag() == 15;
    }

private:
    int sumRow(int r) { return board[r][0] + board[r][1] + board[r][2]; }
    int sumCol(int c) { return board[0][c] + board[1][c] + board[2][c]; }
    int sumDiag() { return board[0][0] + board[1][1] + board[2][2]; }
    int sumAntiDiag() { return board[0][2] + board[1][1] + board[2][0]; }
};


#endif // NUMERICALBOARD_H
