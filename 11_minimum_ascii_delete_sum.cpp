/*
 * ============================================================================
 * PROBLEM: Minimum ASCII Delete Sum for Two Strings (Weighted LCS)
 * PLATFORM: LeetCode 712
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two strings `s1` and `s2`, return the lowest ASCII sum of deleted
 * characters to make two strings equal.
 *
 * ALGORITHM (Weighted LCS Maximization):
 * - Instead of maximizing the *count* of common characters (standard LCS),
 *   we maximize the *ASCII sum* of the common subsequence!
 * - Let dp[i][j] be the maximum ASCII sum of a common subsequence of
 *   s1[0..i-1] and s2[0..j-1].
 * - Transition:
 *   If s1[i-1] == s2[j-1]:
 *       dp[i][j] = int(s1[i-1]) + dp[i-1][j-1]
 *   Else:
 *       dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * - Result:
 *   Total ASCII sum of both strings minus 2 * dp[n][m].
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * Two strings `s1` and `s2` separated by whitespace.
 *
 * OUTPUT FORMAT:
 * A single integer representing the minimum ASCII delete sum.
 *
 * EXAMPLE:
 * Input:
 * sea eat
 * Output:
 * 231
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int minimumDeleteSum(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = static_cast<int>(s1[i - 1]) + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int totalAscii = 0;
    for (char c : s1) totalAscii += static_cast<int>(c);
    for (char c : s2) totalAscii += static_cast<int>(c);

    return totalAscii - 2 * dp[n][m];
}

int main() {
    string s1, s2;
    if (cin >> s1 >> s2) {
        cout << minimumDeleteSum(s1, s2) << "\n";
    }
    return 0;
}
