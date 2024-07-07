/* CSC14111 - 21KHMT - Lab 1: Brute-force algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q3. The convex-hull problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <math.h>

const std::string inPath = "inputs/";

// Normal brute-force with O(n^3)
std::set<int*> getConHullPtsNorm(int** points, int numPts) {
    std::set<int*> conHullPts = {};
    for (int i = 0; i < numPts - 1; i++)
        for (int j = i + 1; j < numPts; j++) {
            int a = points[j][1] - points[i][1];
            int b = points[i][0] - points[j][0];
            int c = points[i][0] * points[j][1]
                - points[j][0] * points[i][1];

            bool allSameSide = true;
            int prevSide = 0;
            for (int k = 0; k < numPts; k++) {
                if (k == i || k == j) continue;

                int currVal = a * points[k][0] + b * points[k][1];
                int currSide = currVal > c ? 1 : (currVal < c ? -1 : 0);
                if (prevSide == 0) prevSide = currSide;

                if ((prevSide == 1 && currSide == -1)
                    || (prevSide == -1 && currSide == 1)) {
                    allSameSide = false; break;
                }
            }

            if (!allSameSide) continue;
            conHullPts.insert(points[i]);
            conHullPts.insert(points[j]);
        }
    return conHullPts;
}

// Counterclockwise brute-force with O(n^2)
float calcAngle(int* fromPt, int* toPt) {
    float angle = atan2(toPt[1] - fromPt[1], toPt[0] - fromPt[0]);
    if (angle < 0) angle += 2 * M_PI;
    return angle;
}

std::pair<int*, float>findNextPtAndAngle
(int** points, int numPts, int* currPt, float currAngle) {
    std::pair<int*, float> outs; // nextPoint, minAngle
    outs.second = 2 * M_PI;

    for (int i = 0; i < numPts; i++) {
        if (points[i] == currPt) continue;

        float angle = calcAngle(currPt, points[i]);
        if (angle < outs.second && angle >= currAngle)
            outs = std::make_pair(points[i], angle);
    }
    return outs;
}

std::vector<int*> getConHullPtsCntClock(int** points, int numPts) {
    std::vector<int*> conHullPts = {};
    
    conHullPts.push_back(points[0]);
    for (int i = 1; i < numPts; i++)
        if (conHullPts[0][1] < points[i][1]) continue;
        else if (conHullPts[0][1] > points[i][1] || conHullPts[0][0] > points[i][0])
            conHullPts[0] = points[i];

    int* currPt = conHullPts[0]; float currAngle = 0;
    while (true) {
        auto ptInfo = findNextPtAndAngle(points, numPts, currPt, currAngle);
        int* nextPt = ptInfo.first; currAngle = ptInfo.second;

        if (conHullPts[0] == nextPt) break;
        conHullPts.push_back(nextPt);
        currPt = nextPt;
    }
    return conHullPts;
}

int main() {
    std::ifstream inFile(inPath + "3.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int numPts = std::stoi(line);

    int** points = new int*[numPts];
    for (int i = 0; i < numPts; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        points[i] = new int[2];
        sline >> points[i][0] >> points[i][1];
    }
    inFile.close();

    std::cout << "---> Normal brute-force with O(n^3)\n";
    auto conHullPtsNorm = getConHullPtsNorm(points, numPts);
    for (auto& pt : conHullPtsNorm) std::cout << pt[0] << " " << pt[1] << "\n";

    std::cout << "---> Counterclockwise brute-force with O(n^2)\n";
    auto conHullPtsCntClock = getConHullPtsCntClock(points, numPts);
    for (auto& pt : conHullPtsCntClock) std::cout << pt[0] << " " << pt[1] << "\n";

    std::cout << std::flush;
    for (int i = 0; i < numPts; i++) delete[] points[i];
    delete[] points;
    return 0;
}