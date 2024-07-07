/* CSC14111 - 21KHMT - Lab 1: Brute-force algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q5. The sum of subsets problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <numeric>

const std::string inPath = "inputs/";

std::set<std::vector<int>, std::greater<std::vector<int>>>
getValidSubsets(int* arr, int arrSize, int target) {
    std::set<std::vector<int>, std::greater<std::vector<int>>> valSubsets;
    std::vector<std::vector<int>> subsets = {{}};

    for (int i = 0; i < arrSize; i++) {
        std::vector<std::vector<int>> genSubsets = subsets;
        for (int j = 0; j < genSubsets.size(); j++)
            genSubsets[j].push_back(arr[i]);
        for (int j = 0; j < genSubsets.size(); j++) {
            subsets.push_back(genSubsets[j]);
            if (std::accumulate(genSubsets[j].begin(), genSubsets[j].end(), 0)
                == target) valSubsets.insert(genSubsets[j]);
        }
    }
    return valSubsets;
}

int main() {
    std::ifstream inFile(inPath + "5.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int arrSize = std::stoi(line);

    int* arr = new int[arrSize];
    std::getline(inFile, line);
    std::stringstream sline(line);
    for (int i = 0; i < arrSize; i++) sline >> arr[i];

    std::getline(inFile, line);
    int target = std::stoi(line);
    inFile.close();

    auto valSubsets = getValidSubsets(arr, arrSize, target);
    if (valSubsets.empty()) std::cout << "No solution\n";
    else {
        for (auto& subset : valSubsets) {
            for (auto& ele : subset) std::cout << ele << " ";
            std::cout << "\n";
        }
    }

    std::cout << std::flush;
    delete[] arr;
    return 0;
}