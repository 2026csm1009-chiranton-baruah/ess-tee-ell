#include <stdio.h>

#define MAX 10001

int main() {
    int N;
    scanf("%d", &N);
    int freq[MAX] = {0};

    for (int i = 0; i < N; i++) {
        int t;
        scanf("%d", &t);
        freq[t]++;
    }

    long long dp[MAX] = {0};
    dp[0] = 0;
    dp[1] = (long long)freq[1] * 1;

    for (int i = 2; i < MAX; i++) {
        long long take = dp[i-2] + (long long)freq[i] * i;
        long long skip = dp[i-1];
        dp[i] = (take > skip) ? take : skip;
    }

    printf("%lld\n", dp[MAX-1]);
    return 0;
}

