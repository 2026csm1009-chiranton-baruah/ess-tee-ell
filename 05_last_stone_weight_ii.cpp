/*
PROBLEM: Last Stone Weight II (LeetCode 1049)
Partition stone weights into two groups so the absolute difference of their
sums is minimized. This is equivalent to finding a subset sum closest to
half of the total weight.

INPUT:
n
w1 w2 ... wn

SAMPLE INPUT:
6
2 7 4 1 8 1

SAMPLE OUTPUT:
1

COMPILE: g++ -std=c++17 -O2 05_last_stone_weight_ii.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for (int &x : a) { cin >> x; sum += x; }

    int half = sum / 2;
    vector<char> dp(half + 1, false);
    dp[0] = true;
    for (int x : a)
        for (int s = half; s >= x; --s)
            dp[s] = dp[s] || dp[s - x];

    for (int s = half; s >= 0; --s) {
        if (dp[s]) {
            cout << sum - 2 * s << '\n';
            return 0;
        }
    }
}
