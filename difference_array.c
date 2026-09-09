#include <stdio.h>
#include <stdlib.h>

long arrayManipulation(int n, int queries[][3], int m) {
    long *diff = calloc(n + 2, sizeof(long));

    /* Apply range updates */
    for (int i = 0; i < m; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        long k = queries[i][2];

        diff[a] += k;
        diff[b + 1] -= k;
    }

    /* Prefix sum gives actual array values */
    long current = 0;
    long maximum = 0;

    for (int i = 1; i <= n; i++) {
        current += diff[i];

        if (current > maximum)
            maximum = current;
    }

    free(diff);
    return maximum;
}

int main() {
    int n, m;

    scanf("%d %d", &n, &m);

    int (*queries)[3] = malloc(m * sizeof(*queries));

    for (int i = 0; i < m; i++)
        scanf("%d %d %d",
              &queries[i][0],
              &queries[i][1],
              &queries[i][2]);

    printf("%ld\n", arrayManipulation(n, queries, m));

    free(queries);

    return 0;
}
