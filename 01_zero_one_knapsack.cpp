/*
PROBLEM: 0/1 Knapsack (maximum value)
Choose each item at most once. Each item has a weight and value.
Maximize total value without exceeding capacity W.

SOLUTION:
dp[w] = best value achievable with capacity w.
Process capacities in descending order so the current item cannot be reused.

INPUT:
n W
w1 w2 ... wn
v1 v2 ... vn

SAMPLE INPUT:
4 7
2 3 4 5
30 40 50 60

SAMPLE OUTPUT:
90

COMPILE: g++ -std=c++17 -O2 01_zero_one_knapsack.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    if (!(cin >> n >> W)) return 0;
    vector<int> wt(n), val(n);
    for (int &x : wt) cin >> x;
    for (int &x : val) cin >> x;

    vector<long long> dp(W + 1, 0);
    for (int i = 0; i < n; ++i)
        for (int w = W; w >= wt[i]; --w)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);

    cout << dp[W] << '\n';
}
