#include <stdio.h>

int main() {
    int n;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    long long bell[n][n];

    // First element
    bell[0][0] = 1;

    for (int i = 1; i < n; i++) {
        // First element of each row = last element of previous row
        bell[i][0] = bell[i - 1][i - 1];

        // Remaining elements
        for (int j = 1; j <= i; j++) {
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
        }
    }

    printf("\nBell Triangle:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%lld ", bell[i][j]);
        }
        printf("\n");
    }

    return 0;
}
