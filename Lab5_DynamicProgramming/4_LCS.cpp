/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q4. The longest common subsequence (LCS) problem.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::string getLCS(std::string& strS, std::string& strT) {
    int lenS = strS.length(), lenT = strT.length();
    std::vector<std::vector<int>> dp(lenS + 1, std::vector<int>(lenT + 1, 0));

    for (int i = 1; i <= lenS; i++)
        for (int j = 1; j <= lenT; j++)
            if (strS[i - 1] == strT[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

    std::string lcs = "";
    for (int i = lenS, j = lenT; i > 0 && j > 0;) {
        if (strS[i - 1] == strT[j - 1]) {
            lcs = strS[i - 1] + lcs;
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) i--;
        else j--;
    }

    return lcs;
}

int main() {
    std::string strS, strT;
    std::cin >> strS >> strT;

    std::cout << getLCS(strS, strT) << std::endl;
    return 0;
}