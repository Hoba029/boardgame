#ifndef WORDTICTACTOEBOARD_H
#define WORDTICTACTOEBOARD_H
#include <unordered_set>
#include <fstream>


template <typename T>
class WordTicTacToeBoard : public Board<T> {
private:
    std::unordered_set<std::string> validWords;

public:
    WordTicTacToeBoard();
    void load_valid_words();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};


template <typename T>
class WordTicTacToePlayer : public Player<T> {
public:
    WordTicTacToePlayer(std::string name, T symbol);
    void getmove(int& x, int& y);
};


template <typename T>
class WordTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    WordTicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <cstdlib>  // for rand()

using namespace std;

template <typename T>
WordTicTacToeBoard<T>::WordTicTacToeBoard() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


template <typename T>
void WordTicTacToeBoard<T>::load_valid_words() {
    ifstream file("dic.txt");
    string word;
    while (file >> word) {
        if (word.size() == 3) {
            validWords.insert(word);
        }
    }
}

// تحديث اللوحة
template <typename T>
bool WordTicTacToeBoard<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
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

// عرض اللوحة
template <typename T>
void WordTicTacToeBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// التحقق من الفوز إذا كانت هناك كلمة صحيحة
template <typename T>
bool WordTicTacToeBoard<T>::is_win() {
    // التحقق من الصفوف والأعمدة
    for (int i = 0; i < this->rows; i++) {
        string row = "";
        for (int j = 0; j < this->columns; j++) {
            row += this->board[i][j];
        }
        if (validWords.find(row) != validWords.end()) return true;

        string col = "";
        for (int j = 0; j < this->rows; j++) {
            col += this->board[j][i];
        }
        if (validWords.find(col) != validWords.end()) return true;
    }

    // التحقق من الأقطار
    string diagonal1 = "", diagonal2 = "";
    for (int i = 0; i < this->rows; i++) {
        diagonal1 += this->board[i][i];
        diagonal2 += this->board[i][this->rows - i - 1];
    }
    if (validWords.find(diagonal1) != validWords.end()) return true;
    if (validWords.find(diagonal2) != validWords.end()) return true;

    return false;
}

// التحقق من التعادل
template <typename T>
bool WordTicTacToeBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WordTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// الكلاس الخاص باللاعب
template <typename T>
WordTicTacToePlayer<T>::WordTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void WordTicTacToePlayer<T>::getmove(int& x, int& y) {
    bool validMove = false;
    while (!validMove) {
        cout << "\nPlease enter your move (coordinates x and y, separated by space): ";
        cin >> x >> y;

        // التحقق من صحة الإحداثيات
        if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
            cout << "Now, please enter the letter you want to place at (" << x << "," << y << "): ";
            char letter;
            cin >> letter;

            // التحقق من أن الحرف هو حرف أبجدي
            if (isalpha(letter)) {
                this->symbol = toupper(letter);  // تعيين الحرف
                validMove = true;
            } else {
                cout << "Invalid letter! Please enter a valid letter (A-Z).\n";
            }
        } else {
            cout << "Invalid coordinates! Please enter coordinates between 0 and 2.\n";
        }
    }
}

// الكلاس الخاص باللاعب العشوائي
template <typename T>
WordTicTacToeRandomPlayer<T>::WordTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void WordTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

    // اختيار حرف عشوائي من الحروف الأبجدية
    char randomChar = 'A' + rand() % 26;  // Random letter between A and Z
    this->symbol = randomChar;
    cout << "Random move chosen: " << this->symbol << " at (" << x << ", " << y << ")\n";


};

#endif // WORDTICTACTOEBOARD_H
