# Minimax Tic Tac Toe in C++

## Problem Statement:
Design and implement a Tic Tac Toe game where a human can play against an **AI opponent** powered by the **Minimax algorithm**.  
The AI must always play optimally, ensuring it either wins or forces a draw. The board is a standard 3×3 grid where players alternate turns placing their symbols (`X` and `O`).

## Code Description
The code uses **Minimax Algorithm** to simulate all possible future moves and choose the optimal one for the AI.

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
> Prints the Board
- ```cpp
  displayBoard()
  ``` 
> Checks if a position on the Board is valid and empty
- ```cpp
  isValidMove(row, col)
  ``` 
> Marks the player's move on the board
- ```cpp
  makeMove(row, col, player)
  ``` 
> Removes symbol (for backtracking)
- ```cpp
  undoMove(row, col)
  ``` 
> Checks the current ststus of the board for `win`, `loss` or `draw`
- ```cpp
  checkGameStatus()
  ``` 
> Recursive algorithm to evaluate board states
- ```cpp
  minimax(depth, isMaximizing)
  ``` 
> Finds AI's optimal move using minimax
- ```cpp
  getBestMove()
  ``` 
> Allows the user to make his/her move
- ```cpp
  getHumanMove()
  ``` 
> Runs main game loop, alternating turns between human and AI
- ```cpp
  playGame()
  ``` 

## Algorithm
```cpp
// Minimax Tic Tac Toe
- Initialize empty 3x3 board
- Ask user if they want to go first
- Loop until game ends:
   - Check game status → win, lose, draw, or continue
   - If human’s turn:
        - Prompt move input
        - Place human move on board
   - If AI’s turn:
        - Use minimax to evaluate all possible moves
        - Choose move with best score
        - Place AI move on board
   - Alternate turns
- Print final result: Win, Lose, or Draw
- Ask to play again
```

## Comments
### Time Complexity
- **Minimax Algorithm:**
  - **Worst Case:** \( O(b^d) \) where `b` = branching factor (up to 9 moves), `d` = depth of tree (max 9).
  - For Tic Tac Toe: \( O(9!) = 362,880 \) states, but pruning and terminal states reduce actual complexity drastically.  
- **Best Case:** Immediate win/loss detected early → \( O(1) \).  
- **Average Case:** Much smaller due to early termination checks.

### Space Complexity
- **Board Representation:** \( O(3×3) = O(1) \).  
- **Recursion Depth:** At most 9 calls deep → \( O(9) = O(1) \).  
- **Overall:** Constant space (game tree fits easily in memory).

### General Remarks
- AI always plays optimally:  
  - If human plays perfectly → Game ends in **Draw**.  
  - If human makes mistake → AI will **Win**.  
- Demonstrates backtracking and adversarial search principles.

---

## Example Usage
> Input/Output:
```
=== MINIMAX TIC TAC TOE ===
Enter moves as row col (0-2)
Do you want to go first? (y/n): y
You are X (first), AI is O

   0   1   2
0    |   |
  ---|---|---
1    |   |
  ---|---|---
2    |   |

Enter your move (row col): 0 2

   0   1   2
0    |   | X
  ---|---|---
1    |   |
  ---|---|---
2    |   |

AI is thinking...
AI chooses position (1, 1)

   0   1   2
0    |   | X
  ---|---|---
1    | O |
  ---|---|---
2    |   |

Enter your move (row col): 2 0

   0   1   2
0    |   | X
  ---|---|---
1    | O |
  ---|---|---
2  X |   |

AI is thinking...
AI chooses position (0, 1)

   0   1   2
0    | O | X
  ---|---|---
1    | O |
  ---|---|---
2  X |   |

Enter your move (row col): 2 1

   0   1   2
0    | O | X
  ---|---|---
1    | O |
  ---|---|---
2  X | X |

AI is thinking...
AI chooses position (2, 2)

   0   1   2
0    | O | X
  ---|---|---
1    | O |
  ---|---|---
2  X | X | O

Enter your move (row col): 0 0

   0   1   2
0  X | O | X
  ---|---|---
1    | O |
  ---|---|---
2  X | X | O

AI is thinking...
AI chooses position (1, 0)

   0   1   2
0  X | O | X
  ---|---|---
1  O | O |
  ---|---|---
2  X | X | O

Enter your move (row col): 1 2

   0   1   2
0  X | O | X
  ---|---|---
1  O | O | X
  ---|---|---
2  X | X | O

IT'S A DRAW!

Play again? (y/n): n

Thanks for playing!
```