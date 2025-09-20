#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class AlphaBetaTicTacToe {
private:
    char board[3][3];
    char AI_PLAYER = 'X';
    char HUMAN_PLAYER = 'O';
    char EMPTY = ' ';

public:
    AlphaBetaTicTacToe() {
        initializeBoard();
    }

    void initializeBoard() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = EMPTY;
    }

    void displayBoard() {
        std::cout << "\n   0   1   2\n";
        for (int i = 0; i < 3; i++) {
            std::cout << i << "  " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
            if (i < 2) std::cout << "  ---|---|---\n";
        }
        std::cout << "\n";
    }

    bool isValidMove(int row, int col) {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY);
    }

    void makeMove(int row, int col, char player) {
        board[row][col] = player;
    }

    void undoMove(int row, int col) {
        board[row][col] = EMPTY;
    }

    char checkGameStatus() {
        // Rows
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
                return board[i][0];

        // Columns
        for (int j = 0; j < 3; j++)
            if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != EMPTY)
                return board[0][j];

        // Diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
            return board[0][0];
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
            return board[0][2];

        // Draw?
        bool full = true;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == EMPTY)
                    full = false;

        if (full) return 'D'; // Draw
        return 'C'; // Continue
    }

    // ✅ Minimax with Alpha-Beta pruning
    int minimax(int depth, bool isMaximizing, int alpha, int beta) {
        char status = checkGameStatus();

        if (status == AI_PLAYER) return 10 - depth;
        if (status == HUMAN_PLAYER) return -10 + depth;
        if (status == 'D') return 0;

        if (isMaximizing) {
            int bestVal = INT_MIN;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (isValidMove(i, j)) {
                        makeMove(i, j, AI_PLAYER);
                        int eval = minimax(depth + 1, false, alpha, beta);
                        undoMove(i, j);
                        bestVal = std::max(bestVal, eval);
                        alpha = std::max(alpha, bestVal);

                        // 🔥 Prune
                        if (beta <= alpha)
                            return bestVal;
                    }
                }
            }
            return bestVal;
        } else {
            int bestVal = INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (isValidMove(i, j)) {
                        makeMove(i, j, HUMAN_PLAYER);
                        int eval = minimax(depth + 1, true, alpha, beta);
                        undoMove(i, j);
                        bestVal = std::min(bestVal, eval);
                        beta = std::min(beta, bestVal);

                        // 🔥 Prune
                        if (beta <= alpha)
                            return bestVal;
                    }
                }
            }
            return bestVal;
        }
    }

    std::pair<int, int> getBestMove() {
        std::cout << "AI is thinking...\n";
        int bestVal = INT_MIN;
        std::pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isValidMove(i, j)) {
                    makeMove(i, j, AI_PLAYER);
                    int moveVal = minimax(0, false, INT_MIN, INT_MAX);
                    undoMove(i, j);

                    if (moveVal > bestVal) {
                        bestVal = moveVal;
                        bestMove = {i, j};
                    }
                }
            }
        }
        return bestMove;
    }

    std::pair<int, int> getHumanMove() {
        int row, col;
        while (true) {
            std::cout << "Enter your move (row col): ";
            std::cin >> row >> col;
            if (isValidMove(row, col)) return {row, col};
            std::cout << "Invalid move! Try again.\n";
        }
    }

    void playGame() {
        std::cout << "=== ALPHA-BETA PRUNING TIC TAC TOE ===\n";
        std::cout << "Enter moves as row col (0-2)\n";

        char choice;
        std::cout << "Do you want to go first? (y/n): ";
        std::cin >> choice;
        bool humanIsX = (choice == 'y' || choice == 'Y');

        if (humanIsX) {
            AI_PLAYER = 'O';
            HUMAN_PLAYER = 'X';
            std::cout << "You are X (first), AI is O\n";
        } else {
            AI_PLAYER = 'X';
            HUMAN_PLAYER = 'O';
            std::cout << "AI is X (first), You are O\n";
        }

        displayBoard();
        bool xTurn = true;

        while (true) {
            char status = checkGameStatus();
            if (status != 'C') {
                if (status == 'X') std::cout << "X WINS!\n";
                else if (status == 'O') std::cout << "O WINS!\n";
                else std::cout << "IT'S A DRAW!\n";
                break;
            }

            if ((xTurn && humanIsX) || (!xTurn && !humanIsX)) {
                auto humanMove = getHumanMove();
                makeMove(humanMove.first, humanMove.second, HUMAN_PLAYER);
                displayBoard();
            } else {
                auto aiMove = getBestMove();
                makeMove(aiMove.first, aiMove.second, AI_PLAYER);
                std::cout << "AI chooses position (" << aiMove.first << ", " << aiMove.second << ")\n";
                displayBoard();
            }

            xTurn = !xTurn;
        }
    }
};

int main() {
    AlphaBetaTicTacToe game;

    char playAgain;
    do {
        game.initializeBoard();
        game.playGame();
        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgain;
        std::cout << "\n";
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Thanks for playing!\n";
    return 0;
}
