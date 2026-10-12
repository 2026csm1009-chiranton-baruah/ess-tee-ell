
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10000

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

typedef struct {
    Node *node;
    int hd;
} QueueItem;

Node *newNode(int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->data = value;
    node->left = node->right = NULL;
    return node;
}

Node *insert(Node *root, int value) {
    if (root == NULL)
        return newNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

void topView(Node *root) {
    if (root == NULL)
        return;

    QueueItem queue[MAX_NODES];
    int values[MAX_NODES];
    int seen[MAX_NODES] = {0};

    int front = 0, rear = 0;
    int offset = MAX_NODES / 2;

    queue[rear++] = (QueueItem){root, 0};

    int minHD = 0, maxHD = 0;

    while (front < rear) {
        QueueItem item = queue[front++];
        Node *cur = item.node;
        int hd = item.hd;
        int index = hd + offset;

        if (index < 0 || index >= MAX_NODES) {
            fprintf(stderr, "Horizontal distance out of range.\n");
            exit(EXIT_FAILURE);
        }

        if (!seen[index]) {
            seen[index] = 1;
            values[index] = cur->data;
        }

        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;

        if (cur->left != NULL) {
            if (rear == MAX_NODES) {
                fprintf(stderr, "Tree is too large.\n");
                exit(EXIT_FAILURE);
            }
            queue[rear++] = (QueueItem){cur->left, hd - 1};
        }

        if (cur->right != NULL) {
            if (rear == MAX_NODES) {
                fprintf(stderr, "Tree is too large.\n");
                exit(EXIT_FAILURE);
            }
            queue[rear++] = (QueueItem){cur->right, hd + 1};
        }
    }

    printf("Top view: ");
    for (int hd = minHD; hd <= maxHD; hd++) {
        int index = hd + offset;
        if (seen[index])
            printf("%d ", values[index]);
    }
    printf("\n");
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *root = NULL;
    int n, value;

    printf("Enter number of nodes: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter BST values: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) {
            printf("Invalid input.\n");
            freeTree(root);
            return 1;
        }
        root = insert(root, value);
    }

    topView(root);
    freeTree(root);
    return 0;
}
