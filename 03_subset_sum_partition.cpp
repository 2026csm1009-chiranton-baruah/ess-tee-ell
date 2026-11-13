/*
PROBLEM: Partition Equal Subset Sum (LeetCode 416)
Determine whether an integer array can be divided into two subsets with
equal sums. All input values are assumed non-negative.

SOLUTION:
If total sum is odd, answer is false. Otherwise solve subset sum for total/2.
Descending iteration ensures each array element is used at most once.

INPUT:
n
a1 a2 ... an

SAMPLE INPUT:
4
1 5 11 5

SAMPLE OUTPUT:
true

COMPILE: g++ -std=c++17 -O2 03_subset_sum_partition.cpp -o solution
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

    if (sum % 2) {
        cout << "false\n";
        return 0;
    }

    int target = sum / 2;
    vector<char> dp(target + 1, false);
    dp[0] = true;
    for (int x : a)
        for (int s = target; s >= x; --s)
            dp[s] = dp[s] || dp[s - x];

    cout << (dp[target] ? "true" : "false") << '\n';
}
