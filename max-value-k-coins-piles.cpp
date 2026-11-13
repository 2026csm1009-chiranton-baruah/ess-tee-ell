/*
 * PROBLEM: LeetCode 2218 - Maximum Value of K Coins From Piles
 * There are `n` piles of coins on a table. In one move, you can take the top coin
 * from any pile. Return the maximum total value of coins you can have if you
 * choose at most `k` coins optimally.
 *
 * SOLUTION APPROACH (Multiple-Choice / Grouped Knapsack):
 * - Taking `x` coins from a pile must be a prefix of length `x` of that pile.
 * - Each pile is a "group" of mutually exclusive choices: take 1, 2, ..., min(size, k) coins.
 * - Precompute prefix sums for each pile, then run 0/1 grouped knapsack over `k`.
 * - Time Complexity: O(totalCoins * k) | Space Complexity: O(k)
 *
 * INPUT FORMAT:
 * Line 1: Integer N (number of piles) and integer K (max coins to pick)
 * Next N lines: Integer M (pile size) followed by M space-separated coin values (top to bottom)
 *
 * SAMPLE INPUT:
 * 2 2
 * 3 1 100 3
 * 3 7 8 9
 *
 * SAMPLE OUTPUT:
 * 101
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        vector<int> dp(k + 1, 0);

        for (const auto& pile : piles) {
            int m = pile.size();
            vector<int> prefix(m + 1, 0);
            for (int i = 0; i < m; ++i) {
                prefix[i + 1] = prefix[i] + pile[i];
            }

            // Iterate total capacity `j` backwards so we pick at most ONE prefix per pile
            for (int j = k; j >= 1; --j) {
                int maxTake = min(m, j);
                for (int x = 1; x <= maxTake; ++x) {
                    dp[j] = max(dp[j], dp[j - x] + prefix[x]);
                }
            }
        }
        return dp[k];
    }
};

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<vector<int>> piles(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        piles[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> piles[i][j];
    }

    Solution sol;
    cout << sol.maxValueOfCoins(piles, k) << "\n";
    return 0;
}
