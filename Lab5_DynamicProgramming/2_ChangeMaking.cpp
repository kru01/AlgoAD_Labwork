/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q2. The change-making problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

const std::string inPath = "inputs/";

int getChanges(int deNum, int* denoms, int target, int* changes) {
    std::vector<int> dp(target + 1, target + 1),
        coinCnt(target + 1, -1);

    dp[0] = 0;
    for (int i = 1; i <= target; i++)
        for (int j = 0; j < deNum; j++)
            if (denoms[j] <= i && dp[i - denoms[j]] != target + 1)
                if (dp[i] > dp[i - denoms[j]] + 1) {
                    dp[i] = dp[i - denoms[j]] + 1;
                    coinCnt[i] = j;
                }

    if (dp[target] > target) return -1;

    for (int left = target; left > 0;) {
        int pos = coinCnt[left];
        if (pos == -1) return -1;
        changes[pos]++;
        left -= denoms[pos];
    }

    return dp[target];
}

int main() {
    std::ifstream inFile(inPath + "2.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int deNum = std::stoi(line);

    int* denoms = new int[deNum];
    std::getline(inFile, line);
    std::stringstream sline(line);
    for (int i = 0; i < deNum; i++) sline >> denoms[i];

    std::getline(inFile, line);
    int target = std::stoi(line);
    inFile.close();

    int* changes = new int[deNum]();

    if (getChanges(deNum, denoms, target, changes) == - 1) {
        std::cout << "No solution" << std::endl;
        return 0;
    }

    for (int i = 0; i < deNum; i++)
        std::cout << denoms[i] << ": " << changes[i] << "\n";

    std::cout << std::flush;
    delete[] denoms; delete[] changes;
    return 0;
}