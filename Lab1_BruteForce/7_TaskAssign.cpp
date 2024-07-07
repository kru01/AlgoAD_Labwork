/* CSC14111 - 21KHMT - Lab 1: Brute-force algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q7. The assignment problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>

const std::string inPath = "inputs/";

std::pair<std::vector<int>, int> getValAssign
(int** perJobMap, int numJobs) {
    std::pair<std::vector<int>, int> valAssign({}, std::numeric_limits<int>::max());
            // assigment, minValue
    std::vector<int> assigns(numJobs);
    for (int i = 0; i < numJobs; i++) assigns[i] = i;

    do {
        int currVal = 0;
        for (int i = 0; i < numJobs; i++) currVal += perJobMap[i][assigns[i]];
        if (currVal < valAssign.second)
            valAssign = std::make_pair(assigns, currVal);
    } while(std::next_permutation(assigns.begin(), assigns.end()));
    return valAssign;
}

int main() {
    std::ifstream inFile(inPath + "7.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int numJobs = std::stoi(line);

    int** perJobMap = new int*[numJobs];
    for (int i = 0; i < numJobs; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        perJobMap[i] = new int[numJobs];
        for (int j = 0; j < numJobs; j++) sline >> perJobMap[i][j];
    }
    inFile.close();

    auto valAssign = getValAssign(perJobMap, numJobs);
    for (auto& assign : valAssign.first) std::cout << assign + 1 << " ";
    std::cout << "\n" << valAssign.second << std::endl;

    for (int i = 0; i < numJobs; i++) delete[] perJobMap[i];
    delete[] perJobMap;
    return 0;
}