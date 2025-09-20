# Alpha-Beta Pruning Tic Tac Toe in C++

## Problem Statement
Design and implement a Tic Tac Toe game where a human can play against an **AI opponent** powered by the **Minimax Algorithm with Alpha-Beta Pruning.**
The AI must always play optimally, ensuring it either wins or forces a draw.
This version optimizes the classic Minimax approach by eliminating unnecessary branches (pruning), resulting in faster decision-making without sacrificing optimality.

The game uses a standard 3×3 grid, and players alternate turns placing their symbols (X and O).

## Theory: Alpha-Beta Pruning
### 1. Background

- The Minimax Algorithm is a recursive search strategy used in two-player zero-sum games (like Tic Tac Toe, Chess, etc.).
- It assumes both players play optimally:
  - The maximizing player (AI) tries to maximize the score.
  - The minimizing player (human) tries to minimize the score.
- However, plain Minimax explores all possible game states, which grows exponentially

### 2. What is Alpha-Beta Pruning?
- Alpha-Beta Pruning is an optimization that cuts off parts of the Minimax tree that cannot affect the final decision.
- It introduces two parameters:
  - `Alpha (α)` → Best (highest) value the maximizer can guarantee so far
  - `Beta (β)` → Best (lowest) value the minimizer can guarantee so far
- As the recursion unfolds:
  - If β ≤ α, it means the current branch cannot improve the outcome → stop exploring it. This is called a pruning condition.

### 3. Intuitive Example
- Imagine you’re the AI, evaluating your possible moves:
  - You find one branch where you can guarantee at least +5 (α = +5).
  - In another branch, the opponent can already limit you to ≤ +3 (β = +3).
  - Since β < α, you know the opponent will never allow you to reach +5 — so there’s no need to explore further.
- **Result:** You skip unnecessary work without affecting the final decision.

## Code Description
This implementation enhances the Minimax-based AI by introducing Alpha-Beta Pruning, reducing redundant evaluations in the decision tree.

### Data Structures Used:
- **3x3 board** → Represented as a 2D char array.  
- **Constants**:
  - `AI_PLAYER` → Symbol for the AI  
  - `HUMAN_PLAYER` → Symbol for the human  
  - `EMPTY` → Empty cell `' '`  

### Functions:
> Initializes and empty playing board
- ```cpp
  initializeBoard()
  ```
Fills all board cells with the `EMPTY` character.

> Prints the Board
- ```cpp
  displayBoard()
  ```
Prints the current state of the board in a formatted grid layout.

> Checks if a position on the Board is valid and empty
- ```cpp
  isValidMove(row, col)
  ```
Returns `true` if the cell is inside bounds and unoccupied.

> Marks the player's move on the board
- ```cpp
  makeMove(row, col, player)
  ```
Places a player's symbol (`X` or `O`) on the board.

> Removes symbol (for backtracking)
- ```cpp
  undoMove(row, col)
  ```
Resets a cell back to `EMPTY`.

> Checks the current ststus of the board for `win`, `loss` or `draw`
- ```cpp
  checkGameStatus()
  ```
Returns `'X'` if player X wins

Returns `'O'` if player O wins

Returns `'D'` if the board is full (Draw)

Returns `'C'` to continue the game

> Recursive algorithm to evaluate board states
- ```cpp
  minimax(depth, isMaximizing)
  ```
- Recursively simulates all possible game states to determine the optimal move.
- Uses Alpha-Beta bounds (`alpha`, `beta`) to skip evaluating unpromising branches, improving efficiency.

> Finds AI's optimal move using minimax
- ```cpp
  getBestMove()
  ```
Loops through all possible valid moves, applies the `minimax()` function, and returns the best (row, col) position for the AI.

> Allows the user to make his/her move
- ```cpp
  getHumanMove()
  ```
Prompts the player for their move until a valid position is entered.

> Runs main game loop, alternating turns between human and AI
- ```cpp
  playGame()
  ```
- Alternates turns between the AI and the human player.
- Continuously checks for win/loss/draw conditions.
- Displays board state after each move.
- Declares the final result.

## Algorithm
```cpp
// Alpha-Beta Pruning Tic Tac Toe
- Initialize empty 3×3 board
- Ask user if they want to go first
- Loop until game ends:
   - Check game status (win, loss, draw)
   - If human’s turn:
       - Get valid move input
       - Place move on board
   - If AI’s turn:
       - Use minimax with alpha-beta pruning
       - Choose move with best score
       - Place move on board
   - Alternate turns
- Print final outcome (Win / Lose / Draw)
- Ask if the user wants to play again
```

## Comments
### Time Complexity
- **Minimax (without pruning):**
  - \( O(b^d) \)
    - `b` = branching factor (up to 9 moves),
    - `d` = depth of tree (max 9).
- **With Alpha Beta Pruning:**
  - Best case reduces to \( O(b^{d/2}) \), cutting search time significantly by avoiding exploration of inferior branches.
- For Tic Tac Toe:
  - Real complexity $<<$ $9!$, typically only dozens of evaluations per move.
### Space Complexity
- **Board Representation:** \( O(3×3) = O(1) \).  
- **Recursion Depth:** At most 9 calls deep → \( O(9) = O(1) \).  
- **Overall:** Constant space (game tree fits easily in memory).

### General Remarks
- The Alpha-Beta Pruned Minimax ensures:
  - AI never loses (optimal play).
  - Human can only draw with perfect play.
  - Execution is significantly faster than plain Minimax.

- Demonstrates concepts of:
  - Adversarial Search
  - Game Tree Evaluation
  - Pruning Optimization
  - Recursive Backtracking

---

## Example Usage
> Input/Output:
```
=== ALPHA-BETA PRUNING TIC TAC TOE ===
Enter moves as row col (0-2)
Do you want to go first? (y/n): y
You are X (first), AI is O

   0   1   2
0    |   |
  ---|---|---
1    |   |
  ---|---|---
2    |   |

Enter your move (row col): 1 1

   0   1   2
0    |   |  
  ---|---|---
1    | X |  
  ---|---|---
2    |   |  

AI is thinking...
AI chooses position (0, 0)

   0   1   2
0  O |   |
  ---|---|---
1    | X |
  ---|---|---
2    |   |

Enter your move (row col): 2 0

   0   1   2
0  O |   |
  ---|---|---
1    | X |
  ---|---|---
2  X |   |

AI is thinking...
AI chooses position (0, 2)

   0   1   2
0  O |   | O
  ---|---|---
1    | X |
  ---|---|---
2  X |   |

Enter your move (row col): 0 1

   0   1   2
0  O | X | O
  ---|---|---
1    | X |
  ---|---|---
2  X |   |

AI is thinking...
AI chooses position (2, 1)

   0   1   2
0  O | X | O
  ---|---|---
1    | X |
  ---|---|---
2  X | O |

Enter your move (row col): 1 2

   0   1   2
0  O | X | O
  ---|---|---
1    | X | X
  ---|---|---
2  X | O |

AI is thinking...
AI chooses position (1, 0)

   0   1   2
0  O | X | O
  ---|---|---
1  O | X | X
  ---|---|---
2  X | O |

Enter your move (row col): 2 2

   0   1   2
0  O | X | O
  ---|---|---
1  O | X | X
  ---|---|---
2  X | O | X

IT'S A DRAW!

Play again? (y/n): n

Thanks for playing!
```