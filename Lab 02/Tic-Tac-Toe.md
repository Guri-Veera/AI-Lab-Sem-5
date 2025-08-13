# Tic Tac Toe AI Solver in C++

## Problem Statement
The goal of this program is to implement a **Tic Tac Toe** game between a human player and an AI opponent.  
The AI follows a set of **deterministic rules** to ensure it never loses and often wins.


## AI Strategy (Rules)
The AI makes decisions using the following rules in priority order:

1. **Win if possible** → If AI has a winning move, take it.
2. **Block opponent** → If the human can win in the next move, block it.
3. **Take center** → If the center square is available, take it.
4. **Take corner** → If any corner is available, take it.
5. **Take edge** → As a last option, pick an available edge.

This ensures the AI always plays optimally.

---

## Functions
> Initializes an empty Board
- ```cpp
  void initializeBoard()
  ```
> Prints the Board
- ```cpp
  void displayBoard()
  ```
> Checks if a position on the Board is valid and empty
- ```cpp
  bool isValidMove(int row, int col)
  ```
> Marks the player's move on the board
- ```cpp
  void makeMove(int row, int col, char player)
  ```
> Checks the current ststus of the board for `win`, `loss` or `draw`
- ```cpp
  char checkGameStatus()
  ```
> Rule 1: Finds the Winning Move (if any)
- ```cpp
  std::pair<int, int> findWinningMove(char player)
  ```
> Rule 2: Finds the Blocking Move (if any)
- ```cpp
  std::pair<int, int> findBlockingMove(char opponent)
  ```
> Rule 3: Takes Center Position (if available)
- ```cpp
  std::pair<int, int> takeCenter()
  ```
> Rule 4: Takes Corner (if available)
- ```cpp
  std::pair<int, int> takeCorner()
  ```
> Rule 5: Takes any available edge
- ```cpp
  std::pair<int, int> takeEdge()
  ```
> Determines the next move for the AI according to priority of the above 5 Rules 
- ```cpp
  std::pair<int, int> getAIMove()
  ```
> Allows the user to make his/her move
- ```cpp
  std::pair<int, int> getHumanMove()
  ```
> Main Game Loop
- ```cpp
  void playGame()
  ```

## Example Run

### User Wins
```
=== TIC TAC TOE SOLVER ===
You are O, AI is X
Enter moves as row col (0-2)
Do you want to go first? (y/n): y

   0   1   2
0    |   |  
  ---|---|---
1    |   |
  ---|---|---
2    |   |

Enter your move (row col): 0 2

   0   1   2
0    |   | O
  ---|---|---
1    |   |
  ---|---|---
2    |   |

AI is thinking...
AI Strategy: Taking the center position!
AI chooses position (1, 1)

   0   1   2
0    |   | O
  ---|---|---
1    | X |
  ---|---|---
2    |   |

Enter your move (row col): 2 0

   0   1   2
0    |   | O
  ---|---|---
1    | X |
  ---|---|---
2  O |   |

AI is thinking...
AI Strategy: Taking a corner position!
AI chooses position (0, 0)

   0   1   2
0  X |   | O
  ---|---|---
1    | X |
  ---|---|---
2  O |   |

Enter your move (row col): 2 2

   0   1   2
0  X |   | O
  ---|---|---
1    | X |
  ---|---|---
2  O |   | O

AI is thinking...
AI Strategy: Blocking your winning move!
AI chooses position (1, 2)

   0   1   2
0  X |   | O
  ---|---|---
1    | X | X
  ---|---|---
2  O |   | O

Enter your move (row col): 2 1

   0   1   2
0  X |   | O
  ---|---|---
1    | X | X
  ---|---|---
2  O | O | O

YOU WIN! Congratulations!

Play again? (y/n): n

Thanks for playing!
```

### Draw
```
=== TIC TAC TOE SOLVER ===
You are O, AI is X
Enter moves as row col (0-2)
Do you want to go first? (y/n): y

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
1    | O |
  ---|---|---
2    |   |

AI is thinking...
AI Strategy: Taking a corner position!
AI chooses position (0, 0)

   0   1   2
0  X |   |
  ---|---|---
1    | O |
  ---|---|---
2    |   |

Enter your move (row col): 0 2

   0   1   2
0  X |   | O
  ---|---|---
1    | O |
  ---|---|---
2    |   |

AI is thinking...
AI Strategy: Blocking your winning move!
AI chooses position (2, 0)

   0   1   2
0  X |   | O
  ---|---|---
1    | O |
  ---|---|---
2  X |   |

Enter your move (row col): 1 0

   0   1   2
0  X |   | O
  ---|---|---
1  O | O |
  ---|---|---
2  X |   |

AI is thinking...
AI Strategy: Blocking your winning move!
AI chooses position (1, 2)

   0   1   2
0  X |   | O
  ---|---|---
1  O | O | X
  ---|---|---
2  X |   |

Enter your move (row col): 0 1

   0   1   2
0  X | O | O
  ---|---|---
1  O | O | X
  ---|---|---
2  X |   |

AI is thinking...
AI Strategy: Blocking your winning move!
AI chooses position (2, 1)

   0   1   2
0  X | O | O
  ---|---|---
1  O | O | X
  ---|---|---
2  X | X |

Enter your move (row col): 2 2

   0   1   2
0  X | O | O
  ---|---|---
1  O | O | X
  ---|---|---
2  X | X | O

IT'S A DRAW! Good game!

Play again? (y/n): n

Thanks for playing!
```