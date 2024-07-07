/* CSC14111 - 21KHMT - Lab 1: Brute-force algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q1. Find the contiguous subarray of largest sum. 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const std::string inPath = "inputs/";

// Brute-force version with O(n^3)
int* getSubArrMaxSumBruteF(int* arr, int arrSize) {
    int* outs = new int[3](); // 0 - maxSum, 1 - i, 2 - j
    outs[1] = outs[2] = -1;
    for (int i = 0; i < arrSize; i++)
        for (int j = i; j < arrSize; j++) {
            int currSum = 0;
            for (int k = i; k <= j; k++)
                currSum += arr[k];
            if (currSum > outs[0]) {
                outs[0] = currSum;
                outs[1] = i; outs[2] = j;
            }
        }
    return outs;
}

// Upgraded version with O(n^2)
int* getSubArrMaxSumUpgraded(int* arr, int arrSize) {
    int* outs = new int[3](); // 0 - maxSum, 1 - i, 2 - j
    outs[1] = outs[2] = -1;
    for (int i = 0; i < arrSize; i++) {
        int currSum = 0;
        for (int j = i; j < arrSize; j++) {
            currSum += arr[j];
            if (currSum > outs[0]) {
                outs[0] = currSum;
                outs[1] = i; outs[2] = j;
            }
        }
    }
    return outs;
}

// Dynamic programming version with O(n)
int* getSubArrMaxSumDP(int* arr, int arrSize) {
    int* outs = new int[3](); // 0 - maxSum, 1 - i, 2 - j
    outs[1] = outs[2] = -1;
    int currSum = 0, start = 0;
    for (int i = 0; i < arrSize; i++) {
        currSum += arr[i];

        if (currSum > outs[0]) {
            outs[0] = currSum;
            outs[1] = start;
            outs[2] = i;
            continue;
        }
        if (currSum < 0) {
            currSum = 0;
            start = i + 1;
        }
    }
    return outs;
}

void printResults(int* arr, int* results) {
    if (results[1] != -1)
        for (int i = results[1]; i <= results[2]; i++)
            std::cout << arr[i] << " ";
    std::cout << "\n" << results[0] << std::endl;
    delete[] results;
}

int main() {
    std::ifstream inFile(inPath + "1.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int arrSize = std::stoi(line);

    std::getline(inFile, line);
    inFile.close();

    int* arr = new int[arrSize];
    std::stringstream sline(line);
    for (int i = 0; i < arrSize; i++)
        sline >> arr[i];

    std::cout << "---> Brute-force version with O(n^3)\n";
    printResults(arr, getSubArrMaxSumBruteF(arr, arrSize));

    std::cout << "---> Upgraded version with O(n^2)\n";
    printResults(arr, getSubArrMaxSumUpgraded(arr, arrSize));

    std::cout << "---> Dynamic programming version with O(n)\n";
    printResults(arr, getSubArrMaxSumDP(arr, arrSize));

    delete[] arr;
    return 0;
}