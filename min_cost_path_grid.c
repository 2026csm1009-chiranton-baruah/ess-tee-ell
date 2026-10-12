#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int m, n;

    printf("Enter rows and columns: ");
    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || n <= 0) {
        printf("Invalid dimensions.\n");
        return 1;
    }

    if ((size_t)m > SIZE_MAX / (size_t)n ||
        (size_t)m * (size_t)n >
            SIZE_MAX / sizeof(long long)) {
        printf("Grid is too large.\n");
        return 1;
    }

    long long *grid = malloc(
        (size_t)m * (size_t)n * sizeof(long long));
    long long *dp = malloc(
        (size_t)m * (size_t)n * sizeof(long long));

    if (grid == NULL || dp == NULL) {
        printf("Memory allocation failed.\n");
        free(grid);
        free(dp);
        return 1;
    }

    printf("Enter grid costs:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%lld", &grid[(size_t)i * n + j]) != 1) {
                printf("Invalid input.\n");
                free(grid);
                free(dp);
                return 1;
            }
        }
    }

    #define GRID(i, j) grid[(size_t)(i) * n + (j)]
    #define DP(i, j) dp[(size_t)(i) * n + (j)]

    DP(0, 0) = GRID(0, 0);

    for (int j = 1; j < n; j++)
        DP(0, j) = DP(0, j - 1) + GRID(0, j);

    for (int i = 1; i < m; i++)
        DP(i, 0) = DP(i - 1, 0) + GRID(i, 0);

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            long long top = DP(i - 1, j);
            long long left = DP(i, j - 1);

            DP(i, j) = GRID(i, j) +
                       (top < left ? top : left);
        }
    }

    printf("Minimum path cost: %lld\n", DP(m - 1, n - 1));

    free(grid);
    free(dp);
    return 0;
}
