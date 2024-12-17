#ifndef PYRAMICTICTACTOEBOARD_H
#define PYRAMICTICTACTOEBOARD_H
#include"BoardGame_Classes.h"

#include <ctime>


template <typename T>
class  PyramicTicTacToe_Board:public Board<T> {
public:
     PyramicTicTacToe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class   PyramicTicTacToe_Player : public Player<T> {
public:
      PyramicTicTacToe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class   PyramicTicTacToe_Random_Player : public RandomPlayer<T>{
public:
      PyramicTicTacToe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
template <typename T>
  PyramicTicTacToe_Board<T>::  PyramicTicTacToe_Board() {
    this->rows = 3;        // عدد الصفوف
    this->columns = 5;     // عدد الأعمدة
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // تهيئة كل الخلايا إلى القيمة الافتراضية (0)
        }
    }
    this->n_moves = 0; // تعيين عدد الحركات الأولية إلى 0
}

template <typename T>
bool   PyramicTicTacToe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}


template <typename T>
void   PyramicTicTacToe_Board<T>::display_board() {
      cout << "      | " << (this->board[0][0] != 0 ? this->board[0][0] : ' ') << " |   " << endl;
    cout << "   ____________ " << endl;


    cout << "   |";
    for (int j = 0; j < 3; j++) {
        cout << (this->board[1][j] != 0 ? this->board[1][j] : ' ');
        if (j < 3) cout << " | ";
    }
    cout << endl;
    cout << "___________________  " << endl;


    for (int j = 0; j < 5; j++) {
        cout << (this->board[2][j] != 0 ? this->board[2][j] : ' ');
        if (j < 5) cout << " | ";
    }
    cout << endl;
    cout << "" << endl;
}



    // Returns true if there is any winner
template <typename T>
bool   PyramicTicTacToe_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 1; i < this->rows; i++) {

    if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0)


return true;
        }


        if(( this->board[2][1]  == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != 0) ||
            (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != 0)) {
            return true;

            }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0)||

        (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != 0) ||
        (this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[0][0] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool   PyramicTicTacToe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool   PyramicTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for   PyramicTicTacToe_Player
template <typename T>
  PyramicTicTacToe_Player<T>::  PyramicTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void   PyramicTicTacToe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for   PyramicTicTacToe_Random_Player
template <typename T>
  PyramicTicTacToe_Random_Player<T>::  PyramicTicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void   PyramicTicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}












#endif //  PyramicTicTacToe_H
