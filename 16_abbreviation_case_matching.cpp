/*
 * ============================================================================
 * PROBLEM: Abbreviation (Conditional Case-Sensitive LCS Alignment)
 * PLATFORM: HackerRank (Abbreviation)
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * You can perform two operations on string `a`:
 *   1. Capitalize zero or more of `a`'s lowercase letters.
 *   2. Delete all of the remaining lowercase letters in `a`.
 * Given strings `a` (mixed case) and `b` (all uppercase), determine if it is
 * possible to make `a` equal to `b`.
 *
 * ALGORITHM (2D Boolean Alignment DP):
 * - Let dp[i][j] be true if prefix a[0..i-1] can be transformed into b[0..j-1].
 * - Base Cases:
 *   dp[0][0] = true
 *   dp[i][0] = dp[i-1][0] && islower(a[i-1]) (can only delete lowercase letters)
 * - Transition:
 *   1. If a[i-1] is uppercase:
 *      It CANNOT be deleted. It must match b[j-1]:
 *      dp[i][j] = (j > 0 && a[i-1] == b[j-1]) ? dp[i-1][j-1] : false;
 *   2. If a[i-1] is lowercase:
 *      We can either DELETE it (dp[i-1][j]) OR CAPITALIZE it if
 *      toupper(a[i-1]) == b[j-1] (dp[i-1][j-1]):
 *      dp[i][j] = dp[i-1][j] || (j > 0 && toupper(a[i-1]) == b[j-1] && dp[i-1][j-1]);
 *
 * TIME COMPLEXITY: O(N * M) per query
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * First line: Integer Q (number of queries).
 * For each query:
 *   Line 1: String `a`
 *   Line 2: String `b`
 *
 * OUTPUT FORMAT:
 * For each query, print "YES" or "NO" on a new line.
 *
 * EXAMPLE:
 * Input:
 * 1
 * daBcd
 * ABC
 * Output:
 * YES
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

string abbreviation(const string& a, const string& b) {
    int n = a.size();
    int m = b.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        if (islower(static_cast<unsigned char>(a[i - 1]))) {
            dp[i][0] = dp[i - 1][0];
        } else {
            dp[i][0] = false;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char ca = a[i - 1];
            char cb = b[j - 1];
            if (isupper(static_cast<unsigned char>(ca))) {
                dp[i][j] = (ca == cb) && dp[i - 1][j - 1];
            } else {
                bool deleteChar = dp[i - 1][j];
                bool capitalizeChar = (toupper(static_cast<unsigned char>(ca)) == cb) && dp[i - 1][j - 1];
                dp[i][j] = deleteChar || capitalizeChar;
            }
        }
    }
    return dp[n][m] ? "YES" : "NO";
}

int main() {
    int q;
    if (!(cin >> q)) return 0;
    while (q--) {
        string a, b;
        cin >> a >> b;
        cout << abbreviation(a, b) << "\n";
    }
    return 0;
}
