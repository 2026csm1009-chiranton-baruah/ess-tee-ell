#include <stdio.h>

int removeDuplicates(int arr[], int n) {
    int newSize = 0;

    for (int i = 0; i < n; i++) {
        int alreadyExists = 0;

        // Check whether arr[i] has appeared before
        for (int j = 0; j < newSize; j++) {
            if (arr[j] == arr[i]) {
                alreadyExists = 1;
                break;
            }
        }

        // Keep only the first occurrence
        if (!alreadyExists) {
            arr[newSize] = arr[i];
            newSize++;
        }
    }

    return newSize;
}

int main() {
    int n;

    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int newSize = removeDuplicates(arr, n);

    for (int i = 0; i < newSize; i++)
        printf("%d ", arr[i]);

    printf("\n");

    return 0;
}
