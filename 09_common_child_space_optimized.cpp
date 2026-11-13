/*
 * ============================================================================
 * PROBLEM: Common Child (Space-Optimized LCS for Large Constraints)
 * PLATFORM: HackerRank (Common Child)
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * A string is said to be a child of another string if it can be formed by
 * deleting 0 or more characters from the other string. Letters cannot be
 * rearranged. Given two strings of equal length (up to 5,000 characters),
 * find the longest string that can be constructed such that it is a child of
 * both.
 *
 * ALGORITHM (1D Rolling Array Space-Optimized DP):
 * - Standard 2D DP uses O(N * M) memory (~100 MB for N=5000), which is tight
 *   on strict memory limits.
 * - Notice that computing row `i` only requires values from row `i-1`.
 * - We maintain two 1D arrays `prev` and `curr` of size M + 1:
 *   If s1[i-1] == s2[j-1]:
 *       curr[j] = 1 + prev[j-1]
 *   Else:
 *       curr[j] = max(prev[j], curr[j-1])
 * - After finishing row `i`, swap `prev` and `curr`.
 *
 * TIME COMPLEXITY: O(N * M)
 * SPACE COMPLEXITY: O(M)
 *
 * INPUT FORMAT:
 * Two lines, each containing one uppercase string (s1 and s2).
 *
 * OUTPUT FORMAT:
 * A single integer representing the length of the longest common child.
 *
 * EXAMPLE:
 * Input:
 * HARRY
 * SALLY
 * Output:
 * 2
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int commonChild(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        swap(prev, curr);
    }
    return prev[m];
}

int main() {
    string s1, s2;
    if (cin >> s1 >> s2) {
        cout << commonChild(s1, s2) << "\n";
    }
    return 0;
}
