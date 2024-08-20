/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q9. The Knapsack problem.
 */
#include <iostream>
#include <fstream>
#include <vector>

const std::string inPath = "inputs/";

int fillKnapsack
(int cap, int itNum, int* wts, int* vals, std::vector<int>& items) {
    std::vector<std::vector<int>>
        dp(itNum + 1, std::vector<int>(cap + 1, 0));

    for (int i = 1; i <= itNum; i++)
        for (int w = 1; w <= cap; w++) {
            int curr = i - 1;

            if (wts[curr] > w) dp[i][w] = dp[i - 1][w];
            else dp[i][w] =
                std::max(dp[i - 1][w], dp[i - 1][w - wts[curr]] + vals[curr]);
        }

    int maxVal = dp[itNum][cap], w = cap;

    for (int i = itNum; i > 0 && maxVal > 0; i--)
        if (maxVal != dp[i - 1][w]) {
            items.push_back(i);
            maxVal -= vals[i - 1];
            w -= wts[i - 1];
        }

    return dp[itNum][cap];
}

int main() {
    std::ifstream inFile(inPath + "9.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int cap, itNum;
    inFile >> cap >> itNum;

    int* wts = new int[itNum], *vals = new int[itNum];
    for (int i = 0; i < itNum; i++) inFile >> wts[i] >> vals[i];
    inFile.close();

    std::vector<int> items;
    int maxVal = fillKnapsack(cap, itNum, wts, vals, items);

    if (items.empty()) {
        std::cout << "No solution" << std::endl;
        return 0;
    }

    for (int i = items.size() - 1; i >= 0; i--) std::cout << items[i] << " ";
    std::cout << "\n" << maxVal << std::endl;

    delete[] wts; delete[] vals;
    return 0;
}