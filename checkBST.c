#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* -------------------- BST Node -------------------- */

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;


/* -------------------- Create Node -------------------- */

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/* -------------------- Insert into BST -------------------- */

Node* insert(Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);

    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}


/* -------------------- Check BST -------------------- */

/*
    Every node must satisfy:

        min < node->data < max

    Initially:

        INT_MIN < root->data < INT_MAX

    For the left subtree:

        min < node->data < root->data

    For the right subtree:

        root->data < node->data < max
*/

int checkBSTHelper(Node *root, long long min, long long max) {

    if (root == NULL)
        return 1;

    if (root->data <= min || root->data >= max)
        return 0;

    return checkBSTHelper(root->left, min, root->data) &&
           checkBSTHelper(root->right, root->data, max);
}


int checkBST(Node *root) {
    return checkBSTHelper(root, LLONG_MIN, LLONG_MAX);
}


/* -------------------- Free Tree -------------------- */

void freeTree(Node *root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


/* -------------------- Main -------------------- */

int main() {

    int n;
    Node *root = NULL;

    /*
        Input format used by this standalone program:

        First line:
        n

        Second line:
        n node values

        Example:
        7
        4 2 6 1 3 5 7
    */

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);

        root = insert(root, value);
    }

    if (checkBST(root))
        printf("Yes\n");
    else
        printf("No\n");

    freeTree(root);

    return 0;
}
