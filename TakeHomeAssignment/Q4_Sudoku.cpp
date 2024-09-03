#include <iostream>

const int N = 9;

/* BRUTE-FORCE EXHAUSTIVE SEARCH
 */
bool isValidSudoku(int grid[N][N]) {
    for (int row = 0; row < N; row++) { // Check all rows and columns
        bool rowFlags[N] = {0}, colFlags[N] = {0};

        for (int col = 0; col < N; col++) {
            int numR = grid[row][col] - 1, numC = grid[col][row] - 1;

            if (numR != 0) { // Check rows
                if (rowFlags[numR]) return false;
                rowFlags[numR] = true;
            }

            if (numC != 0) { // Check columns
                if (colFlags[numC]) return false;
                colFlags[numC] = true;
            }
        }
    }

    // Check all 3x3 sub-grids
    for (int stRow = 0; stRow < N; stRow += 3)
        for (int stCol = 0; stCol < N; stCol += 3) {
            bool boxFlags[N + 1] = {0};

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) {
                    int num = grid[stRow + i][stCol + j];
                    if (num == 0) continue;

                    if (boxFlags[num]) return false;
                    boxFlags[num] = true;
                }
        }

    return true;
}

bool solveSudokuBF(int grid[N][N], int idx) {
    // After a whole grid is generated, check if it's valid
    if (idx == N * N) return isValidSudoku(grid);

    int row = idx / N, col = idx % N;

    // If this cell is not empty, move to the next one
    if (grid[row][col] != 0) return solveSudokuBF(grid, idx + 1);

    for (int num = 1; num <= 9; num++) {
        grid[row][col] = num;
        if (solveSudokuBF(grid, idx + 1)) return true;
    }

    // If no number leads to a valid grid
    grid[row][col] = 0;
    return false;
}

/* BACKTRACKING
 */
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) // Check rows and columns
        if (grid[row][i] == num || grid[i][col] == num) return false;

    // Check 3x3 sub-grids
    int stRow = row - row % 3, stCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[stRow + i][stCol + j] == num) return false;

    return true;
}

bool solveSudokuBTrack(int grid[N][N]) {
    // Optional: Check if the input is even valid
    if (!isValidSudoku(grid)) return false;

    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++) {
            if (grid[row][col] != 0) continue;

            for (int num = 1; num <= 9; num++) {
                if (!isSafe(grid, row, col, num)) continue;

                grid[row][col] = num;
                if (solveSudokuBTrack(grid)) return true;
                grid[row][col] = 0;
            }

            return false;
        }

    return true;
}

/* DRIVER CODES
 */
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            std::cout << grid[i][j] << ((j + 1) % 3 != 0 ? " " : " | ");

        if ((i + 1) % 3 == 0) std::cout << "\n" << std::string(N * 2 + 3, '-');
        std::cout << "\n";
    }
}

int main() {
    int grid[N][N] = {
        { 3, 1, 6, 5, 7, 8, 4, 9, 2 },
        { 5, 2, 9, 1, 3, 4, 7, 6, 8 },
        { 4, 8, 7, 6, 2, 9, 5, 3, 1 },
        { 2, 6, 3, 0, 1, 5, 9, 8, 7 },
        { 9, 7, 4, 8, 6, 0, 1, 2, 5 },
        { 8, 5, 1, 7, 9, 2, 6, 4, 3 },
        { 1, 3, 8, 0, 4, 7, 2, 0, 6 },
        { 6, 9, 2, 3, 5, 1, 8, 7, 4 },
        { 7, 4, 5, 0, 8, 6, 3, 1, 0 }
    };

    std::cout << "--> Sudoku Exhaustive search\n";
    if (solveSudokuBF(grid, 0)) printGrid(grid);
    else std::cout << "No solution";

    std::cout << "\n--> Sudoku Backtracking\n";
    if (solveSudokuBTrack(grid)) printGrid(grid);
    else std::cout << "No solution";

    std::cout << std::endl;
    return 0;
}