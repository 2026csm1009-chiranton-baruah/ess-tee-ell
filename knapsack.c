#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int knapsack(int W, int wt[], int val[], int n)
{
    // dp[w] = maximum value achievable with capacity w
    int dp[W + 1];

    // Initially, value is 0 for every capacity
    for (int w = 0; w <= W; w++)
        dp[w] = 0;

    // Process each item
    for (int i = 0; i < n; i++)
    {
        // IMPORTANT: go backwards
        for (int w = W; w >= wt[i]; w--)
        {
            dp[w] = max(
                dp[w],
                val[i] + dp[w - wt[i]]
            );
        }
    }

    return dp[W];
}

int main()
{
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    int wt[n], val[n];

    printf("Enter weights:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter values:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    int answer = knapsack(W, wt, val, n);

    printf("Maximum value = %d\n", answer);

    return 0;
}
