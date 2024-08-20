/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q6. The matrix chain multiplication problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

const std::string inPath = "inputs/";

void makeMatChainOrder
(std::vector<std::vector<int>>& splits, int i, int j, std::string& order) {
    if (i == j) {
        order += "A" + std::to_string(i);
        return;
    }
    order += "(";
    makeMatChainOrder(splits, i, splits[i][j], order);
    makeMatChainOrder(splits, splits[i][j] + 1, j, order);
    order += ")";
}

int getMatChainOrder(int matNum, int* dims, std::string& order) {
    std::vector<int> inner(matNum, 0);
    std::vector<std::vector<int>> minOps(matNum, inner), splits(matNum, inner);

    for (int len = 2; len < matNum; len++)
        for (int i = 1; i < matNum - len + 1; i++) {
            int end = i + len - 1;
            minOps[i][end] = std::numeric_limits<int>::max();

            for (int div = i; div <= end - 1; div++) {
                int cost = minOps[i][div] + minOps[div + 1][end]
                    + dims[i - 1] * dims[div] * dims[end];

                if (cost < minOps[i][end]) {
                    minOps[i][end] = cost;
                    splits[i][end] = div;
                }
            }
        }
    
    makeMatChainOrder(splits, 1, matNum - 1, order);
    return minOps[1][matNum - 1];
}

int main() {
    std::ifstream inFile(inPath + "6.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int matNum = std::stoi(line);

    int* dims = new int[matNum + 1];
    for (int i = 0; i < matNum; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        int d2;
        sline >> dims[i] >> d2;
        if (i == matNum - 1) dims[matNum] = d2;
    }
    inFile.close();

    std::string order = "";
    int minOps = getMatChainOrder(matNum + 1, dims, order);

    std::cout << order.substr(1, order.length() - 2)
        << "\n" << minOps << std::endl;

    delete[] dims;
    return 0;
}