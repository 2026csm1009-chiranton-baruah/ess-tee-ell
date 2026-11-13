/*
 * PROBLEM: LeetCode 474 - Ones and Zeroes
 * Given an array of binary strings `strs` and two integers `m` and `n`,
 * return the size of the largest subset of `strs` such that there are at most
 * `m` 0's and `n` 1's in the subset.
 *
 * SOLUTION APPROACH (2D Cost 0/1 Knapsack):
 * - Each string is an item with two weights: (zeros, ones) and value = 1.
 * - dp[i][j] = max strings selectable using at most `i` zeros and `j` ones.
 * - Both capacity loops run backwards to prevent reusing the same string.
 * - Time Complexity: O(L * m * n) | Space Complexity: O(m * n)
 *
 * INPUT FORMAT:
 * Line 1: Integer L (number of strings), integer `m` (max 0s), integer `n` (max 1s)
 * Next L lines: Binary strings
 *
 * SAMPLE INPUT:
 * 5 5 3
 * 10
 * 0001
 * 111001
 * 1
 * 0
 *
 * SAMPLE OUTPUT:
 * 4
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (const string& s : strs) {
            int zeros = count(s.begin(), s.end(), '0');
            int ones = s.size() - zeros;

            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1);
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    int l, m, n;
    if (!(cin >> l >> m >> n)) return 0;
    vector<string> strs(l);
    for (int i = 0; i < l; ++i) cin >> strs[i];

    Solution sol;
    cout << sol.findMaxForm(strs, m, n) << "\n";
    return 0;
}
