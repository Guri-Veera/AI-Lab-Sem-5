# Magic Square Generator in C++

## Problem Statement
A **magic square** of order `n` is an arrangement of `n × n` numbers such that the sum of every row, column, and both main diagonals is the same (called the **magic constant**).

- Works only for `$n >= 3`.
- Magic constant is given by:
  
$$
M = \frac{n(n^2 + 1)}{2}
$$

## Code Description

This program generates magic squares using two methods:
1. **Odd n (Siamese Method)** → Works for odd values of `n`.
2. **Doubly Even n (n % 4 == 0)** → Works for orders like 4, 8, 12, etc.

Singly even (n = 2 mod 4) is not implemented in this code.

## Functions
> Used to print the Magic Square
- ```cpp
  void printSquare(vector<vector<int>> &square)
  ```
> Used to solve the Magic Square for odd n (Siamese Method)
- ```cpp
  vector<vector<int>> generateOdd(int n)
  ```
> Used to solve the Magic Square for doubly-even n (n % 4) == 0
- ```cpp
  vector<vector<int>> generateDoublyEven(int n)
  ```

## Algorithm
```cpp
- Siamese Method
- Create an n×n matrix initialized with 0.
- Place 1 at position (row=0, col=n/2).
- For each next number from 2 to n^2:
    - Compute tentative position:
        - newRow = (row  1 + n) mod n
        - newCol = (col + 1) mod n
- If that cell is empty, place the number there.
- If not empty, move down one row from the previous position instead.
- Continue until all numbers are placed.

Doubly Even Method
- Fill an n×n matrix with numbers from 1 to n^2 in row-major order.
   (Row 1: 1 … n, Row 2: n+1 … 2n, etc.)
- Let maxNum = n^2.
- For each cell (i, j):
    - If (i % 4 == j % 4) OR ((i % 4 + j % 4) == 3)
        - Replace square[i][j] with its complement:
            - square[i][j] = maxNum + 1  square[i][j]
- Resulting matrix is a magic square.

- Input n
- If n < 3:
    - Exit
- magicConstant = n * (n^2 + 1) / 2
- Print magicConstant
- If n is odd:
    - Call Siamese method to generate square
- Else if n % 4 == 0:
    - Call Doubly-even method to generate square
- Else:
    - Print "Singly-even not implemented"
    - Exit
- Print the generated square 
```


## Example Usage

> Input
```cpp
Enter n (size of magic square): 5
```

> Output
```
Magic constant (sum of each row/column/diagonal): 65

  17   24    1    8   15 
  23    5    7   14   16 
   4    6   13   20   22 
  10   12   19   21    3 
  11   18   25    2    9
```

---

> Input
```cpp
Enter n (size of magic square): 4
```

> Output
```
Magic constant (sum of each row/column/diagonal): 34

  16   2   3  13
   5  11  10   8
   9   7   6  12
   4  14  15   1
```