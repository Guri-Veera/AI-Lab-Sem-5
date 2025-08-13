#include <iostream>
#include <vector>
#include <string>

class TicTacToe {
private:
    char board[3][3];
    char AI_PLAYER = 'X';
    char HUMAN_PLAYER = 'O';
    char EMPTY = ' ';

public:
    TicTacToe() {
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
        }
        if (boardFull) return 'D'; // Draw

        return 'C'; // Continue playing
    }

    // RULE 1: Win if possible
    std::pair<int, int> findWinningMove(char player) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isValidMove(i, j)) {
                    // Try the move
                    board[i][j] = player;
                    if (checkGameStatus() == player) {
                        board[i][j] = EMPTY; // Undo move
                        return {i, j};
                    }
                    board[i][j] = EMPTY; // Undo move
                }
            }
        }
        return {-1, -1}; // No winning move found
    }

    // RULE 2: Block opponent's winning move
    std::pair<int, int> findBlockingMove(char opponent) {
        return findWinningMove(opponent); // Same logic, different player
    }

    // RULE 3: Take center if available
    std::pair<int, int> takeCenter() {
        if (isValidMove(1, 1)) {
            return {1, 1};
        }
        return {-1, -1};
    }

    // RULE 4: Take corners (strategic positions)
    std::pair<int, int> takeCorner() {
        std::vector<std::pair<int, int>> corners = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
        for (auto corner : corners) {
            if (isValidMove(corner.first, corner.second)) {
                return corner;
            }
        }
        return {-1, -1};
    }

    // RULE 5: Take any available edge
    std::pair<int, int> takeEdge() {
        std::vector<std::pair<int, int>> edges = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
        for (auto edge : edges) {
            if (isValidMove(edge.first, edge.second)) {
                return edge;
            }
        }
        return {-1, -1};
    }

    // AI Strategy: Apply rules in order of priority
    std::pair<int, int> getAIMove() {
        std::cout << "AI is thinking...\n";

        // RULE 1: Try to win
        auto move = findWinningMove(AI_PLAYER);
        if (move.first != -1) {
            std::cout << "AI Strategy: Going for the WIN!\n";
            return move;
        }

        // RULE 2: Block human from winning
        move = findBlockingMove(HUMAN_PLAYER);
        if (move.first != -1) {
            std::cout << "AI Strategy: Blocking your winning move!\n";
            return move;
        }

        // RULE 3: Take center
        move = takeCenter();
        if (move.first != -1) {
            std::cout << "AI Strategy: Taking the center position!\n";
            return move;
        }

        // RULE 4: Take corner
        move = takeCorner();
        if (move.first != -1) {
            std::cout << "AI Strategy: Taking a corner position!\n";
            return move;
        }

        // RULE 5: Take edge
        move = takeEdge();
        if (move.first != -1) {
            std::cout << "AI Strategy: Taking an edge position!\n";
            return move;
        }

        return {-1, -1}; // Should never reach here
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
        std::cout << "=== TIC TAC TOE SOLVER ===\n";
        std::cout << "You are O, AI is X\n";
        std::cout << "Enter moves as row col (0-2)\n";

        bool humanFirst;
        char choice;
        std::cout << "Do you want to go first? (y/n): ";
        std::cin >> choice;
        humanFirst = (choice == 'y' || choice == 'Y');

        displayBoard();

        while (true) {
            char status = checkGameStatus();
            if (status != 'C') {
                if (status == AI_PLAYER) {
                    std::cout << "AI WINS! Better luck next time!\n";
                } else if (status == HUMAN_PLAYER) {
                    std::cout << "YOU WIN! Congratulations!\n";
                } else {
                    std::cout << "IT'S A DRAW! Good game!\n";
                }
                break;
            }

            if (humanFirst) {
                // Human move
                auto humanMove = getHumanMove();
                makeMove(humanMove.first, humanMove.second, HUMAN_PLAYER);
                displayBoard();

                status = checkGameStatus();
                if (status != 'C') continue;

                // AI move
                auto aiMove = getAIMove();
                makeMove(aiMove.first, aiMove.second, AI_PLAYER);
                std::cout << "AI chooses position (" << aiMove.first << ", " << aiMove.second << ")\n";
                displayBoard();
            } else {
                // AI move first
                auto aiMove = getAIMove();
                makeMove(aiMove.first, aiMove.second, AI_PLAYER);
                std::cout << "AI chooses position (" << aiMove.first << ", " << aiMove.second << ")\n";
                displayBoard();

                status = checkGameStatus();
                if (status != 'C') continue;

                // Human move
                auto humanMove = getHumanMove();
                makeMove(humanMove.first, humanMove.second, HUMAN_PLAYER);
                displayBoard();
            }
        }
    }
};

int main() {
    TicTacToe game;
    
    char playAgain;
    do {
        game.initializeBoard();
        game.playGame();
        
        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgain;
        std::cout << "\n";
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    std::cout << "Thanks for playing! \n";
    return 0;
}