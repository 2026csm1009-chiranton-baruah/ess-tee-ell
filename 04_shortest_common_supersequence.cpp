/*
 * ============================================================================
 * PROBLEM: Shortest Common Supersequence (SCS)
 * PLATFORM: LeetCode 1092
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two strings `str1` and `str2`, return the shortest string that has both
 * `str1` and `str2` as subsequences. If there are multiple valid strings,
 * return any of them.
 *
 * ALGORITHM (LCS DP Table + Supersequence Reconstruction):
 * - Notice that the length of the SCS is: len(str1) + len(str2) - len(LCS).
 * - We first compute the standard LCS DP table `dp[n+1][m+1]`.
 * - Then, we backtrack from (i = n, j = m):
 *   1. If str1[i-1] == str2[j-1]:
 *      Include str1[i-1] once in the SCS and decrement both i and j.
 *   2. Else if dp[i-1][j] > dp[i][j-1]:
 *      str1[i-1] is not in the LCS, so we must include str1[i-1] and move up (i--).
 *   3. Else:
 *      str2[j-1] is not in the LCS, so we must include str2[j-1] and move left (j--).
 * - Append any remaining characters from str1 (while i > 0) or str2 (while j > 0).
 * - Reverse the resulting string.
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * Two strings str1 and str2 separated by whitespace.
 *
 * OUTPUT FORMAT:
 * A single string representing the Shortest Common Supersequence.
 *
 * EXAMPLE:
 * Input:
 * abac cab
 * Output:
 * cabac
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string shortestCommonSupersequence(const string& str1, const string& str2) {
    int n = str1.size();
    int m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string scs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            scs.push_back(str1[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            scs.push_back(str1[i - 1]);
            --i;
        } else {
            scs.push_back(str2[j - 1]);
            --j;
        }
    }

    while (i > 0) {
        scs.push_back(str1[i - 1]);
        --i;
    }
    while (j > 0) {
        scs.push_back(str2[j - 1]);
        --j;
    }

    reverse(scs.begin(), scs.end());
    return scs;
}

int main() {
    string s1, s2;
    if (cin >> s1 >> s2) {
        cout << shortestCommonSupersequence(s1, s2) << "\n";
    }
    return 0;
}
