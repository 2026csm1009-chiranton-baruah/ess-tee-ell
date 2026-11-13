/*
PROBLEM: Unbounded Knapsack / HackerRank "Knapsack"
Given positive numbers, use each number any number of times. Find the
largest sum not exceeding target k. Here each number is both weight and value.

SOLUTION:
Boolean subset reachability is unnecessary: dp[s] stores whether sum s is
reachable. Iterate sums upward so an element may be reused. The answer is
the largest reachable sum <= k.

INPUT:
t
For each test case:
n k
a1 a2 ... an

SAMPLE INPUT:
2
3 12
1 6 9
5 9
3 4 4 4 8

SAMPLE OUTPUT:
12
9

COMPILE: g++ -std=c++17 -O2 02_unbounded_knapsack_sum.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int &x : a) cin >> x;

        vector<char> dp(k + 1, false);
        dp[0] = true;
        for (int x : a)
            for (int s = x; s <= k; ++s)
                if (dp[s - x]) dp[s] = true;

        int ans = k;
        while (ans > 0 && !dp[ans]) --ans;
        cout << ans << '\n';
    }
}
