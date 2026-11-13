/*
 * ============================================================================
 * PROBLEM: Edit Distance (Levenshtein Distance)
 * PLATFORM: LeetCode 72
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two strings `word1` and `word2`, return the minimum number of operations
 * required to convert `word1` to `word2`.
 * You have the following three operations permitted on a word:
 *   1. Insert a character
 *   2. Delete a character
 *   3. Replace a character
 *
 * ALGORITHM (2D Dynamic Programming - LCS Variant):
 * Let dp[i][j] be the minimum edit distance between word1[0..i-1] and
 * word2[0..j-1].
 * - Base Cases:
 *   dp[i][0] = i (delete all i characters from word1)
 *   dp[0][j] = j (insert all j characters of word2)
 * - Transition:
 *   If word1[i-1] == word2[j-1]:
 *       dp[i][j] = dp[i-1][j-1]  (no operation needed)
 *   Else:
 *       dp[i][j] = 1 + min({
 *           dp[i-1][j],    // Delete from word1
 *           dp[i][j-1],    // Insert into word1
 *           dp[i-1][j-1]   // Replace character
 *       })
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * Two strings word1 and word2 separated by whitespace.
 *
 * OUTPUT FORMAT:
 * A single integer representing the minimum number of operations.
 *
 * EXAMPLE:
 * Input:
 * horse ros
 * Output:
 * 3
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int minDistance(const string& word1, const string& word2) {
    int n = word1.size();
    int m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[n][m];
}

int main() {
    string w1, w2;
    if (cin >> w1 >> w2) {
        cout << minDistance(w1, w2) << "\n";
    }
    return 0;
}
