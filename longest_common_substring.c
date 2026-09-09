#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int longestCommonSubstring(char *X, char *Y)
{
    int m = strlen(X);
    int n = strlen(Y);

    int dp[m + 1][n + 1];

    int ans = 0;

    // Initialize first row and column
    for (int i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= n; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];

                ans = max(ans, dp[i][j]);
            }
            else
            {
                // Must RESET to 0
                dp[i][j] = 0;
            }
        }
    }

    return ans;
}

int main()
{
    char X[1000], Y[1000];

    scanf("%s", X);
    scanf("%s", Y);

    printf("Longest Common Substring length = %d\n",
           longestCommonSubstring(X, Y));

    return 0;
}
