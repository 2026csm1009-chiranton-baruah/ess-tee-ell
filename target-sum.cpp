/*
 * PROBLEM: LeetCode 494 - Target Sum
 * Given an integer array `nums` and an integer `target`, assign '+' or '-' before
 * each integer and return the number of different expressions that evaluate to `target`.
 *
 * SOLUTION APPROACH (Mathematical Reduction to 0/1 Knapsack):
 * - Let P be the subset assigned '+' and N be the subset assigned '-'.
 * - sum(P) - sum(N) = target
 * - sum(P) + sum(N) = totalSum
 * - Adding both equations: 2 * sum(P) = target + totalSum => sum(P) = (target + totalSum) / 2.
 * - Problem reduces to: Count subsets of `nums` with sum equal to `subsetTarget`.
 * - Time Complexity: O(N * subsetTarget) | Space Complexity: O(subsetTarget)
 *
 * INPUT FORMAT:
 * Line 1: Integer N and integer `target`
 * Line 2: N space-separated non-negative integers
 *
 * SAMPLE INPUT:
 * 5 3
 * 1 1 1 1 1
 *
 * SAMPLE OUTPUT:
 * 5
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        if (abs(target) > totalSum || (totalSum + target) % 2 != 0) return 0;

        int subsetTarget = (totalSum + target) / 2;
        vector<int> dp(subsetTarget + 1, 0);
        dp[0] = 1;

        for (int num : nums) {
            for (int j = subsetTarget; j >= num; --j) { // Backwards for 0/1 usage
                dp[j] += dp[j - num];
            }
        }
        return dp[subsetTarget];
    }
};

int main() {
    int n, target;
    if (!(cin >> n >> target)) return 0;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) cin >> nums[i];

    Solution sol;
    cout << sol.findTargetSumWays(nums, target) << "\n";
    return 0;
}
