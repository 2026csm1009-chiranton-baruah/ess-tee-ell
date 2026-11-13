/*
 * ============================================================================
 * PROBLEM: Longest Common Substring (Contiguous Subarray)
 * PLATFORM: LeetCode 718 (Maximum Length of Repeated Subarray) / HackerRank
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given two integer arrays (or strings) `nums1` and `nums2`, return the maximum
 * length of a subarray (contiguous substring) that appears in both arrays.
 *
 * ALGORITHM (Contiguous Suffix DP):
 * Unlike LCS where non-contiguous characters carry over previous matches, a
 * common substring must be contiguous. Thus, if characters do not match, the
 * current streak resets to 0.
 * Let dp[i][j] be the length of the longest common suffix of nums1[0..i-1]
 * and nums2[0..j-1].
 * - Transition:
 *   If nums1[i-1] == nums2[j-1]:
 *       dp[i][j] = 1 + dp[i-1][j-1]
 *       ans = max(ans, dp[i][j])
 *   Else:
 *       dp[i][j] = 0
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(N * M)
 *
 * INPUT FORMAT:
 * First line: Two integers N and M (sizes of the two arrays).
 * Second line: N space-separated integers for nums1.
 * Third line: M space-separated integers for nums2.
 *
 * OUTPUT FORMAT:
 * A single integer representing the maximum length of a common contiguous subarray.
 *
 * EXAMPLE:
 * Input:
 * 5 5
 * 1 2 3 2 1
 * 3 2 1 4 7
 * Output:
 * 3
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findLength(const vector<int>& nums1, const vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLen = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                maxLen = max(maxLen, dp[i][j]);
            } else {
                dp[i][j] = 0;
            }
        }
    }
    return maxLen;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> nums1(n), nums2(m);
    for (int i = 0; i < n; ++i) cin >> nums1[i];
    for (int j = 0; j < m; ++j) cin >> nums2[j];

    cout << findLength(nums1, nums2) << "\n";
    return 0;
}
