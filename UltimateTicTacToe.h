#ifndef ULTIMATETICTACTOE_H
#define ULTIMATETICTACTOE_H

template <typename T>
class SmallBoard : public Board<T> {
public:
    SmallBoard() {
        this->rows = this->columns = 3;
        this->board = new T*[3];
        for (int i = 0; i < 3; i++)
            this->board[i] = new T[3]();
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && this->board[x][y] == 0) {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << (this->board[i][j] ? this->board[i][j] : '-') << " ";
            }
            cout << endl;
        }
    }

    void display_board_row(int row) {
        for (int col = 0; col < 3; col++) {
            cout << (this->board[row][col] ? this->board[row][col] : '-') << " ";
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; i++) {
            if (this->board[i][0] && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2])
                return true;
            if (this->board[0][i] && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i])
                return true;
        }
        if (this->board[0][0] && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2])
            return true;
        if (this->board[0][2] && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0])
            return true;

        return false;
    }

    bool is_draw() override {
        return this->n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class UltimateBoard : public Board<T> {
private:
    SmallBoard<T>* boards[3][3]; // شبكة 3x3 من الألواح الصغيرة
    int currentBoardX = -1, currentBoardY = -1;  // تحديد اللوحة الصغيرة الحالية

public:
    UltimateBoard() {
        this->rows = this->columns = 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                boards[i][j] = new SmallBoard<T>();
    }

    bool update_board(int x, int y, T symbol) override {
        // إذا كانت اللوحة الكبيرة غير محددة أو اللعبة انتهت في اللوحة الصغيرة السابقة
        if (currentBoardX == -1 || boards[currentBoardX][currentBoardY]->game_is_over()) {
            // تحديد اللوحة الصغيرة بناءً على (x, y) من اللوحة الكبيرة
            currentBoardX = x % 3;  // تحديد اللوحة الصغيرة في الاتجاه الأفقي
            currentBoardY = y % 3;  // تحديد اللوحة الصغيرة في الاتجاه الرأسي
        }

        // الآن نقوم بتحديث اللوحة الصغيرة المعينة بناءً على الإحداثيات المدخلة
        return boards[currentBoardX][currentBoardY]->update_board(x / 3, y / 3, symbol); // تحديد المكان داخل اللوحة الصغيرة
    }

    void display_board() override {
        cout << "Ultimate Tic Tac Toe Board:\n";
        for (int i = 0; i < 3; i++) {
            for (int row = 0; row < 3; row++) {
                for (int j = 0; j < 3; j++) {
                    boards[i][j]->display_board_row(row);  // عرض صف من اللوحات الصغيرة
                    cout << " | ";
                }
                cout << endl;
            }
            cout << "-----------------------------\n";
        }
    }

    bool is_win() override {
        return false; // ستكمل لاحقًا
    }

    bool is_draw() override {
        return false; // ستكمل لاحقًا
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class UltimatePlayer : public Player<T> {
public:
    UltimatePlayer(string n, T symbol) : Player<T>(n, symbol) {}
    UltimatePlayer(T symbol) : Player<T>(symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << " (" << this->symbol << "), Enter the coordinates of the big board (0 to 2 for both x and y): ";
        cin >> x >> y;

        // التأكد من أن الإحداثيات في حدود اللوحة الكبيرة (0 إلى 2)
        while (x < 0 || x > 2 || y < 0 || y > 2) {
            cout << "Invalid coordinates! Enter coordinates for the big board between 0 and 2 (x y): ";
            cin >> x >> y;
        }

        // الآن نحدد اللوحة الصغيرة بناءً على الإحداثيات المدخلة
        cout << "Enter coordinates within the small board (0 to 2 for both x and y) [i j]: ";
        cin >> x >> y;

        // التأكد من أن الإحداثيات داخل اللوحة الصغيرة صحيحة (من 0 إلى 2)
        while (x < 0 || x > 2 || y < 0 || y > 2) {
            cout << "Invalid coordinates! Enter coordinates for the small board between 0 and 2 [i j]: ";
            cin >> x >> y;
        }
    }
};



#endif // ULTIMATETICTACTOE_H
