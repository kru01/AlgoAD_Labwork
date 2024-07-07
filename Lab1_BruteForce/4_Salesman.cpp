/* CSC14111 - 21KHMT - Lab 1: Brute-force algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q4. The traveling salesman problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>

const std::string inPath = "inputs/";

std::pair<std::vector<int>, int> getMinRoute
(int** ctMap, int numCt) {
    std::pair<std::vector<int>, int> outs({}, std::numeric_limits<int>::max());
            // minRoute, minDist
    std::vector<int> route(numCt);
    for (int i = 0; i < numCt; i++) route[i] = i;

    int start = 0;
    do {
        bool noRoad = false;
        int from = start, currDist = 0;
        for (int i = 0; i < numCt; i++) {
            if (ctMap[from][route[i]] < 0) {
                noRoad = true; break;
            }
            currDist += ctMap[from][route[i]];
            from = route[i];
        }
        if (noRoad) continue;
        currDist += ctMap[from][start];
        if (outs.second > currDist) outs = std::make_pair(route, currDist);
    } while (std::next_permutation(route.begin(), route.end()));
    return outs;
}

int main() {
    std::ifstream inFile(inPath + "4.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int numCt = std::stoi(line);

    int** ctMap = new int*[numCt];
    for (int i = 0; i < numCt; i++) {
        ctMap[i] = new int[numCt]();
        for (int j = 0; j < numCt; j++)
            if (i != j) ctMap[i][j] = -1;
    }

    while (std::getline(inFile, line)) {
        std::stringstream sline(line);
        int ct1; sline >> ct1;
        if (ct1 == -1) break;

        int ct2, dist;
        sline >> ct2 >> dist;
        ctMap[ct1 - 1][ct2 - 1] = ctMap[ct2 - 1][ct1 - 1] = dist;
    }
    inFile.close();

    auto minRouteInfo = getMinRoute(ctMap, numCt);
    if (minRouteInfo.first.empty()) std::cout << "No solution" << std::endl;
    else {
        for (auto& ct : minRouteInfo.first) std::cout << ct + 1 << " ";
        std::cout << "\n" << minRouteInfo.second << std::endl;
    }

    for (int i = 0; i < numCt; i++) delete[] ctMap[i];
    delete[] ctMap;
    return 0;
}