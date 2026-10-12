
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    long long *a = NULL;

    if (n > 0) {
        a = malloc((size_t)n * sizeof(long long));
        if (a == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    printf("Enter array elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &a[i]) != 1) {
            printf("Invalid input.\n");
            free(a);
            return 1;
        }
    }

    // prev2 = best sum up to i-2
    // prev1 = best sum up to i-1
    long long prev2 = 0;
    long long prev1 = 0;

    for (int i = 0; i < n; i++) {
        long long take = a[i] + prev2;
        long long skip = prev1;

        long long current = (take > skip) ? take : skip;

        prev2 = prev1;
        prev1 = current;
    }

    printf("Maximum non-adjacent sum: %lld\n", prev1);

    free(a);
    return 0;
}
