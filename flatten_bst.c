
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

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

void flattenInorder(Node *root, Node **prev, Node **head) {
    if (root == NULL)
        return;

    // Save the original right subtree before changing pointers.
    Node *rightSubtree = root->right;

    flattenInorder(root->left, prev, head);

    if (*prev == NULL) {
        *head = root;
    } else {
        (*prev)->left = NULL;
        (*prev)->right = root;
    }

    root->left = NULL;
    *prev = root;

    flattenInorder(rightSubtree, prev, head);
}

void printFlattened(Node *root) {
    printf("Flattened BST: ");
    while (root != NULL) {
        printf("%d ", root->data);
        root = root->right;
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
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
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

    Node *head = NULL;
    Node *prev = NULL;

    flattenInorder(root, &prev, &head);
    printFlattened(head);

    // The flattened tree has only right pointers.
    while (head != NULL) {
        Node *next = head->right;
        free(head);
        head = next;
    }

    return 0;
}
