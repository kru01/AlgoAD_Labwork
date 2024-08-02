/* CSC14111 - 21KHMT - Lab 3: Divide and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q5. The closest-pair problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

const std::string inPath = "inputs/";

struct Point {
    int x, y;
    float getDistTo(Point p) {
        return sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
    }
};

float getClosestPairBF(Point* points, int ptNum,
        std::pair<Point, Point>& clPair) {
    float minDist = std::numeric_limits<float>::max();
    for (int i = 0; i < ptNum; i++)
        for (int j = i + 1; j < ptNum; j++) {
            float dist = points[i].getDistTo(points[j]);
            if (dist < minDist) {
                clPair = {points[i], points[j]}; minDist = dist;
            }
        }
    return minDist;
}

float getClosestPairDnC(Point* points, int ptNum,
        std::pair<Point, Point>& clPair) {
    if (ptNum <= 3) return getClosestPairBF(points, ptNum, clPair);

    int mid = ptNum / 2; std::pair<Point, Point> tmpPair;
    float minL = getClosestPairDnC(points, mid, clPair),
        minR = getClosestPairDnC(points + mid, ptNum - mid, tmpPair),
        minDist = std::min(minL, minR);
    
    if (minDist == minR) clPair = tmpPair;

    std::vector<Point> strip;
    for (int i = 0; i < ptNum; i++)
        if (abs(points[i].x - points[mid].x) < minDist)
            strip.push_back(points[i]);

    std::sort(strip.begin(), strip.end(), [](const Point& p1, const Point& p2) {
        return p1.y < p2.y;
    });

    for (int i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size()
                && abs(strip[i].y - strip[j].y) < minDist; j++) {
            float dist = strip[i].getDistTo(strip[j]);
            if (dist < minDist) {
                clPair = {strip[i], strip[j]}; minDist = dist;
            }
        }

    return minDist;
}

int main() {
    std::ifstream inFile(inPath + "5.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int ptNum = std::stoi(line);

    Point* points = new Point[ptNum];
    for (int i = 0; i < ptNum; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        sline >> points[i].x >> points[i].y;
    }
    inFile.close();

    std::sort(points, points + ptNum, [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    });

    std::pair<Point, Point> clPair;
    float minDist = getClosestPairDnC(points, ptNum, clPair);

    std::cout << clPair.first.x << " " << clPair.first.y << "\n";
    std::cout << clPair.second.x << " " << clPair.second.y << "\n";
    std::cout << minDist << std::endl;

    delete[] points;
    return 0;
}