```c
#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   UTILITY FUNCTIONS
   ========================================================= */

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* =========================================================
   1. BUBBLE SORT
   ========================================================= */

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
                swapped = 1;
            }
        }

        /* Already sorted */
        if (!swapped)
            break;
    }
}

/* =========================================================
   2. SELECTION SORT
   ========================================================= */

void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[minIndex])
                minIndex = j;
        }

        swap(&a[i], &a[minIndex]);
    }
}

/* =========================================================
   3. INSERTION SORT
   ========================================================= */

void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

/* =========================================================
   4. SHELL SORT
   ========================================================= */

void shellSort(int a[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int key = a[i];
            int j = i;

            while (j >= gap && a[j - gap] > key)
            {
                a[j] = a[j - gap];
                j -= gap;
            }

            a[j] = key;
        }
    }
}

/* =========================================================
   5. MERGE SORT
   ========================================================= */

void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL)
    {
        printf("Memory allocation failed.\n");
        free(L);
        free(R);
        return;
    }

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int a[], int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);

    merge(a, left, mid, right);
}

/* =========================================================
   6. QUICK SORT
   ========================================================= */

int partition(int a[], int low, int high)
{
    int pivot = a[high];

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    if (low >= high)
        return;

    int p = partition(a, low, high);

    quickSort(a, low, p - 1);
    quickSort(a, p + 1, high);
}

/* =========================================================
   7. HEAP SORT
   ========================================================= */

void heapify(int a[], int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    /* Build max heap */
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Extract elements */
    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);

        heapify(a, i, 0);
    }
}

/* =========================================================
   MAIN
   ========================================================= */

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nOriginal array:\n");
    printArray(a, n);

    int choice;

    printf("\n===== SORTING ALGORITHMS =====\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Shell Sort\n");
    printf("5. Merge Sort\n");
    printf("6. Quick Sort\n");
    printf("7. Heap Sort\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            bubbleSort(a, n);
            break;

        case 2:
            selectionSort(a, n);
            break;

        case 3:
            insertionSort(a, n);
            break;

        case 4:
            shellSort(a, n);
            break;

        case 5:
            mergeSort(a, 0, n - 1);
            break;

        case 6:
            quickSort(a, 0, n - 1);
            break;

        case 7:
            heapSort(a, n);
            break;

        default:
            printf("Invalid choice.\n");
            free(a);
            return 0;
    }

    printf("\nSorted array:\n");
    printArray(a, n);

    free(a);

    return 0;
}
```
