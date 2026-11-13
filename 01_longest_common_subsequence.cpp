/*
 * ============================================================================
 * PROBLEM: Longest Common Subsequence (Standard LCS)
 * PLATFORM: LeetCode 1143 / HackerRank (The Longest Common Subsequence)
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two strings `text1` and `text2`, return the length of their longest
 * common subsequence. If there is no common subsequence, return 0.
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative
 * order of the remaining characters.
 *
 * ALGORITHM (Bottom-Up 2D Dynamic Programming):
 * Let dp[i][j] be the length of the LCS of text1[0..i-1] and text2[0..j-1].
 * - Base Case: dp[0][j] = 0 and dp[i][0] = 0 (empty string has LCS 0).
 * - Transition:
 *   If text1[i-1] == text2[j-1]:
 *       dp[i][j] = 1 + dp[i-1][j-1]
 *   Else:
 *       dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * - Result: dp[n][m], where n = text1.length(), m = text2.length().
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M) (Can be optimized to O(min(N, M)) using 1D array)
 *
 * INPUT FORMAT:
 * Two space-separated or newline-separated strings s1 and s2.
 *
 * OUTPUT FORMAT:
 * A single integer representing the length of the longest common subsequence.
 *
 * EXAMPLE:
 * Input:
 * abcde ace
 * Output:
 * 3
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int longestCommonSubsequence(const string& text1, const string& text2) {
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

int main() {
    string s1, s2;
    if (cin >> s1 >> s2) {
        cout << longestCommonSubsequence(s1, s2) << "\n";
    }
    return 0;
}
