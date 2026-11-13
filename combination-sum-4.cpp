/*
 * PROBLEM: LeetCode 377 - Combination Sum IV
 * Given an array of distinct integers `nums` and a target integer `target`,
 * return the number of possible combinations (sequences) that add up to `target`.
 * Note: Different sequences are counted as different combinations ([1, 2] != [2, 1]).
 *
 * SOLUTION APPROACH (Unbounded Knapsack - Permutation Counting):
 * - Because order matters, `target` capacity MUST be the outer loop and `nums`
 *   the inner loop. At each sum `j`, every number can be appended as the last element.
 * - Use `unsigned int` (or `uint64_t`) to avoid signed integer overflow on intermediate
 *   unreachable states before the final answer fits in 32-bit int.
 * - Time Complexity: O(target * N) | Space Complexity: O(target)
 *
 * INPUT FORMAT:
 * Line 1: Integer N and integer `target`
 * Line 2: N space-separated distinct positive integers
 *
 * SAMPLE INPUT:
 * 3 4
 * 1 2 3
 *
 * SAMPLE OUTPUT:
 * 7
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;

        for (int j = 1; j <= target; ++j) { // Outer loop = target -> counts permutations
            for (int num : nums) {
                if (j >= num) {
                    dp[j] += dp[j - num];
                }
            }
        }
        return static_cast<int>(dp[target]);
    }
};

int main() {
    int n, target;
    if (!(cin >> n >> target)) return 0;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) cin >> nums[i];

    Solution sol;
    cout << sol.combinationSum4(nums, target) << "\n";
    return 0;
}
