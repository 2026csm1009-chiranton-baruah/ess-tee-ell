#include <stdio.h>

#define MAX 100000

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    int freq[MAX] = {0};

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        freq[arr[i]]++;
    }

    for (int i = 0; i < n; i++) {
        if (freq[arr[i]] == 1)
            printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
