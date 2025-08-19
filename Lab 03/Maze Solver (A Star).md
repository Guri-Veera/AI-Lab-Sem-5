# Maze Solver (A*) in C++

## Problem Statement:
Given a 2D maze of size rows × cols, where some cells are blocked (-1) and others are open (0), the goal is to find the shortest path from a given start cell to a goal cell. Movement is allowed in four cardinal directions (up, down, left, right). The algorithm should compute the path with minimum cost using A* search with the Manhattan distance heuristic.

### Example Maze
```cpp
std::vector<std::vector<int>> maze = {
{0,  0,  0, -1,  0},
{-1, 0,  0, -1,  0},
{0,  0,  0,  0,  0},
{0, -1, -1,  0,  0},
{0,  0,  0, -1,  0},
}

0 → Open cell
-1 → Blocked cell
S → Start position
G → Goal position
```

## Code Description
The code solves the maze using A* search

Data Structures Used:

- Class `State`: Represents a node in the search tree, storing:
- `id` → Unique identifier
- `pos` → Cell index (row * cols + col)
- `parent` → Parent node ID (for path reconstruction)
- `depth` → Depth of node
- `gCost` → Cost from start to this node
- `hCost` → Heuristic cost to goal
- `fCost` → Total cost (`gCost + hCost`)
- Priority Queue `openList`: Stores nodes to explore, ordered by `fCost`
- Unordered Sets `openSet` and `closedSet`: Track visited nodes for O(1) lookup
- Map `allStates`: Maps node ID to `State` for reconstructing the path

## Functions
> Used to find manhattan distance between 2 cells
- ```cpp
  int manhattan(int pos1, int pos2)
  ```
> Checks if a cell is within bounds and open
- ```cpp
  bool isValid(int row, int col)
  ```
> Generates valid next moves
- ```cpp
  std::vector<State> generateSuccessors(const State& current)
  ```
> Reconstructs path from start to goal using parent IDs
- ```cpp
  std::vector<int> reconstructPath(const State& goalState)
  ```
> Prints maze with solution path marked
- ```cpp
  void printMazeWithPath(const std::vector<int>& path)
  ```
> Runs A* search and returns true if goal is reachable
- ```cpp
  bool solve(int start, int goal)
  ```

## Algorithm
```
A* Search Algorithm
- Initialize start state with gCost=0, hCost=Manhattan(start, goal), fCost=g+h
- Push start state into priority queue (openList) and openSet
- While openList is not empty:
    - Pop state with lowest fCost
    - If state is goal, reconstruct path and terminate
    - Mark state as visited (move from openSet to closedSet)
    - Generate successors of current state
    - For each successor:
        - Skip if already in closedSet
        - If not in openSet, add to openList and openSet
        - If in openSet, check if new gCost is lower → update state
- If openList becomes empty, no path exists
- Return the reconstructed path (if found)
```

## Comments
### Time Complexity
- A* depends on branching factor b and solution depth d:
- **Worst Case:** $O(b^d)$ (all nodes explored)
- **Best Case:** $O(d)$ (direct path with heuristic guidance)
- **Average Case:** Heuristic usually reduces explored nodes significantly

### Space Complexity
- **Open List:** $O(b^d)$ in worst case (stores frontier nodes)
- **Closed Set:** $O(n)$ (all reachable nodes)
- **State Map:** $O(n)$ (stores all nodes for path reconstruction)

### General Remarks
- A* guarantees optimal path if the heuristic is admissible (Manhattan distance is admissible for 4-direction movement)
- Using a priority queue ensures nodes with lowest `fCost` are explored first
- Memory usage grows with number of open nodes, especially in large mazes

## Example Usage
> Input
```cpp
std::vector<std::vector<int>> maze = {
{0,  0,  0, -1,  0},
{-1, 0,  0, -1,  0},
{0,  0,  0,  0,  0},
{0, -1, -1,  0,  0},
{0,  0,  0, -1,  0},
}
```

>Output
```cpp
A* Maze Solver
Enter maze dimensions (rows cols): 5 5
Enter maze (0 = open, -1 = blocked):
0  0  0 -1  0
-1 0  0 -1  0
0  0  0  0  0
0 -1 -1  0  0
0  0  0 -1  0
Enter start position (row col): 0 0
Enter goal position (row col): 4 4

Starting A* search...

Goal reached!
Nodes explored: 9
Path length: 8
Path cost: 80

Maze with solution path:
S = Start, G = Goal, * = Path, # = Blocked, . = Open

S * . # .
# * . # .
. * * * .
. # # * *
. . . # G

Path coordinates: (0,0) (0,1) (1,1) (2,1) (2,2) (2,3) (3,3) (3,4) (4,4)
```