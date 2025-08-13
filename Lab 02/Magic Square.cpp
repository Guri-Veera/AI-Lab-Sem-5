#include <bits/stdc++.h>
using namespace std;

// Function to print the magic square
void printSquare(vector<vector<int>> &square) {
    int n = square.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(4) << square[i][j] << " ";
        cout << "\n";
    }
}

// Siamese method for odd n
vector<vector<int>> generateOdd(int n) {
    vector<vector<int>> square(n, vector<int>(n, 0));
    int i = 0, j = n / 2;

    for (int num = 1; num <= n * n; num++) {
        square[i][j] = num;
        int newi = (i - 1 + n) % n;
        int newj = (j + 1) % n;

        if (square[newi][newj])
            i = (i + 1) % n;
        else {
            i = newi;
            j = newj;
        }
    }
    return square;
}

// Doubly even magic square (n % 4 == 0)
vector<vector<int>> generateDoublyEven(int n) {
    vector<vector<int>> square(n, vector<int>(n));
    int num = 1, maxNum = n * n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            square[i][j] = num++;

    // Replace values at certain positions with complementary numbers
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i % 4 == j % 4) || ((i % 4 + j % 4) == 3))
                square[i][j] = maxNum + 1 - square[i][j];
        }
    }
    return square;
}

int main() {
    int n;
    cout << "Enter n (size of magic square): ";
    cin >> n;

    if (n < 3) {
        cout << "Magic square not possible for n < 3\n";
        return 0;
    }

    int magicConstant = n * (n * n + 1) / 2;
    cout << "Magic constant (sum of each row/column/diagonal): " 
         << magicConstant << "\n\n";

    vector<vector<int>> square;

    if (n % 2 == 1) {
        square = generateOdd(n);
    } 
    else if (n % 4 == 0) {
        square = generateDoublyEven(n);
    } 
    else {
        cout << "Singly-even order (n=2 mod 4) not implemented in this code.\n";
        return 0;
    }

    printSquare(square);

    return 0;
}
