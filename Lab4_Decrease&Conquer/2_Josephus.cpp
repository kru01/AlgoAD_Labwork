/* CSC14111 - 21KHMT - Lab 4: Decrease and conquer algorithms
 * 21127135 - Diep Huu Phuc
 *
 * Q2. Josephus problem.
 */
#include <iostream>
#include <limits>

// https://zhu45.org/posts/2016/Dec/31/josephus-problem/
int solveJosephus(int ppNum) {
    int larPow = 1;
    while (larPow < ppNum) larPow *= 2;
    return 2 * ppNum - larPow + 1;
}

int main() {
    std::cout << "Enter an int > 2: ";
    int ppNum;

    while (!(std::cin >> ppNum) || ppNum <= 2) {
        std::cout << "Invalid! Reinput: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << solveJosephus(ppNum) << std::endl;
    return 0;
}