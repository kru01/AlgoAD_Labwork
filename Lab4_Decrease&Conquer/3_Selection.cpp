/* CSC14111 - 21KHMT - Lab 4: Decrease and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q3. Selection problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

const std::string inPath = "inputs/";

int partition(int* arr, int lower, int upper, int pos) {
    if (lower == upper) return lower;

    int pivot = arr[pos];
    std::swap(arr[lower], arr[pos]);
    pos = lower;

    for (int i = lower + 1; i <= upper; i++)
        if (pivot > arr[i]) std::swap(arr[i], arr[++pos]);

    std::swap(arr[lower], arr[pos]);
    return pos;
}

int getKthSmallest(int* arr, int arrSz, int kth, int lower, int upper) {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distInt(lower, upper);

    int pvPos = partition(arr, lower, upper, distInt(generator));
    if (pvPos == kth) return arr[pvPos];

    if (pvPos > kth) return getKthSmallest(arr, arrSz, kth, lower, pvPos - 1);
    return getKthSmallest(arr, arrSz, kth, pvPos + 1, upper);
}


int main() {
    std::ifstream inFile(inPath + "3.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int arrSz = std::stoi(line);

    int* arr = new int[arrSz];
    std::getline(inFile, line);
    std::stringstream sline(line);
    for (int i = 0; i < arrSz; i++) sline >> arr[i];

    std::getline(inFile, line);
    int kth = std::stoi(line);
    inFile.close();

    std::cout << getKthSmallest(arr, arrSz, kth - 1, 0, arrSz - 1);

    std::cout << std::endl;
    delete[] arr;
    return 0;
}