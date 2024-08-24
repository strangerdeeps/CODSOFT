#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}

// Function to check if there are any moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// Function to evaluate the board
int evaluate(const vector<vector<char>>& board) {
    // Check rows for a win
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'O')
                return 10;
            else if (board[row][0] == 'X')
                return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'O')
                return 10;
            else if (board[0][col] == 'X')
                return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O')
            return 10;
        else if (board[0][0] == 'X')
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O')
            return 10;
        else if (board[0][2] == 'X')
            return -10;
    }

    // No one has won yet
    return 0;
}

// Minimax algorithm with Alpha-Beta Pruning
int minimax(vector<vector<char>>& board, int depth, bool isMaximizing, int alpha, int beta) {
    int score = evaluate(board);

    // If AI has won, return the score
    if (score == 10)
        return score - depth;

    // If human has won, return the score
    if (score == -10)
        return score + depth;

    // If there are no moves left and no winner, it's a tie
    if (!isMovesLeft(board))
        return 0;

    if (isMaximizing) {
        int best = INT_MIN;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = 'O';

                    // Call minimax recursively and choose the maximum value
                    best = max(best, minimax(board, depth + 1, !isMaximizing, alpha, beta));

                    // Undo the move
                    board[i][j] = ' ';

                    // Alpha-Beta Pruning
                    alpha = max(alpha, best);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;

    } else {
        int best = INT_MAX;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = 'X';

                    // Call minimax recursively and choose the minimum value
                    best = min(best, minimax(board, depth + 1, !isMaximizing, alpha, beta));

                    // Undo the move
                    board[i][j] = ' ';

                    // Alpha-Beta Pruning
                    beta = min(beta, best);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // Make the move
                board[i][j] = 'O';

                // Compute the value of this move
                int moveVal = minimax(board, 0, false, INT_MIN, INT_MAX);

                // Undo the move
                board[i][j] = ' ';

                // If the value of the current move is more than the best value, update best move
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Function to check if the game has ended
bool checkGameEnd(const vector<vector<char>>& board) {
    int score = evaluate(board);

    if (score == 10) {
        cout << "AI wins!" << endl;
        return true;
    } else if (score == -10) {
        cout << "Human wins!" << endl;
        return true;
    } else if (!isMovesLeft(board)) {
        cout << "It's a tie!" << endl;
        return true;
    }

    return false;
}

// Main function to play the game
void playGame() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    printBoard(board);

    while (true) {
        // Human's turn
        int row, col;
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        if (board[row][col] != ' ') {
            cout << "Invalid move, try again." << endl;
            continue;
        }

        board[row][col] = 'X';
        printBoard(board);

        if (checkGameEnd(board)) break;

        // AI's turn
        cout << "AI's move:" << endl;
        pair<int, int> aiMove = findBestMove(board);
        board[aiMove.first][aiMove.second] = 'O';
        printBoard(board);

        if (checkGameEnd(board)) break;
    }
}

int main() {
    playGame();
    return 0;
}
