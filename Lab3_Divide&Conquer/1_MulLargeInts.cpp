/* CSC14111 - 21KHMT - Lab 3: Divide and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q1. The multiplication of large integers problem.
 */
#include <iostream>
#include <limits>
#include <cmath>

int countDigits(long long num) {
    return std::floor(std::log10(abs(num)) + 1);
}

long long mulLarIntsUpg(long long n1, long long n2, int alpha=1) {
    const int maxDgCnt = std::max(countDigits(n1), countDigits(n2));

    if (n1 == 0 || n2 == 0) return 0;
    if (maxDgCnt <= alpha) return n1 * n2;

    int m = maxDgCnt / 2;
    long x = n1 / std::pow(10, m), y = n1 % (long)std::pow(10, m);
    long w = n2 / std::pow(10, m), z = n2 % (long)std::pow(10, m);

    long r = mulLarIntsUpg(x + y, w + z);
    long p = mulLarIntsUpg(x, w), q = mulLarIntsUpg(y, z);

    return p * std::pow(10, 2*m) + (r - p - q) * std::pow(10, m) + q;
}

int main() {
    std::cout << "Enter 2 integers: ";
    long long n1, n2;

    while (!(std::cin >> n1)) {
        std::cout << "Invalid! Reinput: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (!(std::cin >> n2)) {
        std::cout << "Invalid! Reinput: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << mulLarIntsUpg(n1, n2) << std::endl;
    return 0;
}