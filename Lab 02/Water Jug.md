# Water Jug Problem Solver in C++

## Problem Statement
To measure out a certain volume of water using 2 water jugs of known max volume. The jugs can only be filled fully or emptied out completely or emptied into each other till the receiving jug is full.

## Code Description
The code solves the problem by considering all possible moves of a certain state and then parsing through the tree of these moves by DFS or BFS (chosen by the user at run-time)

### Data Structures Used:
- **Enum**  `SearchType` to provide choice to the user between DFS and BFS
- **Structure** `State` with member variables -- `int id`, `int jug1`, `int jug2`, `int parent`, `int depth`, `std::string action` to keep track of states
- **Structure** `JugConfig` with member variables -- `capacity1`, `capacity2`, `target` to store the limit of jugs and the final volume required
- **Unordered Map** `stateMap` that maps state IDs to a state. Useful for tracing path taken by using parent's ID stored inside the state
- **Deque** `container` to allow for both Stack and Queue operations in a single container. Used to store possible moves/states (to be searched)
- **Unordered Set** `openSet` to store possible states. Duplicate of `container` but allows for average O(1) lookups instead of O(n) traversal-lookup in deque. Extremely beneficial to reduce time complexity at the cost of increased space
- **Unordered Set** `closed` to keep track of states already traversed. Benefits from O(1) lookup time to check if a state has been traversed or not
- **Vector of States** `path` to store the path taken by the solution (if found)

## Functions
> Used to swap empty space with adjacent element
- ```cpp
  void swap(int &a, int &b)
  ```
> Used to swap empty space with adjacent element
- ```cpp
  void swap(int &a, int &b)
  ```
> Used to swap empty space with adjacent element
- ```cpp
  void swap(int &a, int &b)
  ```
> Used to generate all moves from a given jug state configuration
- ```cpp
  void GenMoves(State currState, std::deque<State> &container, std::unordered_set<std::string> &openSet, std::unordered_set<std::string>& closed, std::unordered_map<int, State> &stateMap, SearchType searchType, const JugConfig& config);
  ```
> Used to check if a state has reached the Goal State (either jug contains the required volume of water)
- ```cpp
  bool GoalTest(const State &currState, const JugConfig& config);
  ```

## Algorithm
```
Input:
- Capacity of Jug 1 (C1)
- Capacity of Jug 2 (C2)
- Target amount (T)
- Choice of search algorithm: DFS or BFS

Initialize problem configuration
- Read C1,C2,T.
- If T > max(C1,C2), output “Target not possible” and terminate.

Choose search strategy
- If user selects DFS → use stack-like behavior.
- If user selects BFS → use queue-like behavior.

Create initial state
- Jug1 = 0, Jug2 = 0.
- Depth = 0, Parent = -1.
- Action = “Initial state (both jugs empty)”.
- Insert into:
    - container (deque for DFS/BFS)
    - open set (states to be explored)

Search loop (until container is empty):
- Remove a state:
    - DFS → from back (stack).
    - BFS → from front (queue).
- Mark it as explored (move from open to closed).

Goal Test
- If Jug1 == T OR Jug2 == T, then:
    - Stop search.
    - Reconstruct path by following parent links back to initial state.
    - Print the sequence of actions and states.
    - Terminate.

Generate possible moves (successor states)
- From current state, create new states by applying:
    - Fill Jug 1 fully.
    - Fill Jug 2 fully.
    - Empty Jug 1 completely.
    - Empty Jug 2 completely.
    - Pour from Jug 1 → Jug 2 until Jug 1 is empty or Jug 2 is full.
    - Pour from Jug 2 → Jug 1 until Jug 2 is empty or Jug 1 is full.

- For each generated state:
    - Increase depth by 1.
    - Store action taken.
    - Skip if state is already in open set or closed set.
    - Add new state into container and open set.

Depth Limit
- If depth exceeds MAX_DEPTH, discard the state (avoid infinite search).

If container becomes empty and goal not found:
- Print “No solution found within depth limit”.
- Check solvability condition:
    - If T % gcd(C1,C2) != 0 → Problem has no solution.
    - Else → Increase depth limit and retry.
```

## Comments
### Time Complexity
#### DFS (Depth-First Search)
- **Best Case:** $O(d)$ where $d$ is depth of solution
- **Worst Case:** $O(b^m)$ where $b=6$ (branching factor), $m=$ MAX_DEPTH
- **Upper Limit:** $O(C1 * C2)$ but due to constraints like `closed` list, this number is often not reached (if solution exists)
- **Average Case:** $O(b^d)$ where $d$ is solution depth
- **Note:** May find very long paths before optimal solution

#### BFS (Breadth-First Search)
- **Time Complexity:** $O(b^d)$ where $b=6$, $d=$ solution depth
- **Guarantee:** Always finds optimal solution (shortest path)
- **Note:** Explores all nodes at depth k before depth $k+1$

### Space Complexity
#### DFS
- **Space:** $O(b×m)$ where $m=$ MAX_DEPTH
- **Memory Usage:** Lower - stores only current path + frontier
- **Stack Depth:** Can reach MAX_DEPTH levels

#### BFS
- **Space:** $O(b^d)$ where $d=$ solution depth
- **Memory Usage:** Higher - stores all nodes at current level
- **Risk:** Memory explosion for deep solutions

## Example Usage
> Input
```
    Jug1 = 101L
    Jug2 = 99L
    Target = 50L
```
> Output
```
=== WATER JUG PROBLEM SOLVER ===

Enter capacity of Jug 1: 101
Enter capacity of Jug 2: 99
Enter target amount: 50

Problem: Find 50 liters using jugs of 101L and 99L

Choose search algorithm:
1. Depth-First Search (DFS)
2. Breadth-First Search (BFS)
Enter choice (1 or 2): 2 
Using Breadth-First Search (BFS)

Nodes explored: 100, Container size: 1, Current depth: 49, Current state: (0L, 75L)

=== SOLUTION FOUND! ===
Search Algorithm: BFS
Time taken: 3 ms
Nodes explored: 197
Target 50L achieved in Jug 1

Solution path (98 steps):
------------------------------------------------------------
Step 0: Jug1=0L, Jug2=0L [Initial state (both jugs empty)]
Step 1: Jug1=101L, Jug2=0L [Fill Jug 1 (101L)]
Step 2: Jug1=2L, Jug2=99L [Jug 1 -> Jug 2 (99L)]
Step 3: Jug1=2L, Jug2=0L [Empty Jug 2]
Step 4: Jug1=0L, Jug2=2L [Jug 1 -> Jug 2 (2L)]
Step 5: Jug1=101L, Jug2=2L [Fill Jug 1 (101L)]
Step 6: Jug1=4L, Jug2=99L [Jug 1 -> Jug 2 (97L)]
Step 7: Jug1=4L, Jug2=0L [Empty Jug 2]
Step 8: Jug1=0L, Jug2=4L [Jug 1 -> Jug 2 (4L)]
Step 9: Jug1=101L, Jug2=4L [Fill Jug 1 (101L)]
Step 10: Jug1=6L, Jug2=99L [Jug 1 -> Jug 2 (95L)]
Step 11: Jug1=6L, Jug2=0L [Empty Jug 2]
Step 12: Jug1=0L, Jug2=6L [Jug 1 -> Jug 2 (6L)]
Step 13: Jug1=101L, Jug2=6L [Fill Jug 1 (101L)]
Step 14: Jug1=8L, Jug2=99L [Jug 1 -> Jug 2 (93L)]
Step 15: Jug1=8L, Jug2=0L [Empty Jug 2]
Step 16: Jug1=0L, Jug2=8L [Jug 1 -> Jug 2 (8L)]
Step 17: Jug1=101L, Jug2=8L [Fill Jug 1 (101L)]
Step 18: Jug1=10L, Jug2=99L [Jug 1 -> Jug 2 (91L)]
Step 19: Jug1=10L, Jug2=0L [Empty Jug 2]
Step 20: Jug1=0L, Jug2=10L [Jug 1 -> Jug 2 (10L)]
Step 21: Jug1=101L, Jug2=10L [Fill Jug 1 (101L)]
Step 22: Jug1=12L, Jug2=99L [Jug 1 -> Jug 2 (89L)]
Step 23: Jug1=12L, Jug2=0L [Empty Jug 2]
Step 24: Jug1=0L, Jug2=12L [Jug 1 -> Jug 2 (12L)]
Step 25: Jug1=101L, Jug2=12L [Fill Jug 1 (101L)]
Step 26: Jug1=14L, Jug2=99L [Jug 1 -> Jug 2 (87L)]
Step 27: Jug1=14L, Jug2=0L [Empty Jug 2]
Step 28: Jug1=0L, Jug2=14L [Jug 1 -> Jug 2 (14L)]
Step 29: Jug1=101L, Jug2=14L [Fill Jug 1 (101L)]
Step 30: Jug1=16L, Jug2=99L [Jug 1 -> Jug 2 (85L)]
Step 31: Jug1=16L, Jug2=0L [Empty Jug 2]
Step 32: Jug1=0L, Jug2=16L [Jug 1 -> Jug 2 (16L)]
Step 33: Jug1=101L, Jug2=16L [Fill Jug 1 (101L)]
Step 34: Jug1=18L, Jug2=99L [Jug 1 -> Jug 2 (83L)]
Step 35: Jug1=18L, Jug2=0L [Empty Jug 2]
Step 36: Jug1=0L, Jug2=18L [Jug 1 -> Jug 2 (18L)]
Step 37: Jug1=101L, Jug2=18L [Fill Jug 1 (101L)]
Step 38: Jug1=20L, Jug2=99L [Jug 1 -> Jug 2 (81L)]
Step 39: Jug1=20L, Jug2=0L [Empty Jug 2]
Step 40: Jug1=0L, Jug2=20L [Jug 1 -> Jug 2 (20L)]
Step 41: Jug1=101L, Jug2=20L [Fill Jug 1 (101L)]
Step 42: Jug1=22L, Jug2=99L [Jug 1 -> Jug 2 (79L)]
Step 43: Jug1=22L, Jug2=0L [Empty Jug 2]
Step 44: Jug1=0L, Jug2=22L [Jug 1 -> Jug 2 (22L)]
Step 45: Jug1=101L, Jug2=22L [Fill Jug 1 (101L)]
Step 46: Jug1=24L, Jug2=99L [Jug 1 -> Jug 2 (77L)]
Step 47: Jug1=24L, Jug2=0L [Empty Jug 2]
Step 48: Jug1=0L, Jug2=24L [Jug 1 -> Jug 2 (24L)]
Step 49: Jug1=101L, Jug2=24L [Fill Jug 1 (101L)]
Step 50: Jug1=26L, Jug2=99L [Jug 1 -> Jug 2 (75L)]
Step 51: Jug1=26L, Jug2=0L [Empty Jug 2]
Step 52: Jug1=0L, Jug2=26L [Jug 1 -> Jug 2 (26L)]
Step 53: Jug1=101L, Jug2=26L [Fill Jug 1 (101L)]
Step 54: Jug1=28L, Jug2=99L [Jug 1 -> Jug 2 (73L)]
Step 55: Jug1=28L, Jug2=0L [Empty Jug 2]
Step 56: Jug1=0L, Jug2=28L [Jug 1 -> Jug 2 (28L)]
Step 57: Jug1=101L, Jug2=28L [Fill Jug 1 (101L)]
Step 58: Jug1=30L, Jug2=99L [Jug 1 -> Jug 2 (71L)]
Step 59: Jug1=30L, Jug2=0L [Empty Jug 2]
Step 60: Jug1=0L, Jug2=30L [Jug 1 -> Jug 2 (30L)]
Step 61: Jug1=101L, Jug2=30L [Fill Jug 1 (101L)]
Step 62: Jug1=32L, Jug2=99L [Jug 1 -> Jug 2 (69L)]
Step 63: Jug1=32L, Jug2=0L [Empty Jug 2]
Step 64: Jug1=0L, Jug2=32L [Jug 1 -> Jug 2 (32L)]
Step 65: Jug1=101L, Jug2=32L [Fill Jug 1 (101L)]
Step 66: Jug1=34L, Jug2=99L [Jug 1 -> Jug 2 (67L)]
Step 67: Jug1=34L, Jug2=0L [Empty Jug 2]
Step 68: Jug1=0L, Jug2=34L [Jug 1 -> Jug 2 (34L)]
Step 69: Jug1=101L, Jug2=34L [Fill Jug 1 (101L)]
Step 70: Jug1=36L, Jug2=99L [Jug 1 -> Jug 2 (65L)]
Step 71: Jug1=36L, Jug2=0L [Empty Jug 2]
Step 72: Jug1=0L, Jug2=36L [Jug 1 -> Jug 2 (36L)]
Step 73: Jug1=101L, Jug2=36L [Fill Jug 1 (101L)]
Step 74: Jug1=38L, Jug2=99L [Jug 1 -> Jug 2 (63L)]
Step 75: Jug1=38L, Jug2=0L [Empty Jug 2]
Step 76: Jug1=0L, Jug2=38L [Jug 1 -> Jug 2 (38L)]
Step 77: Jug1=101L, Jug2=38L [Fill Jug 1 (101L)]
Step 78: Jug1=40L, Jug2=99L [Jug 1 -> Jug 2 (61L)]
Step 79: Jug1=40L, Jug2=0L [Empty Jug 2]
Step 80: Jug1=0L, Jug2=40L [Jug 1 -> Jug 2 (40L)]
Step 81: Jug1=101L, Jug2=40L [Fill Jug 1 (101L)]
Step 82: Jug1=42L, Jug2=99L [Jug 1 -> Jug 2 (59L)]
Step 83: Jug1=42L, Jug2=0L [Empty Jug 2]
Step 84: Jug1=0L, Jug2=42L [Jug 1 -> Jug 2 (42L)]
Step 85: Jug1=101L, Jug2=42L [Fill Jug 1 (101L)]
Step 86: Jug1=44L, Jug2=99L [Jug 1 -> Jug 2 (57L)]
Step 87: Jug1=44L, Jug2=0L [Empty Jug 2]
Step 88: Jug1=0L, Jug2=44L [Jug 1 -> Jug 2 (44L)]
Step 89: Jug1=101L, Jug2=44L [Fill Jug 1 (101L)]
Step 90: Jug1=46L, Jug2=99L [Jug 1 -> Jug 2 (55L)]
Step 91: Jug1=46L, Jug2=0L [Empty Jug 2]
Step 92: Jug1=0L, Jug2=46L [Jug 1 -> Jug 2 (46L)]
Step 93: Jug1=101L, Jug2=46L [Fill Jug 1 (101L)]
Step 94: Jug1=48L, Jug2=99L [Jug 1 -> Jug 2 (53L)]
Step 95: Jug1=48L, Jug2=0L [Empty Jug 2]
Step 96: Jug1=0L, Jug2=48L [Jug 1 -> Jug 2 (48L)]
Step 97: Jug1=101L, Jug2=48L [Fill Jug 1 (101L)]
Step 98: Jug1=50L, Jug2=99L [Jug 1 -> Jug 2 (51L)]
 *** TARGET ACHIEVED ***
```