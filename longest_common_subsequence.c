#include <stdio.h>
#include <string.h>

#define MAX 1000

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int LCS(char *X, char *Y)
{
    int m = strlen(X);
    int n = strlen(Y);

    int dp[m + 1][n + 1];

    // Base cases
    for (int i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= n; j++)
        dp[0][j] = 0;

    // Fill DP table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j],
                               dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

int main()
{
    char X[MAX], Y[MAX];

    scanf("%s", X);
    scanf("%s", Y);

    printf("LCS length = %d\n", LCS(X, Y));

    return 0;
}
