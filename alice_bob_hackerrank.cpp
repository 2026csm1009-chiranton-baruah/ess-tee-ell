/*
2
3
1 3 2
5
5 3 2 1 4

Alice
Bob
*/

#include <stdio.h>
#include <string.h>

#define MAXN 20

int arr[MAXN];
int dp[1 << MAXN];
int n;

/* Check whether the elements in mask are increasing */
int isIncreasing(int mask)
{
    int prev = -1;

    for (int i = 0; i < n; i++)
    {
        if (mask & (1 << i))
        {
            if (prev != -1 && arr[prev] > arr[i])
                return 0;

            prev = i;
        }
    }

    return 1;
}

int solve(int mask)
{
    /* Already increasing -> previous player won */
    if (isIncreasing(mask))
        return 0;

    if (dp[mask] != -1)
        return dp[mask];

    /* Try removing each element */
    for (int i = 0; i < n; i++)
    {
        if (mask & (1 << i))
        {
            int newMask = mask ^ (1 << i);

            /* If opponent loses, current player wins */
            if (solve(newMask) == 0)
            {
                return dp[mask] = 1;
            }
        }
    }

    /* Every move allows opponent to win */
    return dp[mask] = 0;
}

char* permutationGame(int a_count, int* a)
{
    n = a_count;

    for (int i = 0; i < n; i++)
        arr[i] = a[i];

    memset(dp, -1, sizeof(dp));

    int fullMask = (1 << n) - 1;

    if (solve(fullMask))
        return "Alice";
    else
        return "Bob";
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        memset(dp, -1, sizeof(dp));

        int fullMask = (1 << n) - 1;

        if (solve(fullMask))
            printf("Alice\n");
        else
            printf("Bob\n");
    }

    return 0;
}
