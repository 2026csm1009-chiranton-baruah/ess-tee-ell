/*
PROBLEM: Combination Sum IV (LeetCode 377)
Count ordered sequences of numbers that sum to target. Each number may be
used repeatedly; different orders count as different sequences.

SOLUTION:
dp[x] counts ordered sequences summing to x. Amount is the outer loop and
candidate numbers are the inner loop, so order matters.

INPUT:
n target
a1 a2 ... an

SAMPLE INPUT:
3 4
1 2 3

SAMPLE OUTPUT:
7

COMPILE: g++ -std=c++17 -O2 09_combination_sum_iv.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<long long> dp(target + 1, 0);
    dp[0] = 1;
    for (int s = 1; s <= target; ++s)
        for (int x : a)
            if (s >= x)
                dp[s] += dp[s - x];

    cout << dp[target] << '\n';
}
