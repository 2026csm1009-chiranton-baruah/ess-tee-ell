#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

/* Initialize stack */
void initStack(Stack *s) {
    s->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));

    if (s->data == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    s->top = -1;
    s->capacity = INITIAL_CAPACITY;
}

/* Resize stack */
void resizeStack(Stack *s) {
    s->capacity *= 2;

    s->data = (int *)realloc(
        s->data,
        s->capacity * sizeof(int)
    );

    if (s->data == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

/* Push */
void push(Stack *s, int value) {
    if (s->top == s->capacity - 1) {
        resizeStack(s);
    }

    s->data[++s->top] = value;
}

/* Pop */
int pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }

    return s->data[s->top--];
}

/* Peek */
int peek(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return -1;
    }

    return s->data[s->top];
}

/* Display */
void displayStack(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");

    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }

    printf("\n");
}

/* Free memory */
void destroyStack(Stack *s) {
    free(s->data);
    s->data = NULL;
}

int main() {
    Stack s;

    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);
    push(&s, 50);   // Causes dynamic resizing

    displayStack(&s);

    printf("Popped: %d\n", pop(&s));
    printf("Top: %d\n", peek(&s));

    displayStack(&s);

    destroyStack(&s);

    return 0;
}
