/*
 * ============================================================================
 * PROBLEM: Max Dot Product of Two Subsequences (Non-Empty Weighted LCS)
 * PLATFORM: LeetCode 1458
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two arrays `nums1` and `nums2`, return the maximum dot product between
 * non-empty subsequences of `nums1` and `nums2` with the same length.
 *
 * ALGORITHM (Non-Empty 2D DP with Negative Value Handling):
 * - Unlike standard LCS where an empty subsequence gives 0, here the chosen
 *   subsequences MUST be non-empty (so the answer can be negative if all pairs
 *   produce negative products).
 * - Let dp[i][j] be the max dot product using non-empty subsequences from
 *   nums1[0..i-1] and nums2[0..j-1].
 * - Initialize dp table with a very small negative sentinel (-1e9).
 * - Transition:
 *   int prod = nums1[i-1] * nums2[j-1];
 *   dp[i][j] = max({
 *       prod,                      // Start a brand-new subsequence pair here
 *       prod + dp[i-1][j-1],       // Extend best previous subsequence pair
 *       dp[i-1][j],                // Skip nums1[i-1]
 *       dp[i][j-1]                 // Skip nums2[j-1]
 *   });
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * First line: Two integers N and M.
 * Second line: N space-separated integers for nums1.
 * Third line: M space-separated integers for nums2.
 *
 * OUTPUT FORMAT:
 * A single integer representing the maximum dot product.
 *
 * EXAMPLE:
 * Input:
 * 4 3
 * 2 1 -2 5
 * 3 0 -6
 * Output:
 * 18
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxDotProduct(const vector<int>& nums1, const vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    const int NEG_INF = -1e9;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, NEG_INF));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int prod = nums1[i - 1] * nums2[j - 1];
            dp[i][j] = max({
                prod,
                prod + dp[i - 1][j - 1],
                dp[i - 1][j],
                dp[i][j - 1]
            });
        }
    }
    return dp[n][m];
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> nums1(n), nums2(m);
    for (int i = 0; i < n; ++i) cin >> nums1[i];
    for (int j = 0; j < m; ++j) cin >> nums2[j];

    cout << maxDotProduct(nums1, nums2) << "\n";
    return 0;
}
