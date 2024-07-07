/* CSC14111 - 21KHMT - Lab 2: Backtracking algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q1. The n-queens problem.
 */
#include <iostream>
#include <limits>
#include <cmath>

void printBoard(int* rows, int quNum) {
    for (int i = 0; i < quNum; i++) {
        for (int j = 0; j < quNum; j++)
            if (rows[i] != j) std::cout << "- ";
            else std::cout << "Q ";
        std::cout << "\n";
    }
}

bool canPlace(int* rows, int currRow) {
    for (int row = 0; row < currRow; row++) {
        if (rows[row] == rows[currRow]
            || abs(rows[currRow] - rows[row]) == currRow - row)
            return false;
    }
    return true;
}

bool placeNQueens(int* rows, int quNum, int currRow) {
    for (int col = 0; col < quNum; col++) {
        rows[currRow] = col;
        if (canPlace(rows, currRow)) {
            if (currRow == quNum - 1) return true;
            if (placeNQueens(rows, quNum, currRow + 1)) return true;
        }
    }
    return false;
}

int main() {
    std::cout << "Input the number of queens (int > 0): ";
    int quNum;
    while (!(std::cin >> quNum) || quNum <= 0) {
        std::cout << "Input must be int > 0! Reinput: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int* rows = new int[quNum];
    if (!placeNQueens(rows, quNum, 0)) std::cout << "No solution\n";
    else printBoard(rows, quNum);

    std::cout << std::flush;
    delete[] rows;
    return 0;
}