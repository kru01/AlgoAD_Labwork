/* CSC14111 - 21KHMT - Lab 1: Brute-force algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q2. The change-making problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

const std::string inPath = "inputs/";

std::vector<int*> getAllChanges(int* arr, int arrSize, int target) {
    if (target == 0) return {new int[arrSize]()};
    if (target < 0) return {};

    std::vector<int*> allChanges = {};
    for (int i = 0; i < arrSize; i++) {
        auto changes = getAllChanges(arr, arrSize, target - arr[i]);
        for (auto& ch : changes) ch[i]++;
        allChanges.reserve(allChanges.size() + changes.size());
        allChanges.insert(allChanges.end(), changes.begin(), changes.end());
    }
    return allChanges;
}

int* getMinChange(std::vector<int*> allChanges, int arrSize) {
    std::sort(allChanges.begin(), allChanges.end(), [arrSize](int* ch1, int* ch2) {
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < arrSize; i++) {
            sum1 += ch1[i]; sum2 += ch2[i];
        }
        return sum1 < sum2;
    });
    return allChanges.front();   
}

int main() {
    std::ifstream inFile(inPath + "2.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int arrSize = std::stoi(line);

    std::getline(inFile, line);
    int* arr = new int[arrSize];
    std::stringstream sline(line);
    for (int i = 0; i < arrSize; i++) sline >> arr[i];

    std::getline(inFile, line);
    int target = std::stoi(line);
    inFile.close();

    auto allChanges = getAllChanges(arr, arrSize, target);
    if (allChanges.empty()) std::cout << "No solution\n";
    else {
        int* minChange = getMinChange(allChanges, arrSize);
        for (int i = 0; i < arrSize; i++)
            std::cout << arr[i] << ": " << minChange[i] << "\n";
    }

    std::cout << std::flush;
    for (auto& ch: allChanges) delete[] ch;
    delete[] arr;
    return 0;
}