#include <stdio.h>
#include <stdlib.h>

long long merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;       // Left subarray index
    int j = mid + 1;    // Right subarray index
    int k = left;       // Temporary array index

    long long inversions = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            /*
             * arr[i] > arr[j].
             *
             * Since the left half is already sorted,
             * arr[i], arr[i+1], ..., arr[mid]
             * are all greater than arr[j].
             */
            temp[k++] = arr[j++];

            inversions += (mid - i + 1);
        }
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inversions;
}

long long mergeSort(int arr[], int temp[], int left, int right) {
    if (left >= right)
        return 0;

    int mid = left + (right - left) / 2;

    long long inversions = 0;

    inversions += mergeSort(arr, temp, left, mid);
    inversions += mergeSort(arr, temp, mid + 1, right);

    inversions += merge(arr, temp, left, mid, right);

    return inversions;
}

long long countInversions(int arr[], int n) {
    int *temp = malloc(n * sizeof(int));

    if (temp == NULL)
        return -1;

    long long result = mergeSort(arr, temp, 0, n - 1);

    free(temp);

    return result;
}

int main() {
    int n;

    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    if (arr == NULL)
        return 1;

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("%lld\n", countInversions(arr, n));

    free(arr);

    return 0;
}
