#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LEN 1000

int min3(int a, int b, int c) {
    int result = (a < b) ? a : b;
    return (result < c) ? result : c;
}

int main(void) {
    char s1[MAX_LEN + 1];
    char s2[MAX_LEN + 1];

    printf("Enter first string: ");
    if (scanf("%1000s", s1) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter second string: ");
    if (scanf("%1000s", s2) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    size_t m = strlen(s1);
    size_t n = strlen(s2);

    if (m + 1 > SIZE_MAX / (n + 1) ||
        (m + 1) * (n + 1) > SIZE_MAX / sizeof(int)) {
        printf("Input is too large.\n");
        return 1;
    }

    int *dp = malloc((m + 1) * (n + 1) * sizeof(int));

    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    #define DP(i, j) dp[(i) * (n + 1) + (j)]

    // Empty-string base cases.
    for (size_t i = 0; i <= m; i++)
        DP(i, 0) = (int)i;

    for (size_t j = 0; j <= n; j++)
        DP(0, j) = (int)j;

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                DP(i, j) = DP(i - 1, j - 1);
            } else {
                int deletion = DP(i - 1, j);
                int insertion = DP(i, j - 1);
                int replacement = DP(i - 1, j - 1);

                DP(i, j) = 1 + min3(
                    deletion, insertion, replacement
                );
            }
        }
    }

    printf("Edit distance: %d\n", DP(m, n));

    free(dp);
    return 0;
}
