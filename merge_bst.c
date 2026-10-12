
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

void inorderStore(Node *root, int arr[], int *index) {
    if (root == NULL)
        return;

    inorderStore(root->left, arr, index);
    arr[(*index)++] = root->data;
    inorderStore(root->right, arr, index);
}

Node *buildBalanced(int arr[], int left, int right) {
    if (left > right)
        return NULL;

    int mid = left + (right - left) / 2;
    Node *root = newNode(arr[mid]);

    root->left = buildBalanced(arr, left, mid - 1);
    root->right = buildBalanced(arr, mid + 1, right);

    return root;
}

void inorderPrint(Node *root) {
    if (root == NULL)
        return;

    inorderPrint(root->left);
    printf("%d ", root->data);
    inorderPrint(root->right);
}

void freeTree(Node *root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *root1 = NULL;
    Node *root2 = NULL;
    int n1, n2, value;

    printf("Enter number of nodes in BST 1: ");
    if (scanf("%d", &n1) != 1 || n1 < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter BST 1 values: ");
    for (int i = 0; i < n1; i++) {
        if (scanf("%d", &value) != 1) {
            printf("Invalid input.\n");
            freeTree(root1);
            return 1;
        }
        root1 = insert(root1, value);
    }

    printf("Enter number of nodes in BST 2: ");
    if (scanf("%d", &n2) != 1 || n2 < 0) {
        printf("Invalid input.\n");
        freeTree(root1);
        return 1;
    }

    printf("Enter BST 2 values: ");
    for (int i = 0; i < n2; i++) {
        if (scanf("%d", &value) != 1) {
            printf("Invalid input.\n");
            freeTree(root1);
            freeTree(root2);
            return 1;
        }
        root2 = insert(root2, value);
    }

    int *a = NULL, *b = NULL, *merged = NULL;

    if (n1 > 0)
        a = malloc((size_t)n1 * sizeof(int));
    if (n2 > 0)
        b = malloc((size_t)n2 * sizeof(int));

    if ((n1 > 0 && a == NULL) || (n2 > 0 && b == NULL)) {
        printf("Memory allocation failed.\n");
        free(a);
        free(b);
        freeTree(root1);
        freeTree(root2);
        return 1;
    }

    int i = 0, j = 0;
    inorderStore(root1, a, &i);
    inorderStore(root2, b, &j);

    // Merge sorted arrays, eliminating duplicate values.
    if ((size_t)n1 + (size_t)n2 >
        (size_t)-1 / sizeof(int)) {
        printf("Input is too large.\n");
        free(a);
        free(b);
        freeTree(root1);
        freeTree(root2);
        return 1;
    }

    merged = malloc(((size_t)n1 + (size_t)n2) * sizeof(int));
    if (n1 + (long long)n2 > 0 && merged == NULL) {
        printf("Memory allocation failed.\n");
        free(a);
        free(b);
        freeTree(root1);
        freeTree(root2);
        return 1;
    }

    i = 0;
    j = 0;
    int k = 0;

    while (i < n1 && j < n2) {
        int next;

        if (a[i] < b[j]) {
            next = a[i++];
        } else if (a[i] > b[j]) {
            next = b[j++];
        } else {
            next = a[i++];
            j++;
        }

        if (k == 0 || merged[k - 1] != next)
            merged[k++] = next;
    }

    while (i < n1) {
        int next = a[i++];
        if (k == 0 || merged[k - 1] != next)
            merged[k++] = next;
    }

    while (j < n2) {
        int next = b[j++];
        if (k == 0 || merged[k - 1] != next)
            merged[k++] = next;
    }

    Node *mergedRoot = buildBalanced(merged, 0, k - 1);

    printf("Merged BST inorder: ");
    inorderPrint(mergedRoot);
    printf("\n");

    free(a);
    free(b);
    free(merged);
    freeTree(root1);
    freeTree(root2);
    freeTree(mergedRoot);

    return 0;
}
