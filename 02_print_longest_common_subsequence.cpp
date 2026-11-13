/*
 * ============================================================================
 * PROBLEM: Print the Longest Common Subsequence (Reconstruction)
 * PLATFORM: HackerRank (The Longest Common Subsequence - Array/String version)
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two sequences A of length N and B of length M, find and print the
 * actual longest common subsequence (not just its length). If there are
 * multiple valid LCSs, print any one of them.
 *
 * ALGORITHM (DP Table + Backtracking):
 * 1. Build the standard 2D LCS DP table `dp[N+1][M+1]`.
 * 2. Start from the bottom-right corner (i = N, j = M) and trace backward:
 *    - If A[i-1] == B[j-1], this element is part of the LCS. Add it to the
 *      result and move diagonally: i--, j--.
 *    - Else, move in the direction of the larger neighbor:
 *      If dp[i-1][j] > dp[i][j-1], move up (i--); otherwise move left (j--).
 * 3. Reverse the collected elements to obtain the LCS in forward order.
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * First line: Two integers N and M (lengths of the sequences).
 * Second line: N space-separated integers representing sequence A.
 * Third line: M space-separated integers representing sequence B.
 *
 * OUTPUT FORMAT:
 * Space-separated integers representing the Longest Common Subsequence.
 *
 * EXAMPLE:
 * Input:
 * 5 6
 * 1 2 3 4 1
 * 3 4 1 2 1 3
 * Output:
 * 1 2 3
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getLCS(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    int m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Backtrack to reconstruct the LCS
    vector<int> lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs.push_back(a[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int j = 0; j < m; ++j) cin >> b[j];

    vector<int> result = getLCS(a, b);
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i + 1 < result.size() ? " " : "");
    }
    cout << "\n";
    return 0;
}
