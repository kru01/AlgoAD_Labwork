/* CSC14111 - 21KHMT - Lab 2: Backtracking algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q2. The knight tour problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

const std::string inPath = "inputs/";

std::pair<int,int> operator+(const std::pair<int, int>& x, const std::pair<int, int>& y) {
    return std::make_pair(x.first + y.first, x.second + y.second);
}

bool getValidTour
(int** board, int bdSize, int mvCnt, std::pair<int, int> currPos) {
    const static std::pair<int, int> moves[8] = {{2, 1}, {1, 2}, {-1, 2},
        {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    
    if (mvCnt == bdSize * bdSize + 1) return true;

    for (int i = 0; i < 8; i++) {
        auto nxPos = currPos + moves[i];

        if (0 <= nxPos.first && nxPos.first < bdSize
            && 0 <= nxPos.second && nxPos.second < bdSize
            && board[nxPos.first][nxPos.second] == 0) {
            board[nxPos.first][nxPos.second] = mvCnt;
            if (getValidTour(board, bdSize, mvCnt + 1, nxPos)) return true;
            board[nxPos.first][nxPos.second] = 0;
        }
    }
    return false;
}

int main() {
    std::ifstream inFile(inPath + "2.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int bdSize = std::stoi(line);

    int stRow, stCol, **board = new int*[bdSize];
    for (int i = 0; i < bdSize; i++) board[i] = new int[bdSize]();

    std::getline(inFile, line);
    inFile.close();
    std::stringstream sline(line);
    sline >> stRow >> stCol;
    board[stRow][stCol] = 1;

    if (!getValidTour(board, bdSize, 2, {stRow, stCol}))
        std::cout << "No solution\n";
    else {
        for (int i = 0; i < bdSize; i++) {
            for (int j = 0; j < bdSize; j++)
                std::cout << std::setw(2) << board[i][j] << " ";
            std::cout << "\n";
        }
    }

    std::cout << std::flush;
    for (int i = 0; i < bdSize; i++) delete[] board[i];
    delete[] board;
    return 0;
}