#include <stdio.h>
#include <limits.h>

int main() {
    int N;
    scanf("%d", &N);
    int s[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
    }

    // dp_no_skip = max sum ending at i without skip
    // dp_skip = max sum ending at i with one skip
    int dp_no_skip = s[0];
    int dp_skip = -10001;  // invalid before first skip
    int max_sum = s[0];

    for (int i = 1; i < N; i++) {
        int new_no_skip = (s[i] > dp_no_skip + s[i]) ? s[i] : dp_no_skip + s[i];
        int new_skip = (dp_no_skip > dp_skip + s[i]) ? dp_no_skip : dp_skip + s[i];

        dp_no_skip = new_no_skip;
        dp_skip = new_skip;

        // track global maximum
        if (dp_no_skip > max_sum) max_sum = dp_no_skip;
        if (dp_skip > max_sum) max_sum = dp_skip;
    }

    printf("%d\n", max_sum);
    return 0;
}

