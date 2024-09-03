#include <iostream>
#include <limits>

int findMedian(int x[], int y[], int xl, int xr, int yl, int yr) {
    static const int INF_MIN = std::numeric_limits<int>::min(),
        INF_MAX = std::numeric_limits<int>::max();

    int m = xr + 1, n = yr + 1;
    // Target the smaller array for binary search.
    if (m > n) return findMedian(y, x, yl, yr, xl, xr);

    for (int left = 0, right = m; left <= right;) {
        int i = (left + right) / 2,
            j = (m + n + 1) / 2 - i;

        // Edge cases: If there is nothing on the left, or the right side.
        int maxXl = (i == 0) ? INF_MIN : x[xl + i - 1],
            minXr = (i == m) ? INF_MAX : x[xl + i];

        int maxYl = (j == 0) ? INF_MIN : y[yl + j - 1],
            minYr = (j == n) ? INF_MAX : y[yl + j];

        // If all left elements aren't greater than the right ones, then
        // if the merged size is odd, the median is the max of left side,
        // otherwise it's the avg of max left and min right.
        if (maxXl <= minYr && maxYl <= minXr)
            if ((m + n) % 2 != 0) return std::max(maxXl, maxYl);
            else return (std::max(maxXl, maxYl) + std::min(minXr, minYr)) / 2;
        else if (maxXl > minYr) right = i - 1; // <- Move left.
        else left = i + 1; // -> Move right.
    }

    return INF_MIN; // There might be problem if reachable.
}

int main() {
    int x[] = {1, 3, 8, 9, 15},
        y[] = {7, 11, 18, 19, 21, 25};

    int m = sizeof(x) / sizeof(x[0]),
        n = sizeof(y) / sizeof(y[0]);

    int median = findMedian(x, y, 0, m - 1, 0, n - 1);

    if (median != std::numeric_limits<int>::min()) std::cout << median;
    else std::cout << "Error";

    std::cout << std::endl;
    return 0;
}