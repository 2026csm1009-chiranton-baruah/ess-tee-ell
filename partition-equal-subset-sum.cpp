/*
 * PROBLEM: LeetCode 416 - Partition Equal Subset Sum
 * Given an integer array `nums`, return true if you can partition the array
 * into two subsets such that the sum of the elements in both subsets is equal.
 *
 * SOLUTION APPROACH (0/1 Knapsack - Subset Sum):
 * - Calculate totalSum. If totalSum is odd, equal partition is impossible.
 * - Target capacity = totalSum / 2.
 * - dp[j] represents whether subset sum `j` can be formed using available items.
 * - Iterate `j` backwards from `target` down to `num` so each element is used at most once.
 * - Time Complexity: O(N * target) | Space Complexity: O(target)
 *
 * INPUT FORMAT:
 * Line 1: Integer N (number of elements)
 * Line 2: N space-separated integers
 *
 * SAMPLE INPUT:
 * 4
 * 1 5 11 5
 *
 * SAMPLE OUTPUT:
 * true
 */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        if (totalSum % 2 != 0) return false;

        int target = totalSum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true; // Base case: sum 0 is always achievable with empty subset

        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        return dp[target];
    }
};

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) cin >> nums[i];

    Solution sol;
    cout << (sol.canPartition(nums) ? "true" : "false") << "\n";
    return 0;
}
