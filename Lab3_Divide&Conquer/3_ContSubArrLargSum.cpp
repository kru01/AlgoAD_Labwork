/* CSC14111 - 21KHMT - Lab 3: Divide and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q3. Find the contiguous subarray of largest sum.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const std::string inPath = "inputs/";

int getContSubArrLargSum(int* arr, int left, int right, int& sarrSt) {
    if (left == right) return std::max(arr[left], 0);

    int mid = (left + right) / 2;
    int maxLS = getContSubArrLargSum(arr, left, mid, sarrSt);
    int maxRS = getContSubArrLargSum(arr, mid + 1, right, sarrSt);

    int currSum = 0, maxL = 0;
    for (int i = mid; i >= left; i--) {
        currSum += arr[i];
        if (currSum > maxL) {
            maxL = currSum; sarrSt = i;
        }
    }

    currSum = 0; int maxR = 0;
    for (int i = mid + 1; i <= right; i++) {
        currSum += arr[i];
        if (currSum > maxR) maxR = currSum;
    }

    int maxSum = std::max(maxL + maxR, std::max(maxL, maxR));
    if (maxSum == maxL) sarrSt = left;
    else if (maxSum == maxR) sarrSt = mid + 1;

    return maxSum;
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
    inFile.close();

    int sarrSt = 0;
    int maxSum = getContSubArrLargSum(arr, 0, arrSz - 1, sarrSt);

    for (int i = sarrSt,  currSum = 0
        ; currSum != maxSum && i < arrSz; currSum += arr[i++]) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n" << maxSum << std::endl;

    delete[] arr;
    return 0;
}