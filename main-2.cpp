// Tic Tac Toe - console game in C++
// Concepts: loops, arrays, conditional logic, functions
// Features: 2-player mode, vs Computer mode, dynamic board display,
//           win / draw detection, replay option and scoreboard

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

char board[9];  // positions 1-9 stored at index 0-8

// All 8 winning lines (rows, columns, diagonals)
const int WIN_LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},   // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},   // columns
    {0, 4, 8}, {2, 4, 6}               // diagonals
};

// ---------- Input helper ----------
int readInt(const string &prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Number daalo.\n";
    }
}

// ---------- Board functions ----------
void resetBoard() {
    for (int i = 0; i < 9; i++) board[i] = '1' + i;
}

void drawBoard() {
    cout << "\n";
    for (int r = 0; r < 3; r++) {
        cout << "     " << board[r * 3] << " | " << board[r * 3 + 1] << " | " << board[r * 3 + 2] << "\n";
        if (r < 2) cout << "    ---+---+---\n";
    }
    cout << "\n";
}

bool isCellFree(int idx) {
    return board[idx] != 'X' && board[idx] != 'O';
}

bool hasWon(char player) {
    for (int i = 0; i < 8; i++) {
        if (board[WIN_LINES[i][0]] == player &&
            board[WIN_LINES[i][1]] == player &&
            board[WIN_LINES[i][2]] == player)
            return true;
    }
    return false;
}

bool isDraw() {
    for (int i = 0; i < 9; i++)
        if (isCellFree(i)) return false;
    return true;
}

// ---------- Computer move ----------
// Strategy: 1) win if possible  2) block opponent  3) take centre  4) random free cell
int findWinningMove(char player) {
    for (int i = 0; i < 9; i++) {
        if (!isCellFree(i)) continue;
        char saved = board[i];
        board[i] = player;
        bool win = hasWon(player);
        board[i] = saved;
        if (win) return i;
    }
    return -1;
}

int computerMove(char me, char opponent) {
    int move = findWinningMove(me);
    if (move != -1) return move;
    move = findWinningMove(opponent);
    if (move != -1) return move;
    if (isCellFree(4)) return 4;
    int free[9], n = 0;
    for (int i = 0; i < 9; i++)
        if (isCellFree(i)) free[n++] = i;
    return free[rand() % n];
}

// ---------- Human move ----------
int humanMove(const string &name, char mark) {
    while (true) {
        int pos = readInt(name + " (" + mark + ") - position choose karo (1-9): ");
        if (pos < 1 || pos > 9) {
            cout << "Position 1 se 9 ke beech honi chahiye.\n";
        } else if (!isCellFree(pos - 1)) {
            cout << "Ye jagah already bhari hai! Dusri chuno.\n";
        } else {
            return pos - 1;
        }
    }
}

// ---------- One full game ----------
// returns 1 if X wins, 2 if O wins, 0 for draw
int playGame(bool vsComputer, const string &p1, const string &p2) {
    resetBoard();
    char current = 'X';
    while (true) {
        drawBoard();
        int move;
        if (current == 'X')
            move = humanMove(p1, 'X');
        else if (vsComputer) {
            move = computerMove('O', 'X');
            cout << "Computer ne position " << move + 1 << " chuni.\n";
        } else
            move = humanMove(p2, 'O');

        board[move] = current;

        if (hasWon(current)) {
            drawBoard();
            return current == 'X' ? 1 : 2;
        }
        if (isDraw()) {
            drawBoard();
            return 0;
        }
        current = (current == 'X') ? 'O' : 'X';
    }
}

// ---------- Main ----------
int main() {
    srand((unsigned)time(0));

    cout << "=====================================\n"
         << "        TIC TAC TOE  (C++ Game)\n"
         << "=====================================\n"
         << "1. Player vs Player\n2. Player vs Computer\n";
    int mode;
    do { mode = readInt("Mode choose karo (1-2): "); } while (mode != 1 && mode != 2);

    bool vsComputer = (mode == 2);
    string p1 = "Player 1";
    string p2 = vsComputer ? "Computer" : "Player 2";

    int score1 = 0, score2 = 0, draws = 0;
    char again;

    do {
        int result = playGame(vsComputer, p1, p2);
        if (result == 1) { cout << "*** " << p1 << " (X) jeet gaya! ***\n"; score1++; }
        else if (result == 2) { cout << "*** " << p2 << " (O) jeet gaya! ***\n"; score2++; }
        else { cout << "*** Match draw ho gaya! ***\n"; draws++; }

        cout << "\n--- Scoreboard ---\n"
             << p1 << ": " << score1 << " | " << p2 << ": " << score2
             << " | Draws: " << draws << "\n";

        cout << "\nDobara khelna hai? (y/n): ";
        cin >> again;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (again == 'y' || again == 'Y');

    cout << "\nThanks for playing!\n";
    return 0;
}
