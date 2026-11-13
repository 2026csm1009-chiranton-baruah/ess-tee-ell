/*
 * ============================================================================
 * PROBLEM: Minimum Insertion Steps to Make a String Palindrome
 * PLATFORM: LeetCode 1312
 * ============================================================================
 *
 * PROBLEM DESCRIPTION:
 * Given a string `s`, in one step you can insert any character at any index of
 * the string. Return the minimum number of steps to make `s` a palindrome.
 *
 * ALGORITHM (LCS / LPS Complement):
 * - Any character already part of the Longest Palindromic Subsequence (LPS)
 *   does not need a matching partner inserted.
 * - Every character NOT in the LPS must have a mirror character inserted on
 *   the opposite side.
 * - Therefore:
 *   Min Insertions = s.length() - LPS(s) = s.length() - LCS(s, reverse(s)).
 *
 * TIME COMPLEXITY: O(N^2)
 * SPACE COMPLEXITY: O(N) (using space-optimized 1D LCS)
 *
 * INPUT FORMAT:
 * A single string `s`.
 *
 * OUTPUT FORMAT:
 * A single integer representing the minimum insertions needed.
 *
 * EXAMPLE:
 * Input:
 * mbadm
 * Output:
 * 2
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int minInsertions(const string& s) {
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    int n = s.size();

    vector<int> prev(n + 1, 0), curr(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i - 1] == rev_s[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        swap(prev, curr);
    }
    return n - prev[n];
}

int main() {
    string s;
    if (cin >> s) {
        cout << minInsertions(s) << "\n";
    }
    return 0;
}
