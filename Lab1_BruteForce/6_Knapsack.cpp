/* CSC14111 - 21KHMT - Lab 1: Brute-force algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q6. The Knapsack problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

const std::string inPath = "inputs/";

std::pair<std::vector<int>, int> getValItems
(int** items, int numIts, int cap) {
    std::pair<std::vector<int>, int> valItems({}, -1); // items, maxValue

    std::vector<std::vector<int>> subsets = {{}};
    for (int i = 0; i < numIts; i++) {
        std::vector<std::vector<int>> genSubsets = subsets;
        for (int j = 0; j < genSubsets.size(); j++)
            genSubsets[j].push_back(i);
        for (int j = 0; j < genSubsets.size(); j++)
            subsets.push_back(genSubsets[j]);
    }
    subsets.erase(subsets.begin());

    for (auto& sset : subsets) {
        int currWt = 0, currVal = 0;
        for (auto& it : sset) {
            currWt += items[it][0]; currVal += items[it][1];
        }
        if (currWt <= cap && currVal > valItems.second)
            valItems = std::make_pair(sset, currVal);
    }
    return valItems;
}

int main() {
    std::ifstream inFile(inPath + "6.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int cap = std::stoi(line);

    std::getline(inFile, line);
    int numIts = std::stoi(line);

    int** items = new int*[numIts];
    for (int i = 0; i < numIts; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        items[i] = new int[2];
        sline >> items[i][0] >> items[i][1]; // weight, value
    }
    inFile.close();

    auto valItems = getValItems(items, numIts, cap);
    if (valItems.first.empty()) std::cout << "No solution" << std::endl;
    else {
        for (auto& it : valItems.first) std::cout << it + 1 << " ";
        std::cout << "\n" << valItems.second << std::endl;
    }

    for (int i = 0; i < numIts; i++) delete[] items[i];
    delete[] items;
    return 0;
}