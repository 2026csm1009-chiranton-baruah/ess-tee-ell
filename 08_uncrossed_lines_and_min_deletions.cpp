/*
 * ============================================================================
 * PROBLEM: Uncrossed Lines / Minimum Deletions to Make Two Strings Equal
 * PLATFORM: LeetCode 1035 (Uncrossed Lines) & LeetCode 583 (Delete Operation)
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * 1. Uncrossed Lines (LC 1035): Given two integer arrays `nums1` and `nums2`,
 *    draw connecting lines between equal numbers nums1[i] == nums2[j] such that
 *    no two lines intersect. Return the maximum number of connecting lines.
 *    -> Insight: Non-intersecting lines preserve relative order, making this
 *       100% equivalent to finding the length of the LCS!
 * 2. Delete Operation for Two Strings (LC 583): Return the minimum number of
 *    steps (single-character deletions) required to make `word1` and `word2`
 *    the same.
 *    -> Insight: Keep the LCS intact and delete all other characters:
 *       Min Deletions = (N - LCS) + (M - LCS) = N + M - 2 * LCS.
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
 * Two integers on separate lines:
 * Line 1: Maximum uncrossed lines (LCS length).
 * Line 2: Minimum deletions required to make both sequences identical.
 *
 * EXAMPLE:
 * Input:
 * 3 3
 * 1 4 2
 * 1 2 4
 * Output:
 * 2
 * 2
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int computeLCS(const vector<int>& nums1, const vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
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

    int lcsLen = computeLCS(nums1, nums2);
    int minDeletions = (n - lcsLen) + (m - lcsLen);

    cout << lcsLen << "\n";
    cout << minDeletions << "\n";
    return 0;
}
