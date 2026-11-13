/*
 * ============================================================================
 * PROBLEM: Distinct Subsequences (Counting LCS Occurrences)
 * PLATFORM: LeetCode 115
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two strings `s` and `t`, return the number of distinct subsequences
 * of `s` which equals `t`.
 *
 * ALGORITHM (Counting DP):
 * Let dp[i][j] be the number of distinct subsequences of s[0..i-1] that equal
 * t[0..j-1].
 * - Base Cases:
 *   dp[i][0] = 1 for all i >= 0 (empty string t can be formed in 1 way: delete all)
 *   dp[0][j] = 0 for all j > 0  (non-empty t cannot be formed from empty s)
 * - Transition:
 *   If s[i-1] == t[j-1]:
 *       // Either match s[i-1] with t[j-1] OR skip s[i-1]
 *       dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
 *   Else:
 *       // Must skip s[i-1]
 *       dp[i][j] = dp[i-1][j]
 * Note: Use `unsigned long long` (or modulo arithmetic) to avoid intermediate
 * overflow on large test cases.
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * Two strings `s` and `t` separated by whitespace.
 *
 * OUTPUT FORMAT:
 * A single integer representing the number of distinct subsequences.
 *
 * EXAMPLE:
 * Input:
 * rabbbit rabbit
 * Output:
 * 3
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

unsigned long long numDistinct(const string& s, const string& t) {
    int n = s.size();
    int m = t.size();
    vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));

    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][m];
}

int main() {
    string s, t;
    if (cin >> s >> t) {
        cout << numDistinct(s, t) << "\n";
    }
    return 0;
}
