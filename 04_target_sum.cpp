/*
PROBLEM: Target Sum (LeetCode 494)
Assign '+' or '-' to every array element so that the resulting expression
equals target. Count the number of assignments. Assumes non-negative values.

SOLUTION:
Let P be the sum of positive-sign elements and N the sum of negative-sign
magnitudes. P-N=target and P+N=sum, so P=(sum+target)/2.
Count 0/1 subsets with that sum. Use long long for counts.

INPUT:
n target
a1 a2 ... an

SAMPLE INPUT:
5 3
1 1 1 1 1

SAMPLE OUTPUT:
5

COMPILE: g++ -std=c++17 -O2 04_target_sum.cpp -o solution
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    vector<int> a(n);
    int sum = 0;
    for (int &x : a) { cin >> x; sum += x; }

    if (abs(target) > sum || (sum + target) % 2 != 0) {
        cout << 0 << '\n';
        return 0;
    }

    int wanted = (sum + target) / 2;
    if (wanted < 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<long long> dp(wanted + 1, 0);
    dp[0] = 1;
    for (int x : a)
        for (int s = wanted; s >= x; --s)
            dp[s] += dp[s - x];

    cout << dp[wanted] << '\n';
}
