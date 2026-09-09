#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* Swap children of nodes at depths that are multiples of k */
void swapAtDepth(Node *root, int depth, int k) {
    if (root == NULL)
        return;

    if (depth % k == 0) {
        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;
    }

    swapAtDepth(root->left, depth + 1, k);
    swapAtDepth(root->right, depth + 1, k);
}

/* Inorder traversal */
void inorder(Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* Free the tree */
void freeTree(Node *root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);

    Node **nodes = (Node**)malloc((n + 1) * sizeof(Node*));

    /* Create all nodes */
    for (int i = 1; i <= n; i++)
        nodes[i] = createNode(i);

    /* Read children */
    for (int i = 1; i <= n; i++) {
        int left, right;
        scanf("%d %d", &left, &right);

        if (left != -1)
            nodes[i]->left = nodes[left];

        if (right != -1)
            nodes[i]->right = nodes[right];
    }

    Node *root = nodes[1];

    int queries;
    scanf("%d", &queries);

    for (int i = 0; i < queries; i++) {
        int k;
        scanf("%d", &k);

        /* Root is at depth 1 */
        swapAtDepth(root, 1, k);

        inorder(root);
        printf("\n");
    }

    freeTree(root);
    free(nodes);

    return 0;
}
