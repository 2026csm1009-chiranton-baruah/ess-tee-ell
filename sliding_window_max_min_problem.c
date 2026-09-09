#include <stdio.h>
#include <stdlib.h>

/* Comparison function for qsort */
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int maxMin(int k, int arr[], int n) {

    /* Step 1: Sort the array */
    qsort(arr, n, sizeof(int), compare);

    /*
     * Step 2:
     * After sorting, the best group of k elements
     * must appear as a consecutive window.
     */
    int minUnfairness = arr[k - 1] - arr[0];

    for (int i = 1; i <= n - k; i++) {

        int unfairness = arr[i + k - 1] - arr[i];

        if (unfairness < minUnfairness)
            minUnfairness = unfairness;
    }

    return minUnfairness;
}

int main() {
    int n, k;

    scanf("%d", &n);
    scanf("%d", &k);

    int arr[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("%d\n", maxMin(k, arr, n));

    return 0;
}
