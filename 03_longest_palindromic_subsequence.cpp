/*
 * ============================================================================
 * PROBLEM: Longest Palindromic Subsequence (LPS)
 * PLATFORM: LeetCode 516
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given a string `s`, find the longest palindromic subsequence's length in `s`.
 * A subsequence is a sequence that can be derived from another sequence by
 * deleting some or no elements without changing the order of the remaining
 * elements.
 *
 * ALGORITHM (Reduction to LCS):
 * A palindrome reads the same forward and backward. Therefore, the Longest
 * Palindromic Subsequence of string `s` is identical to the Longest Common
 * Subsequence of `s` and `reverse(s)`.
 * - Let rev_s = reverse(s).
 * - Return LCS(s, rev_s).
 *
 * TIME COMPLEXITY: O(N^2), where N is the length of string `s`.
 * SPACE COMPLEXITY: O(N^2) (Can be reduced to O(N) using 1D DP).
 *
 * INPUT FORMAT:
 * A single string `s`.
 *
 * OUTPUT FORMAT:
 * A single integer representing the length of the longest palindromic
 * subsequence.
 *
 * EXAMPLE:
 * Input:
 * bbbab
 * Output:
 * 4
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int longestPalindromeSubseq(const string& s) {
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());

    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i - 1] == rev_s[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][n];
}

int main() {
    string s;
    if (cin >> s) {
        cout << longestPalindromeSubseq(s) << "\n";
    }
    return 0;
}
