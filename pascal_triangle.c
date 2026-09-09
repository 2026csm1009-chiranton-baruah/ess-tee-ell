#include <stdio.h>

int main() {
    int n;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    int a[n][n];

    // First element
    a[0][0] = 1;

    for (int i = 0; i < n; i++) {
        a[i][0] = 1;
        a[i][i] = 1;

        for (int j = 1; j < i; j++) {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }

    // Print triangle
    for (int i = 0; i < n; i++) {

        // Optional formatting
        for (int space = 0; space < n - i - 1; space++)
            printf(" ");

        for (int j = 0; j <= i; j++)
            printf("%d ", a[i][j]);

        printf("\n");
    }

    return 0;
}
