/*
PROBLEM: Multiple-Choice / Grouped Knapsack
There are G groups. Each group contains alternative items. Select at most
one item from each group, with total weight <= W, maximizing total value.

SOLUTION:
For each group, build a fresh DP array from the previous groups' DP.
This ensures that two alternatives from the same group cannot both be chosen.
Selecting no item from a group is allowed.

INPUT:
G W
For each group:
numberOfOptions
Then one line per option: weight value

SAMPLE INPUT:
3 7
2
2 4
3 5
2
3 6
4 7
2
2 3
5 8

SAMPLE OUTPUT:
13

COMPILE: g++ -std=c++17 -O2 13_multiple_choice_knapsack.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int G, W;
    cin >> G >> W;
    vector<long long> dp(W + 1, 0);

    for (int g = 0; g < G; ++g) {
        int options;
        cin >> options;
        vector<pair<int, long long>> items(options);
        for (auto &[w, v] : items) cin >> w >> v;

        vector<long long> ndp = dp; // choose nothing from this group
        for (auto [w, v] : items) {
            for (int cap = w; cap <= W; ++cap)
                ndp[cap] = max(ndp[cap], dp[cap - w] + v);
        }
        dp.swap(ndp);
    }

    cout << dp[W] << '\n';
}
