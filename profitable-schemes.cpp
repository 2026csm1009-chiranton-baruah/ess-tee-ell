/*
 * PROBLEM: LeetCode 879 - Profitable Schemes
 * There is a group of `n` members and a list of crimes. Crime `i` requires `group[i]`
 * members and generates `profit[i]` profit. Return the number of schemes that can
 * be chosen such that total members <= `n` and total profit >= `minProfit` (mod 10^9 + 7).
 *
 * SOLUTION APPROACH (2D 0/1 Knapsack with Clamped Profit Dimension):
 * - State: dp[members][profit] = number of schemes using `members` people and achieving
 *   at least `profit` (clamped at `minProfit` so any profit >= minProfit maps to `minProfit`).
 * - Transition: newProfit = min(minProfit, p + currProfit).
 * - Time Complexity: O(Crimes * n * minProfit) | Space Complexity: O(n * minProfit)
 *
 * INPUT FORMAT:
 * Line 1: Integer `n` (members), integer `minProfit`, integer `m` (number of crimes)
 * Line 2: `m` space-separated integers for `group`
 * Line 3: `m` space-separated integers for `profit`
 *
 * SAMPLE INPUT:
 * 5 3 2
 * 2 2
 * 2 3
 *
 * SAMPLE OUTPUT:
 * 2
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        const int MOD = 1e9 + 7;
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
        dp[0][0] = 1; // 1 way with 0 members and 0 profit

        for (size_t idx = 0; idx < group.size(); ++idx) {
            int g = group[idx];
            int p = profit[idx];

            for (int members = n; members >= g; --members) {
                for (int currProfit = minProfit; currProfit >= 0; --currProfit) {
                    int nextProfit = min(minProfit, currProfit + p);
                    dp[members][nextProfit] = (dp[members][nextProfit] + dp[members - g][currProfit]) % MOD;
                }
            }
        }

        int totalWays = 0;
        for (int members = 0; members <= n; ++members) {
            totalWays = (totalWays + dp[members][minProfit]) % MOD;
        }
        return totalWays;
    }
};

int main() {
    int n, minProfit, m;
    if (!(cin >> n >> minProfit >> m)) return 0;
    vector<int> group(m), profit(m);
    for (int i = 0; i < m; ++i) cin >> group[i];
    for (int i = 0; i < m; ++i) cin >> profit[i];

    Solution sol;
    cout << sol.profitableSchemes(n, minProfit, group, profit) << "\n";
    return 0;
}
