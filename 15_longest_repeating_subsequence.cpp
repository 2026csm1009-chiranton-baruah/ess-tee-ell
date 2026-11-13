/*
 * ============================================================================
 * PROBLEM: Longest Repeating Subsequence (Self-LCS with Index Constraint)
 * PLATFORM: Classic Interview / HackerRank & GFG Practice Variant
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given a string `s`, find the length of the longest subsequence that appears
 * at least twice in `s`, such that the two subsequences do not use the same
 * character at the same index position.
 *
 * ALGORITHM (Self-LCS with i != j):
 * - Run LCS of string `s` against itself (`s` and `s`), adding one constraint:
 *   a character at index `i-1` can only match a character at index `j-1` if
 *   `i != j`.
 * - Transition:
 *   If s[i-1] == s[j-1] && i != j:
 *       dp[i][j] = 1 + dp[i-1][j-1]
 *   Else:
 *       dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *
 * TIME COMPLEXITY: O(N^2)
 * SPACE COMPLEXITY: O(N^2)
 *
 * INPUT FORMAT:
 * A single string `s`.
 *
 * OUTPUT FORMAT:
 * A single integer representing the length of the longest repeating subsequence.
 *
 * EXAMPLE:
 * Input:
 * aabebcdd
 * Output:
 * 3
 * (Explanation: The subsequence "abd" appears twice at disjoint indices)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int longestRepeatingSubsequence(const string& s) {
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i - 1] == s[j - 1] && i != j) {
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
        cout << longestRepeatingSubsequence(s) << "\n";
    }
    return 0;
}
