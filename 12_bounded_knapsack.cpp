/*
PROBLEM: Bounded Knapsack
Each item type has weight w[i], value v[i], and at most q[i] copies.
Maximize value without exceeding capacity W.

SOLUTION:
Binary-decompose each quantity q into 0/1 bundles (1, 2, 4, ... and
remainder). A bundle of count c becomes one 0/1 item with weight c*w and
value c*v. Descending capacity iteration prevents bundle reuse.

INPUT:
n W
For each item type, one line:
weight value quantity

SAMPLE INPUT:
3 10
2 3 3
3 4 2
5 8 1

SAMPLE OUTPUT:
14

COMPILE: g++ -std=c++17 -O2 12_bounded_knapsack.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n >> W;
    vector<long long> dp(W + 1, 0);

    for (int i = 0; i < n; ++i) {
        int w, q;
        long long v;
        cin >> w >> v >> q;

        int power = 1;
        while (q > 0) {
            int take = min(power, q);
            long long bundleW = 1LL * take * w;
            long long bundleV = 1LL * take * v;
            if (bundleW <= W) {
                for (int cap = W; cap >= bundleW; --cap)
                    dp[cap] = max(dp[cap],
                                  dp[cap - (int)bundleW] + bundleV);
            }
            q -= take;
            power *= 2;
        }
    }

    cout << dp[W] << '\n';
}
