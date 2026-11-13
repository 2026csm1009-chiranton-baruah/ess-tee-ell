/*
PROBLEM: Coin Change II (LeetCode 518) / HackerRank Coin Change
Count combinations that make amount using unlimited copies of each
denomination. Different orders of the same coins are NOT different
combinations.

SOLUTION:
dp[x] counts combinations for amount x using coins processed so far.
Coins are the outer loop; amounts increase inside it.

INPUT:
n amount
coin1 coin2 ... coinn

SAMPLE INPUT:
3 4
1 2 3

SAMPLE OUTPUT:
4

COMPILE: g++ -std=c++17 -O2 08_coin_change_combinations.cpp -o solution
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

    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int x = c; x <= amount; ++x)
            dp[x] += dp[x - c];

    cout << dp[amount] << '\n';
}
