
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (INT_MAX / 2)

int main(void) {
    int n, amount;

    printf("Enter number of coin denominations and target amount: ");
    if (scanf("%d %d", &n, &amount) != 2 ||
        n <= 0 || amount < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *coins = malloc((size_t)n * sizeof(int));
    int *dp = malloc(((size_t)amount + 1) * sizeof(int));

    if (coins == NULL || dp == NULL) {
        printf("Memory allocation failed.\n");
        free(coins);
        free(dp);
        return 1;
    }

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &coins[i]) != 1 || coins[i] <= 0) {
            printf("Invalid coin denomination.\n");
            free(coins);
            free(dp);
            return 1;
        }
    }

    for (int a = 0; a <= amount; a++)
        dp[a] = INF;

    dp[0] = 0;

    for (int a = 1; a <= amount; a++) {
        for (int i = 0; i < n; i++) {
            if (coins[i] <= a && dp[a - coins[i]] != INF) {
                int candidate = dp[a - coins[i]] + 1;
                if (candidate < dp[a])
                    dp[a] = candidate;
            }
        }
    }

    if (dp[amount] == INF)
        printf("Minimum coins required: -1 (impossible)\n");
    else
        printf("Minimum coins required: %d\n", dp[amount]);

    free(coins);
    free(dp);
    return 0;
}
