# 8 Puzzle Problem Solution in C++ (DFS and BFS)

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
The code solves the 8 Puzzle Problem via both DFS and BFS (user has the option to choose at run-time). It then generates a tree of corresponding states from a given board configuration, by moving the empty space left, right, down and up (within constraints of the board size)

Data Structures Used:
- **Enum**  `SearchType` to provide choice to the user between DFS and BFS
- **Structure** `State` with member variables -- `int id`, `int arr[3][3]`, `int parent`, `int depth` to keep track of states
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
> Used to find the position of the empty space in the matrix
- ```cpp
  int findBlank(const State &currState)
  ```
> Used to check if a state has reached the Goal State (element-wise comparison)
- ```cpp
  bool GoalTest(const State &currState, const State &GoalState)
  ```
> Used to generate all possible moves from a given board configuration
- ```cpp
  void GenMoves(struct State currState, std::deque<State> &container, std::unordered_set<std::string> &openSet, std::unordered_set<std::string>& closed, std::unordered_map<int, State> &stateMap, SearchType searchType)
  ```  

## Algorithm
```cpp
struct State {
    int arr[3][3];      // Current state of the array
    int id;             // Identifier for the state
    int parent;         // Parent state ID
    int depth;          // Depth in the search tree
};

const int MAX_DEPTH = 50;   // Maximum depth limit for the search
int nodes = 1;

Solution() {

	searchType = DFS or BFS

    State initialState
    initialState.arr = Input Array
    initialState.id = 0
    initialState.parent = -1
    initialState.depth = 0

    Similar to the initial state, define the goal state
    
    Initialize "container" for possible states (to be explored) (Stack for DFS or Queue for BFS) (I use Deque to simulate both simultaneously)
    container.push(initialState);

    Initialize unordered set openSet for possible states (Duplicate of "container" but better for quick lookup)
    openSet.insert(stateToString(initialState));    // stateToString converts a unique state to a unique string representation for easy comparison
    
    Initialize unorderd map "stateMap" for storing states (to track path of visitied states)
    stateMap[initialState.id] = initialState;

    Initialize unordered set "closed" for closed states (to avoid revisiting)

    int nodesExplored = 0;  // Counter for nodes explored
    flag = false            // Solution found or not

    while(container is not empty) {
        For DFS,
            currState = container.back()
            container.pop_back()

        For BFS,
            currState = container.front()
            container.pop_front()

        openSet.erase(stateToString(currState));
        nodesExplored++;

        if (GoalTest(currState)) {
            flag = True
            print("Solution Found!")
            PrintSolution(currState, StateMap)
            break
        }

        closed.insert(currState)
        Generate_Possible_Moves(currState, container, closed, stateMap, searchType)
    }

    if (flag == false)
        print("No Solution Found within specified Depth Limit (MAX_DEPTH)")

}

Find_Blank_Index(currState) {
    for (int i = 1 to 3) {
        for (int j = 1 to 3) {
            if (currState.arr[i][j] == 0)
                return {i, j}
        }
    }
}

Goal_Test(currState, GoalState) {
    for (int i = 1 to 3) {
        for (int j = 1 to 3) {
            if (currState.arr[i][j] != GoalState.arr[i][j])
                return false
        }
    }
    return true
}

Generate_Possible_Moves(currState, container, closed, stateMap, searchType) {
    if currState.depth >= MAX_DEPTH
        return // Stop if maximum depth is reached

    int x, y = Find_Blank_Index(currState)
    movement_dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} // Up, Down, Left, Right

    for (direction in movement_dirs) {
        newX = x + direction[0]
        newY = y + direction[1]

        if (nextRow < 1 || nextRow > 3 || nextCol < 1 || nextCol > 3)
            continue; // Skip out of bounds
        
        nextState = currState; // Create a copy of the current state
        swap(next.arr[x][y], next.arr[newX][newY])
        nextState.id = nodes++
        nextState.parent = currState.id
        nextState.depth = currState.depth + 1

        if (nextState not in closed && nextState not in container)
            stateMap[next.id] = nextState
            container.push(nextState)
    }
}

PrintSolution(currState, stateMap) {
    std::vector<State> path;    // Vector to store the path from initial state to goal state
    while(currState.parent != -1) {
        path.push(currState);
        currState = stateMap[currState.parent];
    }
    path.push(currState);
    std::reverse(path.begin(), path.end());

    for (int i = 0 to path.size()) {
        state = path[i];
        print("Step ", i)
        for (int j = 1 to 3) {
            for (int k = 1 to 3) {
                if (state.arr[j][k] == 0) {
                    print("  ");
                }
                else {
                    print(state.arr[j][k], " ");
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
```

## Comments
### Time Complexity
#### DFS (Depth-First Search)
- **Best Case:** $O(d)$ where $d$ is depth of solution
- **Worst Case:** $O(b^m)$ where $b=4$ (branching factor), $m=$ MAX_DEPTH
- **Upper Limit:** $O(n!)=O(362,880)$ but due to constraints like `closed` list, this number is often not reached (if solution exists)
- **Average Case:** $O(b^d)$ where $d$ is solution depth
- **Note:** May find very long paths before optimal solution

#### BFS (Breadth-First Search)
- **Time Complexity:** $O(b^d)$ where $b=4$, $d=$ solution depth
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

### General Remarks
- DFS, in most cases, does not provide optimal solutions as it explores all options in a specific branch of the tree which may result in thouands or millions of operations before moving to the next branch.
- However, BFS is guaranteed to find the most optimal solution as it searches all possible states after a certain number of moves (depth k), before making a new move (depth k+1)
- Example: For the input of `{{6, 4, 7}, {8, 5, 0}, {3, 2, 1}}`, DFS without a MAX_DEPTH constraint found a solution in 24,250 moves, with MAX_DEPTH=50, in 48 moves, whereas BFS took 31 moves.

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
Enter Choice (1 for DFS or 2 for BFS)
2
Using Breadth-First Search (BFS)

Nodes explored: 1000, Container size: 614, Current depth: 11
Nodes explored: 2000, Container size: 1327, Current depth: 12
Nodes explored: 3000, Container size: 1690, Current depth: 13
Nodes explored: 4000, Container size: 2339, Current depth: 14
Nodes explored: 5000, Container size: 3142, Current depth: 14
Nodes explored: 6000, Container size: 3545, Current depth: 15
Nodes explored: 7000, Container size: 3845, Current depth: 15
Nodes explored: 8000, Container size: 4108, Current depth: 15
Nodes explored: 9000, Container size: 4612, Current depth: 16
Nodes explored: 10000, Container size: 5373, Current depth: 16
Nodes explored: 11000, Container size: 6113, Current depth: 16
Nodes explored: 12000, Container size: 6840, Current depth: 16
Nodes explored: 13000, Container size: 7427, Current depth: 17
Nodes explored: 14000, Container size: 7660, Current depth: 17
Nodes explored: 15000, Container size: 7899, Current depth: 17
Nodes explored: 16000, Container size: 8088, Current depth: 17
Nodes explored: 17000, Container size: 8218, Current depth: 17
Nodes explored: 18000, Container size: 8372, Current depth: 17
Nodes explored: 19000, Container size: 8514, Current depth: 17
Nodes explored: 20000, Container size: 8615, Current depth: 18
Nodes explored: 21000, Container size: 9273, Current depth: 18
Nodes explored: 22000, Container size: 9914, Current depth: 18
Nodes explored: 23000, Container size: 10537, Current depth: 18
Nodes explored: 24000, Container size: 11196, Current depth: 18
Nodes explored: 25000, Container size: 11842, Current depth: 18
Nodes explored: 26000, Container size: 12457, Current depth: 18
Nodes explored: 27000, Container size: 13036, Current depth: 18
Nodes explored: 28000, Container size: 13597, Current depth: 18
Nodes explored: 29000, Container size: 14029, Current depth: 19
Nodes explored: 30000, Container size: 14229, Current depth: 19
Nodes explored: 31000, Container size: 14324, Current depth: 19
Nodes explored: 32000, Container size: 14421, Current depth: 19
Nodes explored: 33000, Container size: 14555, Current depth: 19
Nodes explored: 34000, Container size: 14662, Current depth: 19
Nodes explored: 35000, Container size: 14716, Current depth: 19
Nodes explored: 36000, Container size: 14743, Current depth: 19
Nodes explored: 37000, Container size: 14800, Current depth: 19
Nodes explored: 38000, Container size: 14817, Current depth: 19
Nodes explored: 39000, Container size: 14793, Current depth: 19
Nodes explored: 40000, Container size: 14792, Current depth: 19
Nodes explored: 41000, Container size: 14783, Current depth: 19
Nodes explored: 42000, Container size: 14764, Current depth: 19
Nodes explored: 43000, Container size: 14949, Current depth: 20
Nodes explored: 44000, Container size: 15471, Current depth: 20
Nodes explored: 45000, Container size: 15996, Current depth: 20
Nodes explored: 46000, Container size: 16446, Current depth: 20
Nodes explored: 47000, Container size: 16945, Current depth: 20
Nodes explored: 48000, Container size: 17455, Current depth: 20
Nodes explored: 49000, Container size: 17955, Current depth: 20
Nodes explored: 50000, Container size: 18417, Current depth: 20
Nodes explored: 51000, Container size: 18880, Current depth: 20
Nodes explored: 52000, Container size: 19346, Current depth: 20
Nodes explored: 53000, Container size: 19865, Current depth: 20
Nodes explored: 54000, Container size: 20345, Current depth: 20
Nodes explored: 55000, Container size: 20798, Current depth: 20
Nodes explored: 56000, Container size: 21215, Current depth: 20
Nodes explored: 57000, Container size: 21627, Current depth: 20
Nodes explored: 58000, Container size: 21770, Current depth: 21
Nodes explored: 59000, Container size: 21763, Current depth: 21
Nodes explored: 60000, Container size: 21810, Current depth: 21
Nodes explored: 61000, Container size: 21790, Current depth: 21
Nodes explored: 62000, Container size: 21764, Current depth: 21
Nodes explored: 63000, Container size: 21714, Current depth: 21
Nodes explored: 64000, Container size: 21690, Current depth: 21
Nodes explored: 65000, Container size: 21659, Current depth: 21
Nodes explored: 66000, Container size: 21596, Current depth: 21
Nodes explored: 67000, Container size: 21533, Current depth: 21
Nodes explored: 68000, Container size: 21464, Current depth: 21
Nodes explored: 69000, Container size: 21317, Current depth: 21
Nodes explored: 70000, Container size: 21233, Current depth: 21
Nodes explored: 71000, Container size: 21124, Current depth: 21
Nodes explored: 72000, Container size: 20976, Current depth: 21
Nodes explored: 73000, Container size: 20809, Current depth: 21
Nodes explored: 74000, Container size: 20688, Current depth: 21
Nodes explored: 75000, Container size: 20516, Current depth: 21
Nodes explored: 76000, Container size: 20351, Current depth: 21
Nodes explored: 77000, Container size: 20206, Current depth: 21
Nodes explored: 78000, Container size: 20021, Current depth: 21
Nodes explored: 79000, Container size: 19858, Current depth: 22
Nodes explored: 80000, Container size: 20179, Current depth: 22
Nodes explored: 81000, Container size: 20578, Current depth: 22
Nodes explored: 82000, Container size: 20894, Current depth: 22
Nodes explored: 83000, Container size: 21183, Current depth: 22
Nodes explored: 84000, Container size: 21465, Current depth: 22
Nodes explored: 85000, Container size: 21731, Current depth: 22
Nodes explored: 86000, Container size: 22042, Current depth: 22
Nodes explored: 87000, Container size: 22347, Current depth: 22
Nodes explored: 88000, Container size: 22662, Current depth: 22
Nodes explored: 89000, Container size: 22949, Current depth: 22
Nodes explored: 90000, Container size: 23191, Current depth: 22
Nodes explored: 91000, Container size: 23460, Current depth: 22
Nodes explored: 92000, Container size: 23732, Current depth: 22
Nodes explored: 93000, Container size: 24034, Current depth: 22
Nodes explored: 94000, Container size: 24260, Current depth: 22
Nodes explored: 95000, Container size: 24513, Current depth: 22
Nodes explored: 96000, Container size: 24708, Current depth: 22
Nodes explored: 97000, Container size: 24886, Current depth: 22
Nodes explored: 98000, Container size: 25034, Current depth: 22
Nodes explored: 99000, Container size: 25118, Current depth: 23
Nodes explored: 100000, Container size: 24957, Current depth: 23
Nodes explored: 101000, Container size: 24851, Current depth: 23
Nodes explored: 102000, Container size: 24738, Current depth: 23
Nodes explored: 103000, Container size: 24539, Current depth: 23
Nodes explored: 104000, Container size: 24333, Current depth: 23
Nodes explored: 105000, Container size: 24133, Current depth: 23
Nodes explored: 106000, Container size: 23910, Current depth: 23
Nodes explored: 107000, Container size: 23640, Current depth: 23
Nodes explored: 108000, Container size: 23343, Current depth: 23
Nodes explored: 109000, Container size: 23093, Current depth: 23
Nodes explored: 110000, Container size: 22866, Current depth: 23
Nodes explored: 111000, Container size: 22613, Current depth: 23
Nodes explored: 112000, Container size: 22355, Current depth: 23
Nodes explored: 113000, Container size: 22076, Current depth: 23
Nodes explored: 114000, Container size: 21795, Current depth: 23
Nodes explored: 115000, Container size: 21425, Current depth: 23
Nodes explored: 116000, Container size: 21110, Current depth: 23
Nodes explored: 117000, Container size: 20799, Current depth: 23
Nodes explored: 118000, Container size: 20442, Current depth: 23
Nodes explored: 119000, Container size: 20045, Current depth: 23
Nodes explored: 120000, Container size: 19702, Current depth: 23
Nodes explored: 121000, Container size: 19366, Current depth: 23
Nodes explored: 122000, Container size: 18949, Current depth: 23
Nodes explored: 123000, Container size: 18575, Current depth: 23
Nodes explored: 124000, Container size: 18227, Current depth: 24
Nodes explored: 125000, Container size: 18395, Current depth: 24
Nodes explored: 126000, Container size: 18515, Current depth: 24
Nodes explored: 127000, Container size: 18652, Current depth: 24
Nodes explored: 128000, Container size: 18750, Current depth: 24
Nodes explored: 129000, Container size: 18809, Current depth: 24
Nodes explored: 130000, Container size: 18863, Current depth: 24
Nodes explored: 131000, Container size: 18984, Current depth: 24
Nodes explored: 132000, Container size: 19074, Current depth: 24
Nodes explored: 133000, Container size: 19143, Current depth: 24
Nodes explored: 134000, Container size: 19216, Current depth: 24
Nodes explored: 135000, Container size: 19237, Current depth: 24
Nodes explored: 136000, Container size: 19238, Current depth: 24
Nodes explored: 137000, Container size: 19241, Current depth: 24
Nodes explored: 138000, Container size: 19230, Current depth: 24
Nodes explored: 139000, Container size: 19208, Current depth: 24
Nodes explored: 140000, Container size: 19137, Current depth: 24
Nodes explored: 141000, Container size: 19076, Current depth: 24
Nodes explored: 142000, Container size: 18993, Current depth: 24
Nodes explored: 143000, Container size: 18708, Current depth: 25
Nodes explored: 144000, Container size: 18385, Current depth: 25
Nodes explored: 145000, Container size: 17953, Current depth: 25
Nodes explored: 146000, Container size: 17551, Current depth: 25
Nodes explored: 147000, Container size: 17126, Current depth: 25
Nodes explored: 148000, Container size: 16695, Current depth: 25
Nodes explored: 149000, Container size: 16270, Current depth: 25
Nodes explored: 150000, Container size: 15839, Current depth: 25
Nodes explored: 151000, Container size: 15419, Current depth: 25
Nodes explored: 152000, Container size: 14963, Current depth: 25
Nodes explored: 153000, Container size: 14472, Current depth: 25
Nodes explored: 154000, Container size: 13949, Current depth: 25
Nodes explored: 155000, Container size: 13436, Current depth: 25
Nodes explored: 156000, Container size: 12927, Current depth: 25
Nodes explored: 157000, Container size: 12395, Current depth: 25
Nodes explored: 158000, Container size: 11796, Current depth: 25
Nodes explored: 159000, Container size: 11227, Current depth: 25
Nodes explored: 160000, Container size: 10602, Current depth: 25
Nodes explored: 161000, Container size: 9975, Current depth: 25
Nodes explored: 162000, Container size: 9790, Current depth: 26
Nodes explored: 163000, Container size: 9622, Current depth: 26
Nodes explored: 164000, Container size: 9441, Current depth: 26
Nodes explored: 165000, Container size: 9207, Current depth: 26
Nodes explored: 166000, Container size: 8980, Current depth: 26
Nodes explored: 167000, Container size: 8765, Current depth: 26
Nodes explored: 168000, Container size: 8438, Current depth: 26
Nodes explored: 169000, Container size: 8159, Current depth: 26
Nodes explored: 170000, Container size: 7799, Current depth: 26
Nodes explored: 171000, Container size: 7353, Current depth: 27
Nodes explored: 172000, Container size: 6746, Current depth: 27
Nodes explored: 173000, Container size: 6125, Current depth: 27
Nodes explored: 174000, Container size: 5462, Current depth: 27
Nodes explored: 175000, Container size: 4762, Current depth: 27
Nodes explored: 176000, Container size: 4051, Current depth: 27
Nodes explored: 177000, Container size: 3276, Current depth: 27
Nodes explored: 178000, Container size: 2405, Current depth: 27
Nodes explored: 179000, Container size: 1769, Current depth: 28
Nodes explored: 180000, Container size: 1173, Current depth: 28
Nodes explored: 181000, Container size: 424, Current depth: 29

=== SOLUTION FOUND! ===
Search Algorithm: BFS
Time taken: 1995 ms
Nodes explored: 181440
Solution length: 31 moves
Total states in path: 32

Solution path:
Step 0 (State ID: 0, Depth: 0):
6 4 7
8 5
3 2 1

Step 1 (State ID: 1, Depth: 1):
6 4
8 5 7
3 2 1

Step 2 (State ID: 5, Depth: 2):
6   4
8 5 7
3 2 1

Step 3 (State ID: 12, Depth: 3):
6 5 4
8   7
3 2 1

Step 4 (State ID: 29, Depth: 4):
6 5 4
  8 7
3 2 1

Step 5 (State ID: 55, Depth: 5):
6 5 4
3 8 7
  2 1

Step 6 (State ID: 100, Depth: 6):
6 5 4
3 8 7
2   1

Step 7 (State ID: 174, Depth: 7):
6 5 4
3   7
2 8 1

Step 8 (State ID: 312, Depth: 8):
6 5 4
3 7
2 8 1

Step 9 (State ID: 530, Depth: 9):
6 5 4
3 7 1
2 8

Step 10 (State ID: 868, Depth: 10):
6 5 4
3 7 1
2   8

Step 11 (State ID: 1402, Depth: 11):
6 5 4
3   1
2 7 8

Step 12 (State ID: 2289, Depth: 12):
6   4
3 5 1
2 7 8

Step 13 (State ID: 3697, Depth: 13):
  6 4
3 5 1
2 7 8

Step 14 (State ID: 6005, Depth: 14):
3 6 4
  5 1
2 7 8

Step 15 (State ID: 9588, Depth: 15):
3 6 4
2 5 1
  7 8

Step 16 (State ID: 15330, Depth: 16):
3 6 4
2 5 1
7   8

Step 17 (State ID: 24007, Depth: 17):
3 6 4
2   1
7 5 8

Step 18 (State ID: 37289, Depth: 18):
3 6 4
2 1
7 5 8

Step 19 (State ID: 56500, Depth: 19):
3 6
2 1 4
7 5 8

Step 20 (State ID: 83543, Depth: 20):
3   6
2 1 4
7 5 8

Step 21 (State ID: 119562, Depth: 21):
  3 6
2 1 4
7 5 8

Step 22 (State ID: 165207, Depth: 22):
2 3 6
  1 4
7 5 8

Step 23 (State ID: 220101, Depth: 23):
2 3 6
1   4
7 5 8

Step 24 (State ID: 280365, Depth: 24):
2 3 6
1 4
7 5 8

Step 25 (State ID: 341172, Depth: 25):
2 3
1 4 6
7 5 8

Step 26 (State ID: 394494, Depth: 26):
2   3
1 4 6
7 5 8

Step 27 (State ID: 437079, Depth: 27):
  2 3
1 4 6
7 5 8

Step 28 (State ID: 463864, Depth: 28):
1 2 3
  4 6
7 5 8

Step 29 (State ID: 477920, Depth: 29):
1 2 3
4   6
7 5 8

Step 30 (State ID: 482462, Depth: 30):
1 2 3
4 5 6
7   8

Step 31 (State ID: 483752, Depth: 31):
1 2 3
4 5 6
7 8

```