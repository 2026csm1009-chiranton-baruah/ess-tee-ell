#include <stdio.h>
#include <limits.h>

#define MAX 100

int dp[MAX][MAX];
int split[MAX][MAX];

/* Find minimum multiplication cost */
int matrixChainMultiplication(int p[], int n) {

    /*
        Matrix Ai has dimensions:
        p[i-1] x p[i]

        There are n matrices.
    */

    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    /* len = chain length */
    for (int len = 2; len <= n; len++) {

        for (int i = 1; i <= n - len + 1; i++) {

            int j = i + len - 1;

            dp[i][j] = INT_MAX;

            /*
                Try every possible split:
                (Ai ... Ak) (A(k+1) ... Aj)
            */
            for (int k = i; k < j; k++) {

                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    return dp[1][n];
}

/* Print optimal parenthesization */
void printOptimalParenthesis(int i, int j) {

    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalParenthesis(i, split[i][j]);

    printOptimalParenthesis(split[i][j] + 1, j);

    printf(")");
}

int main() {

    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];

    printf("Enter dimensions:\n");

    /*
        If matrices are:
        A1 = p[0] x p[1]
        A2 = p[1] x p[2]
        ...
        An = p[n-1] x p[n]
    */

    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    int minCost = matrixChainMultiplication(p, n);

    printf("\nMinimum number of scalar multiplications = %d\n",
           minCost);

    printf("Optimal parenthesization = ");
    printOptimalParenthesis(1, n);
    printf("\n");

    return 0;
}
