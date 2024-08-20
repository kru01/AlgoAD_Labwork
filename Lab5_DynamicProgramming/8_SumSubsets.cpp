/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q8. The sum of subsets problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

const std::string inPath = "inputs/";

void printValidSubsets(int arrSz, int* arr, int target,
std::vector<std::vector<bool>>& dp, std::vector<int>& subset) {
    if (target == 0) {
        for (int i = subset.size() - 1; i >= 0; i--)
            std::cout << subset[i] << " ";
        std::cout << "\n";
        return;
    }

    if (arrSz == 0) return;

    int size = arrSz - 1, remain = target - arr[size];

    if (dp[size][target])
        printValidSubsets(size, arr, target, dp, subset);

    if (arr[size] <= target && dp[size][remain]) {
        subset.push_back(arr[size]);
        printValidSubsets(size, arr, remain, dp, subset);
        subset.pop_back();
    }
}

bool findValidSubsets(int arrSz, int* arr, int target) {
    std::vector<std::vector<bool>>
        dp(arrSz + 1, std::vector<bool>(target + 1, false));

    for (int i = 0; i < arrSz; i++) dp[i][0] = true;

    for (int i = 1; i <= arrSz; i++)
        for (int j = 1; j <= target; j++)
            if (j < arr[i - 1]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];

    if (!dp[arrSz][target]) return false;

    std::vector<int> subset;
    printValidSubsets(arrSz, arr, target, dp, subset);
    return true;
}

int main() {
    std::ifstream inFile(inPath + "8.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int arrSz = std::stoi(line);

    std::getline(inFile, line);
    std::stringstream sline(line);

    int* arr = new int[arrSz];
    for (int i = 0; i < arrSz; i++) sline >> arr[i];

    std::getline(inFile, line);
    int target = std::stoi(line);
    inFile.close();

    if (!findValidSubsets(arrSz, arr, target))
        std::cout << "No solution" << "\n";

    std::cout << std::flush;
    delete[] arr;
    return 0;
}