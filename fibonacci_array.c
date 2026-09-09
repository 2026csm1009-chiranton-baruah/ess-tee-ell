#include <stdio.h>

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int dp[n + 1];

    dp[0] = 0;

    if (n >= 1)
        dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    printf("Fibonacci(%d) = %d\n", n, dp[n]);

    return 0;
}
