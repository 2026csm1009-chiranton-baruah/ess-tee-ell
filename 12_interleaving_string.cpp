/*
 * ============================================================================
 * PROBLEM: Interleaving String (2-String Prefix Merge LCS Variant)
 * PLATFORM: LeetCode 97
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given strings `s1`, `s2`, and `s3`, find whether `s3` is formed by an
 * interleaving of `s1` and `s2`. An interleaving preserves the left-to-right
 * relative order of characters from both `s1` and `s2`.
 *
 * ALGORITHM (Boolean 2D Prefix Matching DP):
 * - First check: if s1.size() + s2.size() != s3.size(), return false.
 * - Let dp[i][j] be true if s3[0..i+j-1] can be formed by interleaving
 *   s1[0..i-1] and s2[0..j-1].
 * - Base Case: dp[0][0] = true.
 * - Transition:
 *   dp[i][j] = (i > 0 && dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
 *              (j > 0 && dp[i][j-1] && s2[j-1] == s3[i+j-1])
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * Three strings s1, s2, and s3 separated by whitespace.
 *
 * OUTPUT FORMAT:
 * "true" if s3 is a valid interleaving of s1 and s2, otherwise "false".
 *
 * EXAMPLE:
 * Input:
 * aabcc dbbca aadbbcbcac
 * Output:
 * true
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isInterleave(const string& s1, const string& s2, const string& s3) {
    int n = s1.size();
    int m = s2.size();
    if (n + m != static_cast<int>(s3.size())) return false;

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i > 0 && s1[i - 1] == s3[i + j - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j];
            }
            if (j > 0 && s2[j - 1] == s3[i + j - 1]) {
                dp[i][j] = dp[i][j] || dp[i][j - 1];
            }
        }
    }
    return dp[n][m];
}

int main() {
    string s1, s2, s3;
    if (cin >> s1 >> s2 >> s3) {
        cout << (isInterleave(s1, s2, s3) ? "true" : "false") << "\n";
    }
    return 0;
}
