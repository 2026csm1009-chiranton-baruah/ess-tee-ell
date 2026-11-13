/*
PROBLEM: Profitable Schemes (LeetCode 879)
Each job requires group[i] people and earns profit[i]. Count subsets of jobs
using at most n people and earning at least minProfit. Each job is used at
most once. Return the count modulo 1,000,000,007.

SOLUTION:
dp[people][profit] counts schemes, with profit capped at minProfit.
Process each job and scan people/profit downward (0/1 selection).

INPUT:
n minProfit jobCount
group[0] ... group[jobCount-1]
profit[0] ... profit[jobCount-1]

SAMPLE INPUT:
5 3 2
2 2
2 3

SAMPLE OUTPUT:
2

COMPILE: g++ -std=c++17 -O2 10_profitable_schemes.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, minProfit, jobs;
    cin >> n >> minProfit >> jobs;
    vector<int> group(jobs), profit(jobs);
    for (int &x : group) cin >> x;
    for (int &x : profit) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
    dp[0][0] = 1;

    for (int k = 0; k < jobs; ++k) {
        for (int people = n; people >= group[k]; --people) {
            for (int p = minProfit; p >= 0; --p) {
                int np = min(minProfit, p + profit[k]);
                dp[people][np] = (dp[people][np] +
                                  dp[people - group[k]][p]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int people = 0; people <= n; ++people)
        ans = (ans + dp[people][minProfit]) % MOD;
    cout << ans << '\n';
}
