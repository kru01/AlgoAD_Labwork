/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q3. The longest monotonically increasing subsequence (LMIS) problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

const std::string inPath = "inputs/";

int getLMIS(int arrSz, int* arr, std::vector<int>& seq) {
    std::vector<int> dp(arrSz, 1), preds(arrSz, -1);

    for (int i = 1; i < arrSz; i++)
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                preds[i] = j;
            }

    int maxLen = 0, maxIdx = 0;
    for (int i = 0; i < arrSz; i++)
        if (dp[i] > maxLen) {
            maxLen = dp[i]; maxIdx = i;
        }

    for (int curr = maxIdx; curr != -1;) {
        seq.push_back(arr[curr]);
        curr = preds[curr];
    }

    std::reverse(seq.begin(), seq.end());
    return maxLen;
}

int main() {
    std::ifstream inFile(inPath + "3.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int arrSz = std::stoi(line);

    int* arr = new int[arrSz];
    std::getline(inFile, line);
    std::stringstream sline(line);
    for (int i = 0; i < arrSz; i++) sline >> arr[i];

    std::vector<int> seq;
    getLMIS(arrSz, arr, seq);

    for (auto& i : seq) std::cout << i << " ";

    delete[] arr;
    return 0;
}