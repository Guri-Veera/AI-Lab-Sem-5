# Block World Problem Solver in Prolog

## Introduction to Prolog

**Prolog (Programming in Logic)** is a declarative programming language widely used in **Artificial Intelligence** and **computational linguistics**.  
It uses logical relationships (facts and rules) and automatic backtracking to deduce solutions instead of explicit step-by-step instructions.

---

## Problem Statement

The **Block World Problem** involves a set of blocks (A, B, C, ...) that can be stacked on one another or placed on a table.  
The objective is to move from an **initial configuration** of blocks to a **goal configuration**, following the rules of valid moves:

1. A block can only be moved if there is **no other block on top of it** (it is *clear*).
2. A block can be moved **onto another clear block** or **onto the table**.
3. Only **one block** can be moved at a time.

### Example

**Initial State:**  
B on A, A on table  
→ `[on(a, table), on(b, a)]`

**Goal State:**  
A on B, B on table  
→ `[on(b, table), on(a, b)]`

---

## Algorithm Used: Depth-Limited Search (DFS)

The program implements a **Depth-Limited Depth-First Search (DFS)** algorithm to explore all possible moves in the search space until the goal state is reached or the maximum depth limit is exceeded.

### Algorithm Steps

1. **Start** with the initial configuration.
2. **Check** if the current state matches the goal. If yes, return the solution path.
3. **Generate** all valid next states by moving clear blocks.
4. **Recurse** into each new state (depth-first) while increasing the search depth.
5. **Stop** when the maximum depth is reached or no valid moves remain.
6. **Backtrack** to explore alternative moves if a dead end is reached.

This method ensures that the program avoids infinite recursion and redundant state exploration.

---

## Core Predicates

### 1. `solve_blocks(Start, Goal, Solution)`
Initializes depth-limited DFS search from `Start` to `Goal`.

### 2. `dfs(State, Goal, Path, FinalPath, CurrentDepth, MaxDepth)`
Performs recursive search up to `MaxDepth`.

### 3. `make_move(State, NewState, Move)`
Generates possible legal moves by moving a clear block either onto another block or the table.

### 4. `is_clear(Block, State)`
Checks if a block has no other block on top.

### 5. `same_state(State1, State2)`
Compares two configurations for equality (order-independent).

### 6. `print_solution(Moves)`
Prints the found sequence of moves in human-readable form.

---

## Example Runs

### Example 1: Solvable Case

**Initial:**  
B on A, A on table  
**Goal:**  
A on B, B on table  

Expected Output:
```
Initial: B on A, A on table
Goal: A on B, B on table

SOLUTION FOUND:
Move b to table
Move a onto b
```

---

### Example 2: Impossible Case

**Initial:**  
A, B, C all on table  
**Goal:**  
A on B, B on C, C on A  

Expected Output:
```
Initial: A, B, C all on table
Goal: A on B, B on C, C on A (impossible circle)

NO SOLUTION POSSIBLE
```

---

## Summary

| Concept | Description |
|----------|--------------|
| **Search Algorithm** | Depth-Limited DFS |
| **Goal Check** | State structure equality |
| **Move Rules** | Only clear blocks can be moved |
| **Output** | Human-readable move sequence |
| **Demonstrated Concepts** | State-space search, recursion, symbolic reasoning |

---