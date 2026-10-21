#include <stdio.h>
#include <limits.h>

#define MAXN 505

long long dp[MAXN][MAXN];
long long v[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &v[i]);

    for (int len = 2; len < n; len++) {
        for (int i = 0; i + len < n; i++) {
            int j = i + len;
            dp[i][j] = LLONG_MAX;
            for (int k = i + 1; k < j; k++) {
                long long cost = dp[i][k] + dp[k][j] + v[i] * v[k] * v[j];
                if (cost < dp[i][j]) dp[i][j] = cost;
            }
        }
    }

    printf("%lld\n", dp[0][n-1]);
    return 0;
}
