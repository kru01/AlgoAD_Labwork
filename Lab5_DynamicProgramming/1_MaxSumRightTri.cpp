/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q1. The problem of maximum sum of a path in a right number triangle.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

const std::string inPath = "inputs/";

int getMaxSumPath
(int height, std::vector<std::vector<int>>& triag, std::vector<int>& path) {
    std::vector<std::vector<int>> dp = triag;

    for (int i = height - 2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            dp[i][j] += std::max(dp[i + 1][j], dp[i + 1][j + 1]);

    path.push_back(triag[0][0]);

    for (int row = 0, col = 0; row < height - 1;) {
        if (dp[row + 1][col] >= dp[row + 1][col + 1]) row++;
        else {
            row++; col++;
        }

        path.push_back(triag[row][col]);
    }

    return dp[0][0];
}

int main() {
    std::ifstream inFile(inPath + "1.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int height = std::stoi(line);

    std::vector<std::vector<int>> triag(height);
    for (int i = 0; i < height; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        for (int j; sline >> j;) triag[i].push_back(j);
    }
    inFile.close();

    std::vector<int> path;
    int maxSum = getMaxSumPath(height, triag, path);

    for (auto& i : path) std::cout << i << " ";
    std::cout << "\n" << maxSum << std::endl;

    return 0;
}