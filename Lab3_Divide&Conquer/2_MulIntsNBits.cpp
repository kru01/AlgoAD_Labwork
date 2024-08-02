/* CSC14111 - 21KHMT - Lab 3: Divide and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q2. The multiplication of two positive integers of n bits.
 */
#include <iostream>
#include <limits>
#include <cmath>

std::string decToBin(long long num) {
    std::string bin = "";
    for (; num; num >>= 1) bin += (num & 1) ? '1' : '0';
    return std::string(bin.rbegin(), bin.rend());
}

std::string addBits(std::string b1, std::string b2) {
    return decToBin(std::stoll(b1, nullptr, 2) + std::stoll(b2, nullptr, 2));
}

long long mulPosIntsNBits(std::string b1, std::string b2, int alpha=1) {
    int b1Len = b1.length(), b2Len = b2.length();
    if (b1Len == 0 || b2Len == 0) return 0;

    int maxBtCnt = std::max(b1Len, b2Len);
    if (maxBtCnt <= alpha)
        return std::stoll(b1, nullptr, 2) * std::stoll(b2, nullptr, 2);

    if (b1Len < b2Len) b1 = std::string(b2Len - b1Len, '0').append(b1);
    else if (b1Len > b2Len) b2 = std::string(b1Len - b2Len, '0').append(b2);

    int flHalfCnt = maxBtCnt / 2, ceHalfCnt = maxBtCnt - flHalfCnt;

    std::string xL = b1.substr(0, ceHalfCnt),
        xR = b1.substr(ceHalfCnt, flHalfCnt),
        yL = b2.substr(0, ceHalfCnt), yR = b2.substr(ceHalfCnt, flHalfCnt);

    long long r = mulPosIntsNBits(addBits(xL, xR), addBits(yL, yR)),
        p = mulPosIntsNBits(xL, yL),
        q = mulPosIntsNBits(xR, yR);

    return p * std::pow(2, 2*flHalfCnt)
        + (r - p - q) * std::pow(2, flHalfCnt) + q;
}

int main() {
    std::cout << "Enter 2 integers: ";
    long long n1, n2;

    while (!(std::cin >> n1) || n1 < 0) {
        std::cout << "Invalid! Reinput: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (!(std::cin >> n2) || n2 < 0) {
        std::cout << "Invalid! Reinput: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string b1 = decToBin(n1), b2 = decToBin(n2);
    std::cout << mulPosIntsNBits(b1, b2) << std::endl;
    return 0;
}