/*
Input: [1,3] [2,6] [8,10] [9,12] [15,18]
Output: [1,6] [8,12] [15,18]
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

/* Sort by start time, then by end time */
int compare(const void *a, const void *b) {
    Interval *x = (Interval *)a;
    Interval *y = (Interval *)b;

    if (x->start != y->start)
        return x->start - y->start;

    return x->end - y->end;
}

void mergeIntervals(Interval arr[], int n) {
    if (n <= 0)
        return;

    qsort(arr, n, sizeof(Interval), compare);

    int index = 0;

    for (int i = 1; i < n; i++) {

        /* Overlapping intervals */
        if (arr[i].start <= arr[index].end) {
            if (arr[i].end > arr[index].end)
                arr[index].end = arr[i].end;
        }

        /* Non-overlapping interval */
        else {
            index++;
            arr[index] = arr[i];
        }
    }

    /* Print merged intervals */
    for (int i = 0; i <= index; i++) {
        printf("[%d, %d]", arr[i].start, arr[i].end);

        if (i < index)
            printf(" ");
    }

    printf("\n");
}

int main() {
    int n;

    scanf("%d", &n);

    Interval *arr = malloc(n * sizeof(Interval));

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    mergeIntervals(arr, n);

    free(arr);

    return 0;
}
