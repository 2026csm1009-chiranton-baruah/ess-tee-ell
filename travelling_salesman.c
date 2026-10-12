
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

int main(void) {
    int n;

    printf("Enter number of cities (2-20): ");
    if (scanf("%d", &n) != 1 || n < 2 || n > 20) {
        printf("Invalid number of cities.\n");
        return 1;
    }

    long long cost[20][20];

    printf("Enter the %d x %d cost matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%lld", &cost[i][j]) != 1 ||
                cost[i][j] < 0) {
                printf("Invalid cost matrix.\n");
                return 1;
            }
        }
    }

    int states = 1 << n;

    long long *dp = malloc(
        (size_t)states * (size_t)n * sizeof(long long)
    );

    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    #define DP(mask, city) dp[(size_t)(mask) * n + (city)]

    for (size_t i = 0; i < (size_t)states * n; i++)
        dp[i] = INF;

    // Start at city 0; only city 0 is visited.
    DP(1, 0) = 0;

    for (int mask = 1; mask < states; mask++) {
        // Current endpoint must be in the visited set.
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)) || DP(mask, u) == INF)
                continue;

            // Try visiting every unvisited city.
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v))
                    continue;

                int nextMask = mask | (1 << v);
                long long nextCost = DP(mask, u) + cost[u][v];

                if (nextCost < DP(nextMask, v))
                    DP(nextMask, v) = nextCost;
            }
        }
    }

    int fullMask = states - 1;
    long long answer = INF;

    // Visit every city, then return to city 0.
    for (int u = 1; u < n; u++) {
        if (DP(fullMask, u) != INF &&
            DP(fullMask, u) <= INF - cost[u][0]) {
            long long total = DP(fullMask, u) + cost[u][0];

            if (total < answer)
                answer = total;
        }
    }

    if (answer == INF)
        printf("No valid tour found.\n");
    else
        printf("Minimum TSP tour cost: %lld\n", answer);

    free(dp);
    return 0;
}
