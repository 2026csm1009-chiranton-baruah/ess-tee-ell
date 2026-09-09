#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   BINARY HEAP IMPLEMENTATION
   Supports:
   - Min Heap
   - Max Heap
   - Insert
   - Extract Min/Max
   - Delete at index
   - Heapify Up
   - Heapify Down
   - Build Heap
   - Search
   - Peek
   - Display
   - Resize
   ========================================================= */

/* ---------------------------------------------------------
   Heap Structure
   --------------------------------------------------------- */

typedef struct {
    int *arr;
    int size;
    int capacity;
    int isMinHeap;     /* 1 = Min Heap, 0 = Max Heap */
} Heap;


/* ---------------------------------------------------------
   Utility Functions
   --------------------------------------------------------- */

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/* ---------------------------------------------------------
   Create Heap
   --------------------------------------------------------- */

Heap *createHeap(int capacity, int isMinHeap)
{
    if (capacity <= 0)
        capacity = 10;

    Heap *heap = (Heap *)malloc(sizeof(Heap));

    if (heap == NULL)
        return NULL;

    heap->arr = (int *)malloc(capacity * sizeof(int));

    if (heap->arr == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    heap->isMinHeap = isMinHeap;

    return heap;
}


/* ---------------------------------------------------------
   Destroy Heap
   --------------------------------------------------------- */

void destroyHeap(Heap *heap)
{
    if (heap == NULL)
        return;

    free(heap->arr);
    free(heap);
}


/* ---------------------------------------------------------
   Comparison
   Returns 1 if a should be above b
   --------------------------------------------------------- */

int higherPriority(Heap *heap, int a, int b)
{
    if (heap->isMinHeap)
        return a < b;
    else
        return a > b;
}


/* ---------------------------------------------------------
   Resize Heap
   --------------------------------------------------------- */

int resizeHeap(Heap *heap)
{
    int newCapacity = heap->capacity * 2;

    int *newArr = (int *)realloc(
        heap->arr,
        newCapacity * sizeof(int)
    );

    if (newArr == NULL)
        return 0;

    heap->arr = newArr;
    heap->capacity = newCapacity;

    return 1;
}


/* ---------------------------------------------------------
   Heapify Up
   Used after insertion
   --------------------------------------------------------- */

void heapifyUp(Heap *heap, int index)
{
    if (index <= 0)
        return;

    int parent = (index - 1) / 2;

    if (higherPriority(heap,
                       heap->arr[index],
                       heap->arr[parent])) {

        swap(&heap->arr[index],
             &heap->arr[parent]);

        heapifyUp(heap, parent);
    }
}


/* ---------------------------------------------------------
   Heapify Down
   Used after deletion/extraction
   --------------------------------------------------------- */

void heapifyDown(Heap *heap, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int best = index;

    if (left < heap->size &&
        higherPriority(heap,
                       heap->arr[left],
                       heap->arr[best])) {

        best = left;
    }

    if (right < heap->size &&
        higherPriority(heap,
                       heap->arr[right],
                       heap->arr[best])) {

        best = right;
    }

    if (best != index) {

        swap(&heap->arr[index],
             &heap->arr[best]);

        heapifyDown(heap, best);
    }
}


/* ---------------------------------------------------------
   Insert
   --------------------------------------------------------- */

int insertHeap(Heap *heap, int value)
{
    if (heap == NULL)
        return 0;

    /* Resize if full */
    if (heap->size == heap->capacity) {
        if (!resizeHeap(heap))
            return 0;
    }

    int index = heap->size;

    heap->arr[index] = value;
    heap->size++;

    heapifyUp(heap, index);

    return 1;
}


/* ---------------------------------------------------------
   Peek
   Returns root without removing it
   --------------------------------------------------------- */

int peekHeap(Heap *heap, int *value)
{
    if (heap == NULL || heap->size == 0)
        return 0;

    *value = heap->arr[0];

    return 1;
}


/* ---------------------------------------------------------
   Extract Root
   Removes minimum from Min Heap
   or maximum from Max Heap
   --------------------------------------------------------- */

int extractRoot(Heap *heap, int *value)
{
    if (heap == NULL || heap->size == 0)
        return 0;

    *value = heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];

    heap->size--;

    if (heap->size > 0)
        heapifyDown(heap, 0);

    return 1;
}


/* ---------------------------------------------------------
   Delete Element at Index
   --------------------------------------------------------- */

int deleteAtIndex(Heap *heap, int index, int *value)
{
    if (heap == NULL ||
        index < 0 ||
        index >= heap->size)
        return 0;

    *value = heap->arr[index];

    /* Replace deleted element with last element */
    heap->arr[index] = heap->arr[heap->size - 1];

    heap->size--;

    if (index < heap->size) {

        /*
           The replacement can need to move either
           upward or downward.
        */

        if (index > 0) {

            int parent = (index - 1) / 2;

            if (higherPriority(heap,
                               heap->arr[index],
                               heap->arr[parent])) {

                heapifyUp(heap, index);
                return 1;
            }
        }

        heapifyDown(heap, index);
    }

    return 1;
}


/* ---------------------------------------------------------
   Search
   Returns index of first occurrence
   Returns -1 if not found
   --------------------------------------------------------- */

int searchHeap(Heap *heap, int value)
{
    if (heap == NULL)
        return -1;

    for (int i = 0; i < heap->size; i++) {

        if (heap->arr[i] == value)
            return i;
    }

    return -1;
}


/* ---------------------------------------------------------
   Build Heap
   Converts an arbitrary array into a heap
   --------------------------------------------------------- */

void buildHeap(Heap *heap)
{
    if (heap == NULL)
        return;

    /*
       Last non-leaf node:

       floor(n / 2) - 1
    */

    for (int i = heap->size / 2 - 1;
         i >= 0;
         i--) {

        heapifyDown(heap, i);
    }
}


/* ---------------------------------------------------------
   Insert an Entire Array
   --------------------------------------------------------- */

int insertArray(Heap *heap, int arr[], int n)
{
    if (heap == NULL || arr == NULL || n < 0)
        return 0;

    for (int i = 0; i < n; i++) {

        if (!insertHeap(heap, arr[i]))
            return 0;
    }

    return 1;
}


/* ---------------------------------------------------------
   Build Heap Directly from Array
   --------------------------------------------------------- */

Heap *createHeapFromArray(int arr[],
                          int n,
                          int isMinHeap)
{
    if (arr == NULL || n < 0)
        return NULL;

    int capacity = (n > 0) ? n : 10;

    Heap *heap = createHeap(capacity, isMinHeap);

    if (heap == NULL)
        return NULL;

    for (int i = 0; i < n; i++)
        heap->arr[i] = arr[i];

    heap->size = n;

    /* O(n) heap construction */
    buildHeap(heap);

    return heap;
}


/* ---------------------------------------------------------
   Display Heap
   --------------------------------------------------------- */

void displayHeap(Heap *heap)
{
    if (heap == NULL) {
        printf("Heap does not exist.\n");
        return;
    }

    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Heap: ");

    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);

    printf("\n");
}


/* ---------------------------------------------------------
   Display Heap Level by Level
   --------------------------------------------------------- */

void displayLevels(Heap *heap)
{
    if (heap == NULL || heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    int level = 0;
    int count = 0;
    int elementsAtLevel = 1;

    printf("Heap levels:\n");

    for (int i = 0; i < heap->size; i++) {

        printf("%d ", heap->arr[i]);

        count++;

        if (count == elementsAtLevel) {

            printf("\n");

            level++;
            count = 0;
            elementsAtLevel *= 2;
        }
    }

    if (count != 0)
        printf("\n");
}


/* ---------------------------------------------------------
   Get Size
   --------------------------------------------------------- */

int heapSize(Heap *heap)
{
    if (heap == NULL)
        return 0;

    return heap->size;
}


/* ---------------------------------------------------------
   Check Empty
   --------------------------------------------------------- */

int isEmpty(Heap *heap)
{
    return heap == NULL || heap->size == 0;
}


/* ---------------------------------------------------------
   Check Full
   --------------------------------------------------------- */

int isFull(Heap *heap)
{
    return heap != NULL &&
           heap->size == heap->capacity;
}


/* ---------------------------------------------------------
   Clear Heap
   --------------------------------------------------------- */

void clearHeap(Heap *heap)
{
    if (heap != NULL)
        heap->size = 0;
}


/* ---------------------------------------------------------
   Heap Sort
   --------------------------------------------------------- */

/*
   This function sorts an array in ascending order.

   It uses a separate Max Heap regardless of the
   Heap object's type.
*/

void maxHeapify(int arr[], int n, int index)
{
    int largest = index;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != index) {

        swap(&arr[index], &arr[largest]);

        maxHeapify(arr, n, largest);
    }
}


void heapSort(int arr[], int n)
{
    if (arr == NULL || n <= 1)
        return;

    /* Build Max Heap */

    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    /* Extract maximum repeatedly */

    for (int i = n - 1; i > 0; i--) {

        swap(&arr[0], &arr[i]);

        maxHeapify(arr, i, 0);
    }
}


/* ---------------------------------------------------------
   Print Array
   --------------------------------------------------------- */

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}


/* =========================================================
   MAIN - DEMONSTRATION
   ========================================================= */

int main()
{
    int value;

    /* =========================================
       MAX HEAP
       ========================================= */

    printf("========== MAX HEAP ==========\n");

    Heap *maxHeap = createHeap(5, 0);

    if (maxHeap == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    insertHeap(maxHeap, 40);
    insertHeap(maxHeap, 20);
    insertHeap(maxHeap, 60);
    insertHeap(maxHeap, 10);
    insertHeap(maxHeap, 50);
    insertHeap(maxHeap, 70);

    displayHeap(maxHeap);
    displayLevels(maxHeap);

    if (peekHeap(maxHeap, &value))
        printf("Maximum: %d\n", value);

    if (extractRoot(maxHeap, &value))
        printf("Extracted: %d\n", value);

    displayHeap(maxHeap);

    int index = searchHeap(maxHeap, 20);

    if (index != -1) {

        deleteAtIndex(maxHeap, index, &value);

        printf("Deleted: %d\n", value);
    }

    displayHeap(maxHeap);

    destroyHeap(maxHeap);


    /* =========================================
       MIN HEAP
       ========================================= */

    printf("\n========== MIN HEAP ==========\n");

    Heap *minHeap = createHeap(5, 1);

    if (minHeap == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    insertHeap(minHeap, 40);
    insertHeap(minHeap, 20);
    insertHeap(minHeap, 60);
    insertHeap(minHeap, 10);
    insertHeap(minHeap, 50);
    insertHeap(minHeap, 70);

    displayHeap(minHeap);
    displayLevels(minHeap);

    if (peekHeap(minHeap, &value))
        printf("Minimum: %d\n", value);

    if (extractRoot(minHeap, &value))
        printf("Extracted: %d\n", value);

    displayHeap(minHeap);

    destroyHeap(minHeap);


    /* =========================================
       BUILD HEAP FROM ARRAY
       ========================================= */

    printf("\n========== BUILD HEAP ==========\n");

    int arr[] = {
        30, 10, 50, 20, 60,
        40, 80, 70, 90
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    Heap *heap = createHeapFromArray(arr, n, 0);

    if (heap != NULL) {

        displayHeap(heap);
        displayLevels(heap);

        destroyHeap(heap);
    }


    /* =========================================
       HEAP SORT
       ========================================= */

    printf("\n========== HEAP SORT ==========\n");

    int data[] = {
        40, 10, 70, 20, 90,
        30, 50, 60, 80
    };

    int size = sizeof(data) / sizeof(data[0]);

    printf("Before sorting: ");
    printArray(data, size);

    heapSort(data, size);

    printf("After sorting:  ");
    printArray(data, size);


    return 0;
}
