#include <iostream>
#include "PyramicTicTacToeBoard.h"
#include "WordTicTacToeBoard.h"
#include "UltimateTicTacToe.h"
#include "BoardGame_Classes.h"
#include <vector>
#include "TicTacToe4x4.h"
#include "FourInARow.h"
#include "NumericalBoard.h"
using namespace std;
void display_menu() {
    cout << "----------------------------------\n";
    cout << "      Welcome to the Game Center    \n";
    cout << "----------------------------------\n";
    cout << "1. Play Pyramic Tic-Tac-Toe\n";
    cout << "2. Play Ultimate Tic-Tac-Toe\n";
    cout << "3. Play Word Tic-Tac-Toe\n";
    cout << "4. Play Four-in-a-Row\n";
    cout << "5. Play Numerical Tic-Tac-Toe\n";
    cout << "6. Play 4x4 Tic-Tac-Toe\n";
    cout << "7. Exit\n";
    cout << "Please choose an option (1-7): ";
}

int main() {
    int choice;

    while (true) {
        display_menu();
        cin >> choice;

        switch (choice) {
        case 1: {
            // اللعبة رقم 1: Pyramic Tic-Tac-Toe
            Player<char>* players[2];
            PyramicTicTacToe_Board<char>* B = new PyramicTicTacToe_Board<char>();
            string playerXName, playerOName;

            cout << "Enter Player X name: ";
            cin >> playerXName;
            players[0] = new PyramicTicTacToe_Player<char>(playerXName, 'X');

            cout << "Enter Player O name: ";
            cin >> playerOName;
            players[1] = new PyramicTicTacToe_Player<char>(playerOName, 'O');

            GameManager<char> game(B, players);
            game.run();

            delete B;
            delete players[0];
            delete players[1];
            break;
        }
        case 2: {
            // اللعبة رقم 2: Ultimate Tic-Tac-Toe
            UltimateBoard<char> mainBoard;
            UltimatePlayer<char> player1("Player 1", 'X');
            UltimatePlayer<char> player2("Player 2", 'O');
            Player<char>* players[2] = { &player1, &player2 };

            GameManager<char> gameManager(&mainBoard, players);
            gameManager.run();
            break;
        }
        case 3: {
            // اللعبة رقم 3: Word Tic-Tac-Toe
            Player<char>* players[2];
            WordTicTacToeBoard<char>* B = new WordTicTacToeBoard<char>();
            B->load_valid_words();
            string playerXName, playerOName;

            cout << "Enter Player 1 name: ";
            cin >> playerXName;
            players[0] = new WordTicTacToePlayer<char>(playerXName, 'X');

            cout << "Enter Player 2 name: ";
            cin >> playerOName;
            players[1] = new WordTicTacToePlayer<char>(playerOName, 'O');

            GameManager<char> wordGame(B, players);
            wordGame.run();

            delete B;
            delete players[0];
            delete players[1];
            break;
        }
        case 4: {
            // اللعبة رقم 4: Four-in-a-Row
            FourInARow game;
            char players[] = {'X', 'O'};
            int turn = 0, col;

            while (true) {
                game.displayBoard();
                cout << "Player " << players[turn % 2] << ", enter column (0-6): ";
                cin >> col;

                if (game.dropPiece(col, players[turn % 2])) {
                    if (game.checkWin(players[turn % 2])) {
                        game.displayBoard();
                        cout << "Player " << players[turn % 2] << " wins!\n";
                        break;
                    }
                    turn++;
                } else {
                    cout << "Invalid move. Try again.\n";
                }
            }
            break;
        }
        case 5: {
            // اللعبة رقم 5: Numerical Tic-Tac-Toe
            NumericalBoard game;
            int num, row, col, turn = 0;
            cout << "Numerical Tic-Tac-Toe\n";

            while (true) {
                game.display();
                cout << "Enter number, row, column: ";
                cin >> num >> row >> col;

                if (game.placeNumber(row, col, num, turn % 2)) {
                    if (game.checkWin()) {
                        game.display();
                        cout << "Player " << (turn % 2 == 0 ? 1 : 2) << " wins!\n";
                        break;
                    }
                    turn++;
                } else {
                    cout << "Invalid move. Try again.\n";
                }
            }
            break;
        }
        case 6: {
            // اللعبة رقم 6: 4x4 Tic-Tac-Toe
            TicTacToe4x4 game;
            int curRow, curCol, newRow, newCol, turn = 0;
            char players[] = {'X', 'O'};

            while (true) {
                game.displayBoard();
                cout << "Player " << players[turn % 2] << ", move (current row col new row col): ";
                cin >> curRow >> curCol >> newRow >> newCol;

                if (game.isMoveValid(curRow, curCol, newRow, newCol, players[turn % 2])) {
                    game.makeMove(curRow, curCol, newRow, newCol, players[turn % 2]);
                    if (game.checkWin(players[turn % 2])) {
                        game.displayBoard();
                        cout << "Player " << players[turn % 2] << " wins!\n";
                        break;
                    }
                    turn++;
                } else {
                    cout << "Invalid move. Try again.\n";
                }
            }
            break;
        }
        case 7:
            cout << "Exiting the Game Center. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}
