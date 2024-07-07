/* CSC14111 - 21KHMT - Lab 2: Backtracking algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q4. The sum of subsets problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

const std::string inPath = "inputs/";

void printVect(std::vector<int> vect) {
    for (auto i : vect) std::cout << i << " ";
    std::cout << "\n";
}

// Normal
void printValSbsets
(int* arr, int arrSz, int target, std::vector<int> subset, int start, int sum) {
    if (sum == target) {
        printVect(subset);
        return;
    }

    for (int i = start; i < arrSz; i++) {
        subset.push_back(arr[i]);
        printValSbsets(arr, arrSz, target, subset, start + 1, sum + arr[i]);
        subset.pop_back();
    }
}

// Upgraded
void printValSbsetsUpg
(int* arr, int arrSz, int target, std::vector<int> subset,
int start, int sum, int total) {
    if (sum == target) {
        printVect(subset);
        return;
    }

    int lost = 0;
    for (int i = start; i < arrSz; i++) {
        if ((sum + total - lost >= target) && (sum + arr[i] <= target)) {
            subset.push_back(arr[i]);
            printValSbsetsUpg(arr, arrSz, target, subset, start + 1,
                sum + arr[i], total - lost - arr[i]);
            subset.pop_back();
        }
        lost += arr[i];
    }
}

int main() {
    std::ifstream inFile(inPath + "4.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int arrSz = std::stoi(line);

    int* arr = new int[arrSz], total = 0;
    std::getline(inFile, line);
    std::stringstream sline(line);
    for (int i = 0; i < arrSz; i++) {
        sline >> arr[i]; total += arr[i];
    }

    std::getline(inFile, line);
    int target = std::stoi(line);
    inFile.close();

    std::sort(arr, arr + arrSz);
    if (target < arr[0] || target > total) {
        std::cout << "No solution" << std::endl;
        delete[] arr; return 0;
    }

    std::vector<int> subset;
    std::cout << "---> Normal\n";
    printValSbsets(arr, arrSz, target, subset, 0, 0);

    subset.clear();
    std::cout << "---> Upgraded\n";
    printValSbsetsUpg(arr, arrSz, target, subset, 0, 0, total);

    std::cout << std::flush;
    delete[] arr;
    return 0;
}