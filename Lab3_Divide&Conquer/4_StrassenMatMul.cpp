/* CSC14111 - 21KHMT - Lab 3: Divide and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q4. The Strassen's matrix multiplication problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

const std::string inPath = "inputs/";

std::vector<std::vector<int>> operator+
        (const std::vector<std::vector<int>>& matA,
        const std::vector<std::vector<int>>& matB) {
    std::vector<std::vector<int>> matC(matA.size(),
        std::vector<int>(matA.size(), 0));

    for (int i = 0; i < matA.size(); i++)
        for (int j = 0; j < matA.size(); j++)
            matC[i][j] = matA[i][j] + matB[i][j];
    return matC;    
}

std::vector<std::vector<int>> operator-
        (const std::vector<std::vector<int>>& matA,
        const std::vector<std::vector<int>>& matB) {
    std::vector<std::vector<int>> matC(matA.size(),
        std::vector<int>(matA.size(), 0));

    for (int i = 0; i < matA.size(); i++)
        for (int j = 0; j < matA.size(); j++)
            matC[i][j] = matA[i][j] - matB[i][j];
    return matC;    
}

void doStrassenMatMul(int matSz, std::vector<std::vector<int>>& matA,
        std::vector<std::vector<int>>& matB,
        std::vector<std::vector<int>>& matC) {
    if (matSz == 1) { matC[0][0] = matA[0][0] * matB[0][0]; return; }

    int halfSz = matSz / 2; std::vector<int> initVect(halfSz, 0);
    std::vector<std::vector<int>> matA11(halfSz, initVect), matA12(halfSz, initVect),
        matA21(halfSz, initVect), matA22(halfSz, initVect), matB11(halfSz, initVect),
        matB12(halfSz, initVect), matB21(halfSz, initVect), matB22(halfSz, initVect);

    for (int i = 0; i < halfSz; i++)
        for (int j = 0; j < halfSz; j++) {
            matA11[i][j] = matA[i][j];
            matA12[i][j] = matA[i][j + halfSz];
            matA21[i][j] = matA[i + halfSz][j];
            matA22[i][j] = matA[i + halfSz][j + halfSz];

            matB11[i][j] = matB[i][j];
            matB12[i][j] = matB[i][j + halfSz];
            matB21[i][j] = matB[i + halfSz][j];
            matB22[i][j] = matB[i + halfSz][j + halfSz];
        }
    
    std::vector<std::vector<int>> matAD11 = matA11 + matA22,
        matAD12 = matB11 + matB22, matAD2 = matA21 + matA22,
        matSU3 = matB12 - matB22, matSU4 = matB21 - matB11,
        matAD5 = matA11 + matA12, matSU6 = matA21 - matA11,
        matAD6 = matB11 + matB12, matSU7 = matA12 - matA22,
        matAD7 = matB21 + matB22;

    std::vector<std::vector<int>> matM1(halfSz, initVect), matM2(halfSz, initVect),
        matM3(halfSz, initVect), matM4(halfSz, initVect), matM5(halfSz, initVect),
        matM6(halfSz, initVect), matM7(halfSz, initVect);

    doStrassenMatMul(halfSz, matAD11, matAD12, matM1);
    doStrassenMatMul(halfSz, matAD2, matB11, matM2);
    doStrassenMatMul(halfSz, matA11, matSU3, matM3);
    doStrassenMatMul(halfSz, matA22, matSU4, matM4);
    doStrassenMatMul(halfSz, matAD5, matB22, matM5);
    doStrassenMatMul(halfSz, matSU6, matAD6, matM6);
    doStrassenMatMul(halfSz, matSU7, matAD7, matM7);

    std::vector<std::vector<int>> matC11 = matM1 + matM4 - matM5 + matM7,
        matC12 = matM3 + matM5, matC21 = matM2 + matM4,
        matC22 = matM1 + matM3 - matM2 + matM6;

    for (int i = 0; i < halfSz; i++)
        for (int j = 0; j < halfSz; j++) {
            matC[i][j] = matC11[i][j];
            matC[i][j + halfSz] = matC12[i][j];
            matC[i + halfSz][j] = matC21[i][j];
            matC[i + halfSz][j + halfSz] = matC22[i][j];
        }
}

int main() {
    std::ifstream inFile(inPath + "4.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(inFile, line);
    int matSz = std::stoi(line); std::vector<int> initVect(matSz, 0);

    std::vector<std::vector<int>> matA(matSz, initVect), matB(matSz, initVect);
    for (int i = 0; i < matSz; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        for (int j = 0; j < matSz; j++) sline >> matA[i][j];
    }
    for (int i = 0; i < matSz; i++) {
        std::getline(inFile, line);
        std::stringstream sline(line);
        for (int j = 0; j < matSz; j++) sline >> matB[i][j];
    }
    inFile.close();

    std::vector<std::vector<int>> matC(matSz, initVect);
    doStrassenMatMul(matSz, matA, matB, matC);

    for (int i = 0; i < matSz; i++) {
        for (int j = 0; j < matSz; j++)
            std::cout << matC[i][j] << " ";
        std::cout << "\n";
    }

    std::cout << std::flush;
    return 0;
}