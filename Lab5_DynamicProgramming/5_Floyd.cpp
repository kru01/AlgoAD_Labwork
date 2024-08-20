/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q5. The Floyd’s algorithm for the all-pairs shortest-paths problem.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

const std::string inPath = "inputs/";
const int INF =  std::numeric_limits<int>::max();

void doFloyd(int verNum, std::vector<std::vector<int>>& dists,
std::vector<std::vector<int>>& preds) {
    for (int inter = 0; inter < verNum; inter++)
        for (int src = 0; src < verNum; src++)
            for (int dest = 0; dest < verNum; dest++) {
                if (dists[src][inter] == INF || dists[inter][dest] == INF)
                    continue;

                int interDist = dists[src][inter] + dists[inter][dest];

                if (dists[src][dest] > interDist) {
                    dists[src][dest] = interDist;
                    preds[src][dest] = inter;
                }
            }
}

void printPath(std::vector<std::vector<int>>& preds, int src, int dest) {
    if (preds[src][dest] == -1) std::cout << dest + 1;
    else {
        printPath(preds, src, preds[src][dest]);
        std::cout << " - " << dest + 1;
    }
}

int main() {
    std::ifstream inFile(inPath + "5.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int verNum; inFile >> verNum;

    std::vector<std::vector<int>> dists
        (verNum, std::vector<int>(verNum, INF));

    for (int i = 0; i < verNum; i++) dists[i][i] = 0;

    std::vector<std::vector<int>> preds
        (verNum, std::vector<int>(verNum, -1));

    for (int i = 0, edgeCnt; i < verNum; i++) {
        inFile >> edgeCnt;

        for (int j = 0, ver, wt; j < edgeCnt; j++) {
            inFile >> ver >> wt;

            dists[i][ver - 1] = wt;
            preds[i][ver - 1] = i;
        }
    }
    inFile.close();

    doFloyd(verNum, dists, preds);

    for (int i = 0; i < verNum; i++)
        for (int j = 0; j < verNum; j++)
            if (i != j && dists[i][j] != INF) {
                printPath(preds, i, j);
                std::cout << ": " << dists[i][j] << "\n";
            }

    std::cout << std::flush;
    return 0;
}