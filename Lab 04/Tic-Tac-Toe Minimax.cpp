#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class MinimaxTicTacToe {
private:
    char board[3][3];
    char AI_PLAYER = 'X';
    char HUMAN_PLAYER = 'O';
    char EMPTY = ' ';

public:
    MinimaxTicTacToe() {
        initializeBoard();
    }

    // Initialize empty board
    void initializeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = EMPTY;
            }
        }
    }

    // Display the current board
    void displayBoard() {
        std::cout << "\n   0   1   2\n";
        for (int i = 0; i < 3; i++) {
            std::cout << i << "  " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
            if (i < 2) std::cout << "  ---|---|---\n";
        }
        std::cout << "\n";
    }

    // Check if position is valid and empty
    bool isValidMove(int row, int col) {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY);
    }

    // Make a move on the board
    void makeMove(int row, int col, char player) {
        if (isValidMove(row, col)) {
            board[row][col] = player;
        }
    }

    // Undo a move
    void undoMove(int row, int col) {
        board[row][col] = EMPTY;
    }

    // Check for winner or draw
    char checkGameStatus() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
                return board[i][0];
            }
        }

        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != EMPTY) {
                return board[0][j];
            }
        }

        // Check diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
            return board[0][0];
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
            return board[0][2];
        }

        // Check for draw
        bool boardFull = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    boardFull = false;
                    break;
                }
            }
            if (!boardFull) break;
        }
        if (boardFull) return 'D'; // Draw

        return 'C'; // Continue playing
    }

    // Minimax algorithm
    int minimax(int depth, bool isMaximizing) {
        char status = checkGameStatus();
        
        // Terminal states
        if (status == AI_PLAYER) return 10 - depth;         // AI wins (prefer quicker wins)
        if (status == HUMAN_PLAYER) return -10 + depth;     // Human wins (delay losses)
        if (status == 'D') return 0;                        // Draw
        
        if (isMaximizing) {
            int maxEval = INT_MIN;
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (isValidMove(i, j)) {
                        makeMove(i, j, AI_PLAYER);
                        int eval = minimax(depth + 1, false);
                        undoMove(i, j);
                        maxEval = std::max(maxEval, eval);
                    }
                }
            }
            return maxEval;
        } else {
            int minEval = INT_MAX;
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (isValidMove(i, j)) {
                        makeMove(i, j, HUMAN_PLAYER);
                        int eval = minimax(depth + 1, true);
                        undoMove(i, j);
                        minEval = std::min(minEval, eval);
                    }
                }
            }
            return minEval;
        }
    }

    // Get the best move for AI using minimax
    std::pair<int, int> getBestMove() {
        std::cout << "AI is thinking...\n";
        
        int bestVal = INT_MIN;
        std::pair<int, int> bestMove = {-1, -1};
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isValidMove(i, j)) {
                    makeMove(i, j, AI_PLAYER);
                    int moveVal = minimax(0, false);
                    undoMove(i, j);
                    
                    if (moveVal > bestVal) {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
        
        return bestMove;
    }

    // Get human player's move
    std::pair<int, int> getHumanMove() {
        int row, col;
        while (true) {
            std::cout << "Enter your move (row col): ";
            std::cin >> row >> col;
            
            if (isValidMove(row, col)) {
                return {row, col};
            } else {
                std::cout << "Invalid move! Try again.\n";
            }
        }
    }

    // Main game loop
    void playGame() {
        std::cout << "=== MINIMAX TIC TAC TOE ===\n";
        std::cout << "Enter moves as row col (0-2)\n";

        bool humanIsX;
        char choice;
        std::cout << "Do you want to go first? (y/n): ";
        std::cin >> choice;
        humanIsX = (choice == 'y' || choice == 'Y');

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

        bool xTurn = true; // X always goes first

        while (true) {
            char status = checkGameStatus();
            if (status != 'C') {
                if (status == 'X') {
                    std::cout << "X WINS!\n";
                } else if (status == 'O') {
                    std::cout << "O WINS!\n";
                } else {
                    std::cout << "IT'S A DRAW!\n";
                }
                break;
            }

            if ((xTurn && humanIsX) || (!xTurn && !humanIsX)) {
                // Human's turn
                auto humanMove = getHumanMove();
                makeMove(humanMove.first, humanMove.second, HUMAN_PLAYER);
                displayBoard();
            } else {
                // AI's turn
                auto aiMove = getBestMove();
                makeMove(aiMove.first, aiMove.second, AI_PLAYER);
                std::cout << "AI chooses position (" << aiMove.first << ", " << aiMove.second << ")\n";
                displayBoard();
            }

            xTurn = !xTurn; // Switch turns
        }
    }
};

int main() {
    MinimaxTicTacToe game;
    
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