#include <bits/stdc++.h>

struct State {
    int id;
    int pos;
    int parent;
    int depth;
    int gCost;  // Cost from start to this node
    int hCost;  // Heuristic cost to goal
    int fCost;  // Total cost (g + h)
    
    State() : id(0), pos(0), parent(-1), depth(0), gCost(0), hCost(0), fCost(0) {}
};

class AStar {
private:
    std::vector<std::vector<int>> maze;
    int rows, cols;
    int startPos, goalPos;
    int nodeCounter;
    
    // Priority queue comparator for A* (lower f-cost has higher priority)
    struct Compare {
        bool operator()(const State& a, const State& b) const {
            if (a.fCost != b.fCost) return a.fCost > b.fCost;
            return a.hCost > b.hCost; // Tie-breaker: prefer lower h-cost
        }
    };
    
    std::priority_queue<State, std::vector<State>, Compare> openList;
    std::unordered_set<int> openSet;
    std::unordered_set<int> closedSet;
    std::unordered_map<int, State> allStates;
    
public:
    AStar(const std::vector<std::vector<int>>& inputMaze) 
        : maze(inputMaze), rows(inputMaze.size()), cols(inputMaze[0].size()), nodeCounter(1) {}
    
    int manhattan(int pos1, int pos2) {
        int r1 = pos1 / cols, c1 = pos1 % cols;
        int r2 = pos2 / cols, c2 = pos2 % cols;
        return abs(r1 - r2) + abs(c1 - c2);
    }
    
    bool isValid(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols && maze[row][col] != -1;
    }
    
    int posToIndex(int row, int col) {
        return row * cols + col;
    }
    
    std::pair<int, int> indexToPos(int index) {
        return {index / cols, index % cols};
    }
    
    std::vector<State> generateSuccessors(const State& current) {
        std::vector<State> successors;
        auto [row, col] = indexToPos(current.pos);
        
        // 8-directional movement (including diagonals)
        const std::vector<std::pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},        // Cardinal directions
            // {-1, -1}, {-1, 1}, {1, -1}, {1, 1}       // Diagonal directions
        };
        
        for (const auto& [dr, dc] : directions) {
            int newRow = row + dr;
            int newCol = col + dc;
            
            if (isValid(newRow, newCol)) {
                State successor;
                successor.id = nodeCounter++;
                successor.pos = posToIndex(newRow, newCol);
                successor.parent = current.id;
                successor.depth = current.depth + 1;
                
                // Cost calculation
                int moveCost = (abs(dr) + abs(dc) == 2) ? 14 : 10; // Diagonal = 14, Cardinal = 10
                successor.gCost = current.gCost + moveCost;
                successor.hCost = manhattan(successor.pos, goalPos) * 10;
                successor.fCost = successor.gCost + successor.hCost;
                
                successors.push_back(successor);
            }
        }
        
        return successors;
    }
    
    std::vector<int> reconstructPath(const State& goalState) {
        std::vector<int> path;
        int currentId = goalState.id;
        
        while (currentId != -1) {
            const State& state = allStates[currentId];
            path.push_back(state.pos);
            currentId = state.parent;
        }
        
        std::reverse(path.begin(), path.end());
        return path;
    }
    
    void printMazeWithPath(const std::vector<int>& path) {
        std::vector<std::vector<char>> display(rows, std::vector<char>(cols));
        
        // Fill the display maze
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (maze[i][j] == -1) {
                    display[i][j] = '#';  // Blocked
                } else {
                    display[i][j] = '.';  // Open
                }
            }
        }
        
        // Mark the path
        for (int pos : path) {
            auto [row, col] = indexToPos(pos);
            display[row][col] = '*';
        }
        
        // Mark start and goal
        auto [startRow, startCol] = indexToPos(startPos);
        auto [goalRow, goalCol] = indexToPos(goalPos);
        display[startRow][startCol] = 'S';
        display[goalRow][goalCol] = 'G';
        
        // Print the maze
        std::cout << "\nMaze with solution path:\n";
        std::cout << "S = Start, G = Goal, * = Path, # = Blocked, . = Open\n\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << display[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    bool solve(int start, int goal) {
        startPos = start;
        goalPos = goal;
        
        // Initialize start state
        State startState;
        startState.id = 0;
        startState.pos = startPos;
        startState.parent = -1;
        startState.depth = 0;
        startState.gCost = 0;
        startState.hCost = manhattan(startPos, goalPos) * 10;
        startState.fCost = startState.gCost + startState.hCost;
        
        openList.push(startState);
        openSet.insert(startState.pos);
        allStates[startState.id] = startState;
        
        int nodesExplored = 0;
        
        while (!openList.empty()) {
            State current = openList.top();
            openList.pop();
            
            openSet.erase(current.pos);
            closedSet.insert(current.pos);
            nodesExplored++;
            
            // Goal test
            if (current.pos == goalPos) {
                std::cout << "\nGoal reached!\n";
                std::cout << "Nodes explored: " << nodesExplored << std::endl;
                std::cout << "Path length: " << current.depth << std::endl;
                std::cout << "Path cost: " << current.gCost << std::endl;
                
                std::vector<int> path = reconstructPath(current);
                printMazeWithPath(path);
                
                std::cout << "\nPath coordinates: ";
                for (int pos : path) {
                    auto [row, col] = indexToPos(pos);
                    std::cout << "(" << row << "," << col << ") ";
                }
                std::cout << std::endl;
                
                return true;
            }
            
            // Progress update
            if (nodesExplored % 100 == 0) {
                std::cout << "Nodes explored: " << nodesExplored 
                         << ", Open list size: " << openList.size()
                         << ", Current f-cost: " << current.fCost << std::endl;
            }
            
            // Generate successors
            std::vector<State> successors = generateSuccessors(current);
            
            for (State& successor : successors) {
                // Skip if already in closed set
                if (closedSet.find(successor.pos) != closedSet.end()) {
                    continue;
                }
                
                // Check if this path to successor is better than any previous one
                bool inOpenSet = openSet.find(successor.pos) != openSet.end();
                bool betterPath = false;
                
                if (!inOpenSet) {
                    betterPath = true;
                } else {
                    // Find existing state with same position and compare costs
                    for (auto& [id, state] : allStates) {
                        if (state.pos == successor.pos && openSet.count(state.pos)) {
                            if (successor.gCost < state.gCost) {
                                betterPath = true;
                                break;
                            }
                        }
                    }
                }
                
                if (betterPath) {
                    allStates[successor.id] = successor;
                    if (!inOpenSet) {
                        openList.push(successor);
                        openSet.insert(successor.pos);
                    }
                }
            }
        }
        
        std::cout << "No path found to goal!" << std::endl;
        std::cout << "Nodes explored: " << nodesExplored << std::endl;
        return false;
    }
};

int main() {
    std::cout << "A* Maze Solver\n";
    std::cout << "Enter maze dimensions (rows cols): ";
    int rows, cols;
    std::cin >> rows >> cols;
    
    std::cout << "Enter maze (0 = open, -1 = blocked):\n";
    std::vector<std::vector<int>> maze(rows, std::vector<int>(cols));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> maze[i][j];
        }
    }
    
    std::cout << "Enter start position (row col): ";
    int startRow, startCol;
    std::cin >> startRow >> startCol;
    
    std::cout << "Enter goal position (row col): ";
    int goalRow, goalCol;
    std::cin >> goalRow >> goalCol;
    
    // Validate positions
    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols ||
        goalRow < 0 || goalRow >= rows || goalCol < 0 || goalCol >= cols) {
        std::cout << "Invalid start or goal position!" << std::endl;
        return 1;
    }
    
    if (maze[startRow][startCol] == -1 || maze[goalRow][goalCol] == -1) {
        std::cout << "Start or goal position is blocked!" << std::endl;
        return 1;
    }
    
    AStar solver(maze);
    int startPos = startRow * cols + startCol;
    int goalPos = goalRow * cols + goalCol;
    
    std::cout << "\nStarting A* search...\n";
    bool solved = solver.solve(startPos, goalPos);
    
    if (!solved) {
        std::cout << "Failed to find a path from start to goal." << std::endl;
    }
    
    return 0;
}