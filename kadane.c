#include <stdio.h>

int kadane(int arr[], int n) {
    int max_so_far = arr[0];
    int current_max = arr[0];

    for (int i = 1; i < n; i++) {
        if (current_max + arr[i] > arr[i])
            current_max = current_max + arr[i];
        else
            current_max = arr[i];

        if (current_max > max_so_far)
            max_so_far = current_max;
    }

    return max_so_far;
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Maximum subarray sum = %d\n", kadane(arr, n));

    return 0;
}
