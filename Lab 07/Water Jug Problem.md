# Water Jug Problem Solver in Common Lisp

## Problem Statement
Design and implement a program in **Common Lisp** to solve the **Water Jug Problem** — 
a classic state-space search problem in Artificial Intelligence.  
Given a set of jugs with fixed capacities, the goal is to measure exactly a target amount of water by performing valid actions.

### Example
- Jugs: (8, 5, 3)
- Target: 4
- Start state: (0, 0, 0)
- Goal: Reach any state where one jug contains exactly 4 units of water.

Valid operations:
- **Fill** a jug completely.
- **Empty** a jug completely.
- **Pour** water from one jug to another until either the source is empty or the destination is full.

---

## Theory: State Space Search in Lisp

### 1. Background
The **Water Jug Problem** is a classic example of **state-space search** and is commonly used to illustrate **Breadth-First Search (BFS)** or **Depth-First Search (DFS)** algorithms.

Each state represents the current quantity of water in each jug.  
Transitions between states are produced by applying valid actions (fill, empty, pour).

Lisp, being a symbolic processing language, is ideal for AI search problems because it supports **dynamic data structures**, **recursion**, and **functional abstraction** naturally.

### 2. Representation of States
Each state is represented as a **list of integers**, e.g.:
```lisp
(8 0 0)   ; 8-liter jug full, others empty
```
The state space forms a **graph**, where each node is a state, and edges correspond to valid actions.

### 3. Operators / Actions
The valid operators are:
- `(fill-action state capacities i)` → Fill jug `i` completely.
- `(empty-action state i)` → Empty jug `i`.
- `(pour-action state capacities i j)` → Pour water from jug `i` to jug `j`.

These transitions generate new states, expanding the search space.

### 4. Search Algorithm (Breadth-First Search)
The algorithm explores all possible states starting from the initial state, using a **queue** to ensure the shortest path to the solution.

**Pseudocode:**
```lisp
Initialize queue with start state
Mark start state as visited
While queue not empty:
    Pop state from queue
    If state meets goal condition → return solution path
    For each neighbor (valid action applied):
        If neighbor not visited:
            Add neighbor to queue
            Record parent and action
If queue empties → no solution exists
```

BFS guarantees finding the **shortest sequence of actions** to reach the target.

### 5. Path Reconstruction
Once a goal state is reached, the algorithm reconstructs the path backward using a hash table that stores:
- Each state’s parent
- The action that led to the state

### 6. Why Lisp?
Lisp’s symbolic nature makes it particularly elegant for this kind of problem:
- Lists naturally represent states and transitions.
- Hash tables and recursion support efficient implementation.
- Code is compact yet expressive.

---

## Code Description

### Key Functions
| Function | Description |
|-----------|--------------|
| `(state->key state)` | Converts a list state to a string for hashing |
| `(goal-reached-p state target)` | Checks if target amount exists in any jug |
| `(fill-action state caps i)` | Fills jug `i` completely |
| `(empty-action state i)` | Empties jug `i` |
| `(pour-action state caps i j)` | Pours from jug `i` to jug `j` |
| `(neighbors-with-actions state caps)` | Generates all valid next states with action descriptions |
| `(reconstruct-path came-from goal-key)` | Rebuilds solution sequence |
| `(solve-jugs caps target &optional start-state)` | Performs BFS to find minimal sequence to reach target |
| `(pretty-print-solution solution)` | Displays readable sequence of steps |

---

## Algorithm
```lisp
(defun solve-jugs (caps target &optional (start-state nil))
  Initialize queue with start state (default: all zeros)
  Initialize hash tables for visited states and parent mapping
  While queue not empty:
    Dequeue state
    If goal reached: reconstruct and return path
    For each neighbor:
       If not visited:
          Mark visited
          Record parent and action
          Enqueue neighbor
  If queue empties → return NIL (no solution)
```

---

## Example Usage
```lisp
(let ((sol (solve-jugs '(8 5 3) 4)))
  (pretty-print-solution sol))
```
**Expected Output (sample):**
```
Solution (7 steps):
 0: Start -> (0 0 0)
 1: Fill 0 -> (8 0 0)
 2: Pour 0 -> 1 (5) -> (3 5 0)
 3: Empty 1 -> (3 0 0)
 4: Pour 0 -> 1 (3) -> (0 3 0)
 5: Fill 0 -> (8 3 0)
 6: Pour 0 -> 1 (2) -> (6 5 0)
 7: Pour 1 -> 2 (3) -> (6 2 3)
Goal reached: one jug has 4 liters!
```

---

## Remarks
- BFS ensures **optimal (shortest)** solution.
- Easily extensible to `N` jugs.
- Lisp provides concise, functional-style implementation.
- Demonstrates fundamental **AI search techniques** and **state representation**.

---

## Time and Space Complexity
- **Time:** \( O(b^d) \), where `b` is the branching factor and `d` is the depth of the solution.
- **Space:** \( O(b^d) \) due to BFS maintaining all visited states.

---

## Conclusion
This Lisp program elegantly models the **Water Jug Problem** using **state-space search** and **functional abstraction**, demonstrating Lisp’s strength in AI problem-solving and search algorithms.
