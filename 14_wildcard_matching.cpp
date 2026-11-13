/*
 * ============================================================================
 * PROBLEM: Wildcard Matching (Pattern-Based LCS / String Alignment)
 * PLATFORM: LeetCode 44
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given an input string `s` and a pattern `p`, implement wildcard pattern
 * matching with support for '?' and '*' where:
 *   - '?' matches any single character.
 *   - '*' matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 *
 * ALGORITHM (2D Boolean Alignment DP):
 * - Let dp[i][j] be true if s[0..i-1] matches p[0..j-1].
 * - Base Cases:
 *   dp[0][0] = true
 *   dp[0][j] = dp[0][j-1] if p[j-1] == '*' (star matches empty prefix)
 * - Transition:
 *   If p[j-1] == '?' || p[j-1] == s[i-1]:
 *       dp[i][j] = dp[i-1][j-1]
 *   Else if p[j-1] == '*':
 *       // '*' matches 0 characters (dp[i][j-1]) OR 1+ characters (dp[i-1][j])
 *       dp[i][j] = dp[i][j-1] || dp[i-1][j]
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * Two strings `s` and `p` separated by whitespace.
 * (Note: use "-" if testing empty string `s` in standard console input)
 *
 * OUTPUT FORMAT:
 * "true" if pattern `p` matches `s`, otherwise "false".
 *
 * EXAMPLE:
 * Input:
 * adceb *a*b
 * Output:
 * true
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isMatch(const string& s, const string& p) {
    int n = s.size();
    int m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;
    for (int j = 1; j <= m; ++j) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        }
    }
    return dp[n][m];
}

int main() {
    string s, p;
    if (cin >> s >> p) {
        if (s == "-") s = "";
        cout << (isMatch(s, p) ? "true" : "false") << "\n";
    }
    return 0;
}
