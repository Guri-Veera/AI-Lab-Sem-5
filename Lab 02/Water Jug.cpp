#include <bits/stdc++.h>

int nodes = 1;              // Global Variable to track the number of nodes generated
const int MAX_DEPTH = 50;   // Maximum depth limit for the search algorithm

enum SearchType {
    DFS = 1,
    BFS = 2
};

struct State {
    int id;
    int jug1;       // Current water in jug 1
    int jug2;       // Current water in jug 2
    int parent;
    int depth;
    std::string action; // Description of action taken to reach this state
};

struct JugConfig {
    int capacity1;  // Capacity of jug 1
    int capacity2;  // Capacity of jug 2
    int target;     // Target amount to achieve
};

void GenMoves(State currState, std::deque<State> &container, std::unordered_set<std::string> &openSet, 
              std::unordered_set<std::string>& closed, std::unordered_map<int, State> &stateMap, 
              SearchType searchType, const JugConfig& config);
bool GoalTest(const State &currState, const JugConfig& config);
std::string stateToString(const State& s);

std::string stateToString(const State& s) {
    return std::to_string(s.jug1) + "," + std::to_string(s.jug2);
}

bool GoalTest(const State &currState, const JugConfig& config) {
    return currState.jug1 == config.target || currState.jug2 == config.target;
}

int main() {
    std::cout << "=== WATER JUG PROBLEM SOLVER ===\n\n";
    
    JugConfig config;
    
    // Get problem configuration from user
    std::cout << "Enter capacity of Jug 1: ";
    std::cin >> config.capacity1;
    std::cout << "Enter capacity of Jug 2: ";
    std::cin >> config.capacity2;
    std::cout << "Enter target amount: ";
    std::cin >> config.target;
    
    // Validate input
    if (config.target > std::max(config.capacity1, config.capacity2)) {
        std::cout << "Error: Target cannot be greater than the largest jug capacity!\n";
        return 1;
    }
    
    std::cout << "\nProblem: Find " << config.target << " liters using jugs of " 
              << config.capacity1 << "L and " << config.capacity2 << "L\n\n";
    
    // Choose search algorithm
    SearchType searchType;
    int choice;
    std::cout << "Choose search algorithm:\n";
    std::cout << "1. Depth-First Search (DFS)\n";
    std::cout << "2. Breadth-First Search (BFS)\n";
    std::cout << "Enter choice (1 or 2): ";
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
        default:
            searchType = DFS;
            std::cout << "Invalid choice. Using DFS by default.\n\n";
    }

    // Initialize starting state (both jugs empty)
    State initialState;
    initialState.id = 0;
    initialState.jug1 = 0;
    initialState.jug2 = 0;
    initialState.parent = -1;
    initialState.depth = 0;
    initialState.action = "Initial state (both jugs empty)";

    std::unordered_map<int, State> stateMap;    // Maps id to state. Useful to trace Path Taken by using parent's ID stored in the State
    stateMap[initialState.id] = initialState;
    
    // Using deque to support both stack (DFS) and queue (BFS) operations
    // Using container to track possible states
    std::deque<State> container;
    container.push_back(initialState);
    
    // Using unordered_set to track possible states
    // This is a duplicate of container, but it allows for O(1) average time complexity for lookups
    // Used in GenMoves() to spped up lookups
    std::unordered_set<std::string> openSet;
    openSet.insert(stateToString(initialState));

    bool solutionFound = false;
    std::unordered_set<std::string> closed;
    int nodesExplored = 0;      // Counter for nodes explored

    auto start_time = std::chrono::high_resolution_clock::now();    // Start timer to measure search time

    while (!container.empty()) {
        State currState;
        
        // DFS: take from back (stack behavior)
        if (searchType == DFS) {
            currState = container.back();
            container.pop_back();
        }
        // BFS: take from front (queue behavior)
        else {
            currState = container.front();
            container.pop_front();
        }
        
        openSet.erase(stateToString(currState));
        nodesExplored++;
        
        // Print progress every 100 nodes explored
        if (nodesExplored % 100 == 0) {
            std::cout << "Nodes explored: " << nodesExplored 
                      << ", Container size: " << container.size() 
                      << ", Current depth: " << currState.depth 
                      << ", Current state: (" << currState.jug1 << "L, " << currState.jug2 << "L)\n";
        }

        if (GoalTest(currState, config)) {
            solutionFound = true;
            auto end_time = std::chrono::high_resolution_clock::now();      // End timer when solution is found
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            
            std::cout << "\n=== SOLUTION FOUND! ===\n";
            std::cout << "Search Algorithm: " << (searchType == DFS ? "DFS" : "BFS") << std::endl;
            std::cout << "Time taken: " << duration.count() << " ms\n";
            std::cout << "Nodes explored: " << nodesExplored << std::endl;
            std::cout << "Target " << config.target << "L achieved in ";
            if (currState.jug1 == config.target) {
                std::cout << "Jug 1\n";
            } else {
                std::cout << "Jug 2\n";
            }
            
            std::vector<State> path;        // To reconstruct the path taken to reach the goal state
            while (currState.parent != -1) {
                path.push_back(currState);
                currState = stateMap[currState.parent];
            }
            path.push_back(currState);
            std::reverse(path.begin(), path.end());
            
            std::cout << "\nSolution path (" << path.size() - 1 << " steps):\n";
            std::cout << std::string(60, '-') << std::endl;
            
            for (size_t i = 0; i < path.size(); ++i) {
                const auto& state = path[i];
                std::cout << "Step " << i << ": ";
                std::cout << "Jug1=" << state.jug1 << "L, Jug2=" << state.jug2 << "L";
                if (i > 0) {
                    std::cout << " [" << state.action << "]";
                } else {
                    std::cout << " [" << state.action << "]";
                }
                
                // Highlight target achievement
                if (state.jug1 == config.target || state.jug2 == config.target) {
                    std::cout << '\n' << " *** TARGET ACHIEVED ***";
                }
                std::cout << std::endl;
            }
            std::cout << std::string(60, '-') << std::endl;
            
            break;
        }

        closed.insert(stateToString(currState));
        GenMoves(currState, container, openSet, closed, stateMap, searchType, config);
    }

    if (!solutionFound) {
        auto end_time = std::chrono::high_resolution_clock::now();      // End timer if no solution is found
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "\nNo solution found within depth limit of " << MAX_DEPTH << "!\n";
        std::cout << "Time taken: " << duration.count() << " ms\n";
        std::cout << "Nodes explored: " << nodesExplored << std::endl;
        
        // Check if solution is theoretically possible
        int gcd_val = std::__gcd(config.capacity1, config.capacity2);
        if (config.target % gcd_val != 0) {
            std::cout << "\nNote: This problem has no solution!\n";
            std::cout << "Target " << config.target << " is not achievable with jugs of capacity " 
                      << config.capacity1 << " and " << config.capacity2 << std::endl;
            std::cout << "For a solution to exist, target must be divisible by GCD(" 
                      << config.capacity1 << ", " << config.capacity2 << ") = " << gcd_val << std::endl;
        } else {
            std::cout << "\nSolution should exist but wasn't found within depth limit. Try increasing MAX_DEPTH.\n";
        }
    }
    
    return 0;
}

void GenMoves(State currState, std::deque<State> &container, std::unordered_set<std::string> &openSet, 
              std::unordered_set<std::string>& closed, std::unordered_map<int, State> &stateMap, 
              SearchType searchType, const JugConfig& config) {
    // Generate possible moves from the current state

    if (currState.depth >= MAX_DEPTH) return;       // Skip if we've reached maximum depth (applies to both DFS and BFS)
    
    std::vector<State> possibleMoves;
    
    // Action 1: Fill Jug 1
    if (currState.jug1 < config.capacity1) {
        State next = currState;
        next.jug1 = config.capacity1;
        next.action = "Fill Jug 1 (" + std::to_string(config.capacity1) + "L)";
        possibleMoves.push_back(next);
    }
    
    // Action 2: Fill Jug 2
    if (currState.jug2 < config.capacity2) {
        State next = currState;
        next.jug2 = config.capacity2;
        next.action = "Fill Jug 2 (" + std::to_string(config.capacity2) + "L)";
        possibleMoves.push_back(next);
    }
    
    // Action 3: Empty Jug 1
    if (currState.jug1 > 0) {
        State next = currState;
        next.jug1 = 0;
        next.action = "Empty Jug 1";
        possibleMoves.push_back(next);
    }
    
    // Action 4: Empty Jug 2
    if (currState.jug2 > 0) {
        State next = currState;
        next.jug2 = 0;
        next.action = "Empty Jug 2";
        possibleMoves.push_back(next);
    }
    
    // Action 5: Pour from Jug 1 to Jug 2
    if (currState.jug1 > 0 && currState.jug2 < config.capacity2) {
        State next = currState;
        int pourAmount = std::min(currState.jug1, config.capacity2 - currState.jug2);
        next.jug1 -= pourAmount;
        next.jug2 += pourAmount;
        next.action = "Jug 1 -> Jug 2 (" + std::to_string(pourAmount) + "L)";
        possibleMoves.push_back(next);
    }
    
    // Action 6: Pour from Jug 2 to Jug 1
    if (currState.jug2 > 0 && currState.jug1 < config.capacity1) {
        State next = currState;
        int pourAmount = std::min(currState.jug2, config.capacity1 - currState.jug1);
        next.jug2 -= pourAmount;
        next.jug1 += pourAmount;
        next.action = "Jug 2 -> Jug 1 (" + std::to_string(pourAmount) + "L)";
        possibleMoves.push_back(next);
    }
    
    // Process all possible moves
    for (auto& next : possibleMoves) {
        next.parent = currState.id;
        next.id = nodes++;
        next.depth = currState.depth + 1;
        
        std::string key = stateToString(next);
        
        if (openSet.find(key) == openSet.end() && closed.find(key) == closed.end()) {
            stateMap[next.id] = next;
            
            // DFS: add to back (stack behavior)
            // BFS: add to back, but we take from front (queue behavior)
            container.push_back(next);
            openSet.insert(key);
        }
    }
}