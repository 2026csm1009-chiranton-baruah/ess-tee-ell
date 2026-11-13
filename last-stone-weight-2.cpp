/*
 * PROBLEM: LeetCode 1049 - Last Stone Weight II
 * Smash pairs of stones together: if weights x == y, both are destroyed;
 * if x != y, stone of weight |y - x| remains. Return the smallest possible
 * weight of the final remaining stone (or 0 if none remain).
 *
 * SOLUTION APPROACH (Minimum Subset Sum Difference):
 * - Smashing stones is equivalent to assigning '+' or '-' to every stone weight
 *   and minimizing the absolute result: |sum(S1) - sum(S2)|.
 * - We want a subset S1 with sum as close as possible to `totalSum / 2`.
 * - Minimum remaining weight = totalSum - 2 * maxAchievableSum.
 * - Time Complexity: O(N * totalSum/2) | Space Complexity: O(totalSum/2)
 *
 * INPUT FORMAT:
 * Line 1: Integer N (number of stones)
 * Line 2: N space-separated stone weights
 *
 * SAMPLE INPUT:
 * 6
 * 2 7 4 1 8 1
 *
 * SAMPLE OUTPUT:
 * 1
 */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int totalSum = accumulate(stones.begin(), stones.end(), 0);
        int target = totalSum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int stone : stones) {
            for (int j = target; j >= stone; --j) {
                dp[j] = dp[j] || dp[j - stone];
            }
        }

        for (int j = target; j >= 0; --j) {
            if (dp[j]) return totalSum - 2 * j;
        }
        return 0;
    }
};

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<int> stones(n);
    for (int i = 0; i < n; ++i) cin >> stones[i];

    Solution sol;
    cout << sol.lastStoneWeightII(stones) << "\n";
    return 0;
}
