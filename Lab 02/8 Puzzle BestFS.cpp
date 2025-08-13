#include <bits/stdc++.h>

int nodes = 1;              // Global Variable to track the number of nodes generated. Used for path reconstruction
const int MAX_DEPTH = 50;   // Maximum depth limit for the search algorithm

enum SearchType {
    DFS = 1,
    BFS = 2,
    BESTFS = 3
};

struct State{
    int id;
    int arr[3][3];
    int parent;
    int depth;
    int heuristic;
};

// Forward declarations
void swap(int &a, int &b);
int findBlank(const State &currState);
bool GoalTest(const State &currState,const State &GoalState);
State GoalState;  // Make GoalState global so it can be accessed in GenMoves

std::string stateToString(const State& s) {
    std::string res;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            res += std::to_string(s.arr[i][j]);
    return res;
}

int misplacedTiles(const State& s, const State& goal) {             // Heuristic 1: Misplaced tiles
    int count = 0;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (s.arr[i][j] != 0 && s.arr[i][j] != goal.arr[i][j])
                count++;
        }
    }
    return count;
}

int manhattan(const State& s, const State& goal) {                  // Heuristic 2: Manhattan Distance
    int dist = 0;
    int posGoal[9][2];
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            posGoal[goal.arr[i][j]][0] = i, posGoal[goal.arr[i][j]][1] = j;

    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            int val = s.arr[i][j];
            if (val != 0) {
                dist += abs(i - posGoal[val][0]) + abs(j - posGoal[val][1]);
            }
        }
    }
    return dist;
}

int heuristicChoice = 1; // 1 for Manhattan, 2 for Misplaced Tiles

// Template function for GenMoves
template <typename Container>
void GenMoves(State currState, Container &container, std::unordered_set<std::string> &openSet, 
              std::unordered_set<std::string>& closed, std::unordered_map<int, State> &stateMap, SearchType searchType);

int main() {
    // Goal State Initialization
    GoalState.id = 0;
    GoalState.parent = -1;
    GoalState.depth = 0;

    int goal[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            GoalState.arr[i][j] = goal[i][j];
        }
    }

    // Multiple test cases with different difficulty levels
    // int inp[3][3] = {{1, 6, 4}, {3, 5, 0}, {8, 7, 2}};   // Unsolvable
    // int inp[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};      // Easy - 1 move
    // int inp[3][3] = {{1, 2, 3}, {4, 0, 5}, {7, 8, 6}};   // Moderate - 3 moves
    int inp[3][3] = {{6, 4, 7}, {8, 5, 0}, {3, 2, 1}};   // Hard
    
    // Choose search algorithm
    SearchType searchType;
    int choice;
    std::cout << "Enter Choice (1 for DFS, 2 for BFS, 3 for BestFS)\n";
    std::cin >> choice;
    
    switch(choice) {
        case 1:
            searchType = DFS;
            std::cout << "Using Depth-First Search (DFS)\n\n";
            break;
        case 2:
            searchType = BFS;
            std::cout << "Using Breadth-First Search (BFS)\n\n";
            break;
        case 3:
            searchType = BESTFS;
            // Choose heuristic for Best-First Search
            std::cout << "Choose heuristic for Best-First Search:\n";
            std::cout << "1. Manhattan Distance\n";
            std::cout << "2. Misplaced Tiles\n";
            std::cout << "Enter choice: ";
            std::cin >> heuristicChoice;
            
            if (heuristicChoice == 2) {
                std::cout << "Using Best-First Search (Greedy, Misplaced Tiles Heuristic)\n\n";
            } else {
                heuristicChoice = 1; // Default to Manhattan
                std::cout << "Using Best-First Search (Greedy, Manhattan Heuristic)\n\n";
            }
            break;
        default:
            searchType = DFS;
    }

    State initialState;
    initialState.id = 0;
    initialState.parent = -1;
    initialState.depth = 0;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            initialState.arr[i][j] = inp[i][j];
        }
    }

    // Compute initial heuristic for BestFS
    initialState.heuristic = manhattan(initialState, GoalState);

    std::unordered_map<int, State> stateMap;    // Maps id to state. Useful to trace Path Taken by using parent's ID stored in the State
    stateMap[initialState.id] = initialState;
    
    // Containers
    std::deque<State> container;   // DFS & BFS
    
    using PQ = std::priority_queue<State, std::vector<State>, 
                 std::function<bool(const State&, const State&)>>;
    PQ bestfs_container([](const State& a, const State& b){
        return a.heuristic > b.heuristic;                       // min-heap by heuristic
    });

    if (searchType == BESTFS) {
        bestfs_container.push(initialState);
    } else {
        container.push_back(initialState);
    }

    // Using unordered_set to track possible states
    // This is a duplicate of container, but it allows for O(1) average time complexity for lookups
    // Used in GenMoves() to speed up lookups
    std::unordered_set<std::string> openSet;
    openSet.insert(stateToString(initialState));

    bool flag = false;
    std::unordered_set<std::string> closed;
    int nodesExplored = 0;      // Counter for nodes explored

    auto start_time = std::chrono::high_resolution_clock::now();    // Start timer to measure search time

    while ((searchType == BESTFS ? !bestfs_container.empty() : !container.empty())) {
        State currState;
        
        if (searchType == DFS) {
            // DFS: take from back (stack behavior)
            currState = container.back();
            container.pop_back();
        }
        else if (searchType == BFS) {
            // BFS: take from front (queue behavior)
            currState = container.front();
            container.pop_front();
        }
        else if (searchType == BESTFS) {
            currState = bestfs_container.top();
            bestfs_container.pop();
        }

        openSet.erase(stateToString(currState));
        nodesExplored++;

        // Print progress every 1000 nodes explored
        if (nodesExplored % 1000 == 0) {
            if (searchType == BESTFS) {
                std::cout << "Nodes explored: " << nodesExplored << ", Container size: " << bestfs_container.size() 
                         << ", Current depth: " << currState.depth << ", Heuristic: " << currState.heuristic << std::endl;
            } else {
                std::cout << "Nodes explored: " << nodesExplored << ", Container size: " << container.size() 
                         << ", Current depth: " << currState.depth << std::endl;
            }
        }

        if (GoalTest(currState, GoalState)) {
            flag = true;
            auto end_time = std::chrono::high_resolution_clock::now();      // End timer when solution is found
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
            std::cout << "\n=== SOLUTION FOUND! ===\n";
            std::cout << "Search Algorithm: " 
                      << (searchType == DFS ? "DFS" : searchType == BFS ? "BFS" : "BestFS") 
                      << std::endl;
            std::cout << "Time taken: " << duration.count() << " ms\n";
            std::cout << "Nodes explored: " << nodesExplored << std::endl;
            
            std::vector<State> path;        // To reconstruct the path taken to reach the goal state
            while (currState.parent != -1) {
                path.push_back(currState);
                currState = stateMap[currState.parent];
            }
            path.push_back(currState);
            std::reverse(path.begin(), path.end());
            
            std::cout << "Solution length: " << path.size() - 1 << " moves\n";
            std::cout << "Total states in path: " << path.size() << "\n\n";
            
            std::cout << "Solution path:\n";
            for (size_t i = 0; i < path.size(); ++i) {
                const auto& state = path[i];
                std::cout << "Step " << i << " (State ID: " << state.id << ", Depth: " << state.depth;
                if (searchType == BESTFS) {
                    std::cout << ", Heuristic: " << state.heuristic;
                }
                std::cout << "):\n";
                for (int row = 0; row < 3; ++row) {
                    for (int col = 0; col < 3; ++col) {
                        if (state.arr[row][col] == 0) {
                            std::cout << "  ";
                        } else {
                            std::cout << state.arr[row][col] << " ";
                        }
                    }
                    std::cout << "\n";
                }
                std::cout << "\n";
            }
            break;
        }

        closed.insert(stateToString(currState));
        
        if (searchType == BESTFS) {
            GenMoves(currState, bestfs_container, openSet, closed, stateMap, searchType);
        } else {
            GenMoves(currState, container, openSet, closed, stateMap, searchType);
        }
    }

    if (flag == false) {
        auto end_time = std::chrono::high_resolution_clock::now();      // End timer if no solution is found
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "\nNo solution found within depth limit of " << MAX_DEPTH << "!\n";
        std::cout << "Time taken: " << duration.count() << " ms\n";
        std::cout << "Nodes explored: " << nodesExplored << std::endl;
    }
    
    return 0;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int findBlank(const State &currState) {
    // Find the index of the blank tile (0)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (currState.arr[i][j] == 0) {
                return i * 3 + j;
            }
        }
    }
    return -1;
}

bool GoalTest(const State &currState, const State &GoalState) {
    // Check if the current state matches the goal state
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (currState.arr[i][j] != GoalState.arr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename Container>
void GenMoves(State currState, Container &container, std::unordered_set<std::string> &openSet, 
              std::unordered_set<std::string>& closed, std::unordered_map<int, State> &stateMap, SearchType searchType) {
    // Generate possible moves from the current state
    if (currState.depth >= MAX_DEPTH && searchType != BESTFS)       // Skip if we've reached maximum depth (applies to both DFS and BFS)
        return;
    
    int blankIndex = findBlank(currState);
    int row = blankIndex / 3;
    int col = blankIndex % 3;

    // Movement directions: {row_delta, col_delta}
    const std::vector<std::pair<int, int>> directions = {
        {-1, 0}, // Up
        {1, 0},  // Down
        {0, -1}, // Left
        {0, 1}   // Right
    };

    for (const auto& direction : directions) {
        int dr = direction.first;
        int dc = direction.second;
        int newRow = row + dr;
        int newCol = col + dc;

        // Check bounds
        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            State next = currState;
            std::swap(next.arr[row][col], next.arr[newRow][newCol]);
            next.parent = currState.id;
            next.id = nodes++;
            next.depth = currState.depth + 1;

            std::string key = stateToString(next);

            if (openSet.find(key) == openSet.end() && closed.find(key) == closed.end()) {
                // compute heuristic only for BestFS
                if (searchType == BESTFS) {
                    next.heuristic = manhattan(next, GoalState);
                }

                stateMap[next.id] = next;
                
                // Handle different container types
                if constexpr (std::is_same_v<Container, std::deque<State>>) {
                    // DFS: add to back (stack behavior)
                    // BFS: add to back, but we take from front (queue behavior)
                    container.push_back(next);   // works for deque
                } else {
                    container.push(next);        // works for priority_queue
                }
                
                openSet.insert(key);
            }
        }
    }
}