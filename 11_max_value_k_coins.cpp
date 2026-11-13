/*
PROBLEM: Maximum Value of K Coins From Piles (LeetCode 2218)
There are piles of coins; only coins at the top of a pile can be taken.
Take exactly k coins in total and maximize their value.

SOLUTION:
For each pile, precompute prefix sums. dp[x] is the maximum value using
exactly x coins from piles processed so far. For a pile, try taking 0..q
coins from its top. Use a fresh array so a pile is processed only once.

INPUT:
numberOfPiles k
For each pile:
pileSize coin1 coin2 ... coinPileSize

SAMPLE INPUT:
2 3
2 1 100
3 10 10 20

SAMPLE OUTPUT:
110

COMPILE: g++ -std=c++17 -O2 11_max_value_k_coins.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int piles, k;
    cin >> piles >> k;
    const long long NEG = -(1LL << 60);
    vector<long long> dp(k + 1, NEG);
    dp[0] = 0;

    for (int i = 0; i < piles; ++i) {
        int sz;
        cin >> sz;
        vector<long long> pref(sz + 1, 0);
        for (int j = 1; j <= sz; ++j) {
            long long x;
            cin >> x;
            pref[j] = pref[j - 1] + x;
        }

        vector<long long> ndp(k + 1, NEG);
        for (int used = 0; used <= k; ++used) {
            if (dp[used] == NEG) continue;
            for (int take = 0; take <= sz && used + take <= k; ++take)
                ndp[used + take] = max(ndp[used + take],
                                       dp[used] + pref[take]);
        }
        dp.swap(ndp);
    }

    cout << (dp[k] == NEG ? -1 : dp[k]) << '\n';
}
