#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1009

typedef struct Node {
    int key;
    struct Node *next;
} Node;

/* Hash function */
int hash(int key) {
    int h = key % TABLE_SIZE;

    if (h < 0)
        h += TABLE_SIZE;

    return h;
}

/* Check whether key exists in hash table */
int contains(Node *table[], int key) {
    int index = hash(key);

    Node *current = table[index];

    while (current != NULL) {
        if (current->key == key)
            return 1;

        current = current->next;
    }

    return 0;
}

/* Insert key into hash table */
void insert(Node *table[], int key) {
    int index = hash(key);

    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
        exit(1);

    newNode->key = key;
    newNode->next = table[index];

    table[index] = newNode;
}

/* Free hash table */
void freeTable(Node *table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = table[i];

        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    int n;

    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    /* Initialize hash table */
    Node *table[TABLE_SIZE] = {NULL};

    int newSize = 0;

    for (int i = 0; i < n; i++) {

        /*
         * If arr[i] has not appeared before,
         * keep it.
         */
        if (!contains(table, arr[i])) {
            insert(table, arr[i]);

            arr[newSize] = arr[i];
            newSize++;
        }
    }

    /* Print array after removing duplicates */
    for (int i = 0; i < newSize; i++)
        printf("%d ", arr[i]);

    printf("\n");

    freeTable(table);

    return 0;
}
