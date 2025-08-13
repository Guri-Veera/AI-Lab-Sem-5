# 8 Puzzle Problem Solution in C++ (DFS, BFS, and BestFS)

## Problem Statement:
Given a 3×3 board with 8 tiles (each numbered from 1 to 8) and one empty space, the objective is to place the numbers to match the final configuration using the empty space. We can slide four adjacent tiles (left, right, above, and below) into the empty space.

### Example Goal State:
```cpp
int goal[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};
```
(Zero represents empty space) The goal is to determine if the Goal State can be reached from an input state, and if so, provide the moves necessary to do so.

## Code Description
The code solves the 8 Puzzle Problem via DFS, BFS, and Best-First Search (Greedy with heuristics).  
User has the option to choose at run-time. It then generates a tree of corresponding states from a given board configuration, by moving the empty space left, right, down and up (within constraints of the board size).

### Data Structures Used:
- **Enum** `SearchType` (DFS, BFS, BESTFS)
- **Structure** `State` with member variables:  
  `int id, int arr[3][3], int parent, int depth, int heuristic`
- **Unordered Map** `stateMap` → maps IDs to states (used for path tracing)
- **Deque** `container` → supports DFS (stack) and BFS (queue)
- **Priority Queue** `bestfs_container` → supports BestFS ordered by heuristic
- **Unordered Set** `openSet` → tracks frontier states (O(1) lookups)
- **Unordered Set** `closed` → tracks visited states
- **Vector of States** `path` → reconstructs solution path

## Heuristics for BestFS
- **Misplaced Tiles:** Counts tiles not in correct position
- **Manhattan Distance:** Sum of absolute row+column distances from goal

## Functions
- `swap(int&, int&)` → swaps two elements
- `findBlank(const State&)` → finds blank (0) tile
- `GoalTest(const State&, const State&)` → checks if goal reached
- `misplacedTiles(const State&, const State&)` → heuristic
- `manhattan(const State&, const State&)` → heuristic
- `GenMoves(State, container, openSet, closed, stateMap, searchType)` → generates neighbors

## Algorithm (High Level)
1. Initialize `initialState` and `GoalState`
2. Insert `initialState` into container (deque or priority queue depending on search)
3. Maintain `openSet`, `closed`, and `stateMap`
4. While container not empty:
   - Pop state (DFS=stack, BFS=queue, BestFS=priority queue)
   - If matches GoalState → reconstruct path & exit
   - Else expand with `GenMoves`
5. If exhausted without success → no solution

## Time Complexity
- **DFS:** Best $O(d)$, Worst $O(b^m)$  
- **BFS:** $O(b^d)$, always optimal solution  
- **BestFS:** Depends on heuristic quality

## Space Complexity
- **DFS:** $O(bm)$, lower memory  
- **BFS:** $O(b^d)$, higher memory  
- **BestFS:** $O(b^d)$ but often prunes search space

## Example Usage
> Input
```cpp
int inp[3][3] = {
    {6, 4, 7},
    {8, 5, 0},
    {3, 2, 1}
};
```

> Output
```
Enter Choice (1 for DFS, 2 for BFS, 3 for BestFS)
3
Choose heuristic for Best-First Search:
1. Manhattan Distance
2. Misplaced Tiles
Enter choice: 2
Using Best-First Search (Greedy, Misplaced Tiles Heuristic)


=== SOLUTION FOUND! ===
Search Algorithm: BestFS
Time taken: 0 ms
Nodes explored: 103
Solution length: 45 moves
Total states in path: 46

Solution path:
Step 0 (State ID: 0, Depth: 0, Heuristic: 21):
6 4 7
8 5
3 2 1

Step 1 (State ID: 2, Depth: 1, Heuristic: 20):
6 4 7
8 5 1
3 2

Step 2 (State ID: 7, Depth: 2, Heuristic: 21):
6 4 7
8 5 1
3   2

Step 3 (State ID: 14, Depth: 3, Heuristic: 20):
6 4 7
8 5 1
  3 2

Step 4 (State ID: 16, Depth: 4, Heuristic: 19):
6 4 7
  5 1
8 3 2

Step 5 (State ID: 18, Depth: 5, Heuristic: 18):
  4 7
6 5 1
8 3 2

Step 6 (State ID: 22, Depth: 6, Heuristic: 17):
4   7
6 5 1
8 3 2

Step 7 (State ID: 25, Depth: 7, Heuristic: 16):
4 7
6 5 1
8 3 2

Step 8 (State ID: 26, Depth: 8, Heuristic: 15):
4 7 1
6 5
8 3 2

Step 9 (State ID: 29, Depth: 9, Heuristic: 14):
4 7 1
6 5 2
8 3

Step 10 (State ID: 32, Depth: 10, Heuristic: 13):
4 7 1
6 5 2
8   3

Step 11 (State ID: 34, Depth: 11, Heuristic: 12):
4 7 1
6 5 2
  8 3

Step 12 (State ID: 36, Depth: 12, Heuristic: 13):
4 7 1
  5 2
6 8 3

Step 13 (State ID: 38, Depth: 13, Heuristic: 12):
  7 1
4 5 2
6 8 3

Step 14 (State ID: 42, Depth: 14, Heuristic: 11):
7   1
4 5 2
6 8 3

Step 15 (State ID: 45, Depth: 15, Heuristic: 10):
7 1
4 5 2
6 8 3

Step 16 (State ID: 46, Depth: 16, Heuristic: 9):
7 1 2
4 5
6 8 3

Step 17 (State ID: 49, Depth: 17, Heuristic: 8):
7 1 2
4 5 3
6 8

Step 18 (State ID: 52, Depth: 18, Heuristic: 9):
7 1 2
4 5 3
6   8

Step 19 (State ID: 54, Depth: 19, Heuristic: 8):
7 1 2
4 5 3
  6 8

Step 20 (State ID: 56, Depth: 20, Heuristic: 9):
7 1 2
  5 3
4 6 8

Step 21 (State ID: 58, Depth: 21, Heuristic: 8):
  1 2
7 5 3
4 6 8

Step 22 (State ID: 62, Depth: 22, Heuristic: 7):
1   2
7 5 3
4 6 8

Step 23 (State ID: 65, Depth: 23, Heuristic: 6):
1 2
7 5 3
4 6 8

Step 24 (State ID: 66, Depth: 24, Heuristic: 5):
1 2 3 
7 5
4 6 8

Step 25 (State ID: 69, Depth: 25, Heuristic: 6):
1 2 3
7 5 8
4 6

Step 26 (State ID: 72, Depth: 26, Heuristic: 5):
1 2 3
7 5 8
4   6

Step 27 (State ID: 74, Depth: 27, Heuristic: 6):
1 2 3
7 5 8
  4 6

Step 28 (State ID: 183, Depth: 28, Heuristic: 5):
1 2 3
  5 8
7 4 6

Step 29 (State ID: 187, Depth: 29, Heuristic: 6):
1 2 3
5   8
7 4 6

Step 30 (State ID: 202, Depth: 30, Heuristic: 5):
1 2 3
5 8
7 4 6

Step 31 (State ID: 207, Depth: 31, Heuristic: 4):
1 2 3
5 8 6
7 4

Step 32 (State ID: 210, Depth: 32, Heuristic: 5):
1 2 3
5 8 6
7   4

Step 33 (State ID: 211, Depth: 33, Heuristic: 4):
1 2 3
5   6
7 8 4

Step 34 (State ID: 216, Depth: 34, Heuristic: 3):
1 2 3
  5 6
7 8 4

Step 35 (State ID: 219, Depth: 35, Heuristic: 4):
1 2 3
7 5 6
  8 4

Step 36 (State ID: 224, Depth: 36, Heuristic: 5):
1 2 3
7 5 6
8   4

Step 37 (State ID: 238, Depth: 37, Heuristic: 4):
1 2 3
7 5 6
8 4

Step 38 (State ID: 239, Depth: 38, Heuristic: 5):
1 2 3
7 5
8 4 6

Step 39 (State ID: 246, Depth: 39, Heuristic: 6):
1 2 3
7   5
8 4 6

Step 40 (State ID: 258, Depth: 40, Heuristic: 5):
1 2 3
7 4 5
8   6

Step 41 (State ID: 262, Depth: 41, Heuristic: 4):
1 2 3
7 4 5
  8 6

Step 42 (State ID: 264, Depth: 42, Heuristic: 3):
1 2 3
  4 5
7 8 6

Step 43 (State ID: 268, Depth: 43, Heuristic: 2):
1 2 3
4   5
7 8 6

Step 44 (State ID: 272, Depth: 44, Heuristic: 1):
1 2 3
4 5
7 8 6

Step 45 (State ID: 274, Depth: 45, Heuristic: 0):
1 2 3
4 5 6
7 8

```