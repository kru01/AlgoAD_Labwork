/* CSC14111 - 21KHMT - Lab 3: Divide and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q6. The change-making problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

const std::string inPath = "inputs/";

int getCoinChangesUpg(int* denoms, int deNum, int target,
        std::vector<int>& changes) {
    int minCoins = target;

    for (int i = 0; i < deNum; i++) {
        if (denoms[i] == target) { changes[i]++; return 1; }

        std::vector<int> currChanges(deNum, 0);
        if (denoms[i] < target) {
            int coinCnt = 1 + getCoinChangesUpg(denoms, deNum,
                    target - denoms[i], currChanges);
            currChanges[i]++;

            if (coinCnt <= minCoins) {
                minCoins = coinCnt; changes = currChanges;
            }
        }
    }

    return minCoins;
}

int main() {
    std::ifstream inFile(inPath + "6.txt");
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
    
    std::vector<int> changes(deNum, 0);
    int minCoins = getCoinChangesUpg(denoms, deNum, target, changes);

    if (minCoins == 0) std::cout << "No solution\n";
    else {
        for (int i = 0; i < deNum; i++)
            std::cout << denoms[i] << ": " << changes[i] << "\n";
    }

    std::cout << std::flush;
    delete[] denoms;
    return 0;
}