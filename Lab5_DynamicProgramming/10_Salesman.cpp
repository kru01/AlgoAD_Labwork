/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q10. The traveling salesman problem.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

const std::string inPath = "inputs/";

const int INF = std::numeric_limits<int>::max();

int travel(int ctNum, int** dists, int c1, int start, int mask,
std::vector<std::vector<int>>& path) {
    static const int maxSubset = (1 << ctNum) - 1;

    static std::vector<std::vector<int>>
        dp(ctNum, std::vector<int>(1 << ctNum, -1));

    if (mask == maxSubset) return dists[c1][start];
    if (dp[c1][mask] != -1) return dp[c1][mask];

    int minLen = INF;
    for (int c2 = 0; c2 < ctNum; c2++)
        if ((mask & (1 << c2)) == 0 && dists[c1][c2] != INF) {
            int len = travel(ctNum, dists, c2, start, mask | (1 << c2), path)
                    + dists[c1][c2];

            if (len < minLen) {
                minLen = len;
                path[c1][mask] = c2;
            }
        }

    dp[c1][mask] = minLen;
    return minLen;
}

std::string makeTour(std::vector<std::vector<int>>& path, int c1) {
    std::string tour = "";
    int mask = (1 << c1);

    while (true) {
        tour += std::to_string(c1 + 1) + " ";

        int nextCt = path[c1][mask];
        if (nextCt == -1) break;

        mask |= 1 << nextCt;
        c1 = nextCt;
    }

    return tour;
}

int getShortestTour(int ctNum, int** dists, std::string& tour) {
    std::vector<std::vector<int>>
        path(ctNum, std::vector<int>(1 << ctNum, -1));

    int bestSt = 0, minLen = INF;

    for (int i = 0; i < ctNum; i++) {
        int len = travel(ctNum, dists, i, i, 1 << i, path);
        if (len < minLen) {
            bestSt = i; minLen = len;
        }
    }

    if (minLen != INF) tour = makeTour(path, bestSt);
    return minLen;
}

int main() {
    std::ifstream inFile(inPath + "10.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int ctNum; inFile >> ctNum;

    int** dists = new int*[ctNum];
    for (int i = 0; i < ctNum; i++) {
        dists[i] = new int[ctNum];
        for (int j = 0; j < ctNum; j++) dists[i][j] = INF;
    }

    for (int c1, c2, d; inFile >> c1 >> c2 >> d;) {
        if (c1 == -1) break;
        c1--; c2--;
        dists[c1][c2] = dists[c2][c1] = d;
    }
    inFile.close();

    std::string tour;
    int minLen = getShortestTour(ctNum, dists, tour);

    if (minLen != INF) {
        std::cout << tour << "\n" << minLen << std::endl;
    } else std::cout << "No solution" << std::endl;

    for (int i = 0; i < ctNum; i++) delete[] dists[i];
    delete[] dists;
    return 0;
}