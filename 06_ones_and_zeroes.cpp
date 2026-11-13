/*
PROBLEM: Ones and Zeroes (LeetCode 474)
Given binary strings and limits m (zeroes) and n (ones), choose the maximum
number of strings without exceeding either limit. Each string can be chosen
at most once.

SOLUTION:
Two-dimensional 0/1 knapsack. For each string, count zeroes z and ones o;
iterate both capacities downward to prevent reusing that string.

INPUT:
N m n
string1
string2
...
stringN

SAMPLE INPUT:
5 5 3
10
0001
111001
1
0

SAMPLE OUTPUT:
4

COMPILE: g++ -std=c++17 -O2 06_ones_and_zeroes.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, m, n;
    cin >> N >> m >> n;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int k = 0; k < N; ++k) {
        string s;
        cin >> s;
        int z = count(s.begin(), s.end(), '0');
        int o = (int)s.size() - z;

        for (int i = m; i >= z; --i)
            for (int j = n; j >= o; --j)
                dp[i][j] = max(dp[i][j], 1 + dp[i - z][j - o]);
    }

    cout << dp[m][n] << '\n';
}
