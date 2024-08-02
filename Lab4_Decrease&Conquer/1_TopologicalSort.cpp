/* CSC14111 - 21KHMT - Lab 4: Decrease and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q1. Topological sorting.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

const std::string inPath = "inputs/";

std::vector<int> doTopologicalSort(std::vector<std::vector<int>>& graph) {
    std::vector<int> indegrees(graph.size(), 0);
    std::queue<int> delQu;

    for (auto& vert : graph)
        for (auto& adj : vert) indegrees[adj]++;

    for (int i = 0; i < graph.size(); i++)
        if (indegrees[i] == 0) delQu.push(i);

    std::vector<int> sorted;
    while (!delQu.empty()) {
        int vert = delQu.front(); delQu.pop();
        sorted.push_back(vert + 1);

        for (auto& adj : graph[vert])
            if (--indegrees[adj] == 0) delQu.push(adj);
    }

    return sorted;
}

int main() {
    std::ifstream inFile(inPath + "1.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int verNum = std::stoi(line);

    std::vector<std::vector<int>> graph(verNum);
    for (int i = 0; i < verNum; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);

        int destCnt; sline >> destCnt;
        graph[i] = std::vector<int>(destCnt);
        for (int j = 0; j < destCnt; j++) {
            sline >> graph[i][j]; graph[i][j]--;
        }
    }
    inFile.close();

    auto sorted = doTopologicalSort(graph);
    for (auto& vert : sorted) std::cout << vert << " ";
    std::cout << std::endl;
    return 0;
}