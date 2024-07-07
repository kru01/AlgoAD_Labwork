/* CSC14111 - 21KHMT - Lab 2: Backtracking algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q5. The Hamiltonian circuit problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const std::string inPath = "inputs/";

bool canReach(int** adjMat, int verNum, int* path, int ver, int pos) {
    if (pos == verNum && adjMat[ver][path[0]] == 0
        || adjMat[path[pos - 1]][ver] == 0) return false;

    for (int i = 0; i < pos; i++) if (path[i] == ver) return false;
    return true;
}

bool getHamiltonPath(int** adjMat, int verNum, int* path, int pos) {
    if (pos == verNum) return true;
    for (int i = 0; i < verNum; i++) {
        if (canReach(adjMat, verNum, path, i, pos)) {
            path[pos] = i;
            if (getHamiltonPath(adjMat, verNum, path, pos + 1)) return true;
            path[pos] = -1;
        }
    }
    return false;
}

int main() {
    std::ifstream inFile(inPath + "5.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int verNum = std::stoi(line);

    int** adjMat = new int*[verNum], *path = new int[verNum];
    for (int i = 0; i < verNum; i++) {
        adjMat[i] = new int[verNum]; path[i] = -1;
        std::getline(inFile, line);
        std::stringstream sline(line);
        for (int j = 0; j < verNum; j++) sline >> adjMat[i][j];
    }

    std::getline(inFile, line);
    path[0] = std::stoi(line);
    inFile.close();

    if (!getHamiltonPath(adjMat, verNum, path, 1))
        std::cout << "No solution\n";
    else {
        for (int i = 0; i < verNum; i++) std::cout << path[i] << " ";
        std::cout << "\n";
    }

    std::cout << std::flush;
    for (int i = 0; i < verNum; i++) delete[] adjMat[i];
    delete[] adjMat; delete[] path;
    return 0;
}