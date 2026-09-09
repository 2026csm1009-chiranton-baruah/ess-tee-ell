#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

/* Initialize queue */
void initQueue(Queue *q) {
    q->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));

    if (q->data == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = INITIAL_CAPACITY;
}

/* Resize queue */
void resizeQueue(Queue *q) {
    int newCapacity = q->capacity * 2;

    int *newData = (int *)malloc(
        newCapacity * sizeof(int)
    );

    if (newData == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    /* Copy elements in logical order */
    for (int i = 0; i < q->size; i++) {
        newData[i] =
            q->data[(q->front + i) % q->capacity];
    }

    free(q->data);

    q->data = newData;
    q->capacity = newCapacity;
    q->front = 0;
    q->rear = q->size - 1;
}

/* Enqueue */
void enqueue(Queue *q, int value) {
    if (q->size == q->capacity) {
        resizeQueue(q);
    }

    q->rear =
        (q->rear + 1) % q->capacity;

    q->data[q->rear] = value;
    q->size++;
}

/* Dequeue */
int dequeue(Queue *q) {
    if (q->size == 0) {
        printf("Queue Underflow\n");
        return -1;
    }

    int value = q->data[q->front];

    q->front =
        (q->front + 1) % q->capacity;

    q->size--;

    return value;
}

/* Front element */
int front(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty\n");
        return -1;
    }

    return q->data[q->front];
}

/* Display */
void displayQueue(Queue *q) {
    if (q->size == 0) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    for (int i = 0; i < q->size; i++) {
        printf("%d ",
               q->data[(q->front + i) % q->capacity]);
    }

    printf("\n");
}

/* Free memory */
void destroyQueue(Queue *q) {
    free(q->data);
    q->data = NULL;
}

int main() {
    Queue q;

    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    enqueue(&q, 50);
    enqueue(&q, 60);
    enqueue(&q, 70);
    enqueue(&q, 80);   // May cause resizing

    displayQueue(&q);

    printf("Front: %d\n", front(&q));

    destroyQueue(&q);

    return 0;
}
