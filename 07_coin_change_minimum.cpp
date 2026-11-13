/*
PROBLEM: Coin Change (LeetCode 322)
Given coin denominations and an amount, return the minimum number of coins
needed to make the amount, or -1 if it is impossible. Coins are reusable.

SOLUTION:
dp[x] is the minimum coins needed for amount x. Initialize to INF except
dp[0]=0. For each coin, scan amounts upward (unbounded reuse).

INPUT:
n amount
coin1 coin2 ... coinn

SAMPLE INPUT:
3 11
1 2 5

SAMPLE OUTPUT:
3

COMPILE: g++ -std=c++17 -O2 07_coin_change_minimum.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, amount;
    cin >> n >> amount;
    vector<int> coins(n);
    for (int &c : coins) cin >> c;

    const int INF = 1e9;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int c : coins)
        for (int x = c; x <= amount; ++x)
            if (dp[x - c] != INF)
                dp[x] = min(dp[x], dp[x - c] + 1);

    cout << (dp[amount] == INF ? -1 : dp[amount]) << '\n';
}
