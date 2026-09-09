#include <stdio.h>
#include <stdlib.h>

/* -------------------- Node Structure -------------------- */

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;


/* -------------------- Queue Structure -------------------- */

typedef struct QueueNode {
    Node *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;


/* -------------------- Create Tree Node -------------------- */

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/* -------------------- Queue Functions -------------------- */

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, Node *treeNode) {
    QueueNode *newNode =
        (QueueNode *)malloc(sizeof(QueueNode));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    newNode->treeNode = treeNode;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Node *dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }

    QueueNode *temp = q->front;
    Node *treeNode = temp->treeNode;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);

    return treeNode;
}

int height(Node *root) {

    if (root == NULL) {
        return -1;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int diameterHelper(Node *root, int *diameter) {

    if (root == NULL) {
        return -1;
    }

    int leftHeight = diameterHelper(root->left, diameter);
    int rightHeight = diameterHelper(root->right, diameter);

    int currentDiameter = leftHeight + rightHeight + 2;

    if (currentDiameter > *diameter) {
        *diameter = currentDiameter;
    }

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}


int diameter(Node *root) {

    int diameterValue = 0;

    diameterHelper(root, &diameterValue);

    return diameterValue;
}

/* -------------------- Construct Tree -------------------- */

/*
    Input format:

    n
    level-order elements

    Use -1 to represent NULL.

    Example:

    7
    1 2 3 4 5 -1 7

    Tree:

            1
           / \
          2   3
         / \   \
        4   5   7
*/

Node *buildTree(int arr[], int n) {

    if (n == 0 || arr[0] == -1) {
        return NULL;
    }

    Node *root = createNode(arr[0]);

    Queue q;
    initQueue(&q);

    enqueue(&q, root);

    int i = 1;

    while (i < n && !isQueueEmpty(&q)) {

        Node *current = dequeue(&q);

        /* Left child */
        if (i < n && arr[i] != -1) {
            current->left = createNode(arr[i]);
            enqueue(&q, current->left);
        }

        i++;

        /* Right child */
        if (i < n && arr[i] != -1) {
            current->right = createNode(arr[i]);
            enqueue(&q, current->right);
        }

        i++;
    }

    return root;
}


/* -------------------- Recursive Traversals -------------------- */

/* Inorder: Left -> Root -> Right */

void inorder(Node *root) {

    if (root == NULL) {
        return;
    }

    inorder(root->left);

    printf("%d ", root->data);

    inorder(root->right);
}


/* Preorder: Root -> Left -> Right */

void preorder(Node *root) {

    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);

    preorder(root->left);

    preorder(root->right);
}


/* Postorder: Left -> Right -> Root */

void postorder(Node *root) {

    if (root == NULL) {
        return;
    }

    postorder(root->left);

    postorder(root->right);

    printf("%d ", root->data);
}


/* -------------------- Level Order Traversal -------------------- */

void levelOrder(Node *root) {

    if (root == NULL) {
        return;
    }

    Queue q;
    initQueue(&q);

    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {

        Node *current = dequeue(&q);

        printf("%d ", current->data);

        if (current->left != NULL) {
            enqueue(&q, current->left);
        }

        if (current->right != NULL) {
            enqueue(&q, current->right);
        }
    }
}


/* -------------------- Free Tree -------------------- */

void freeTree(Node *root) {

    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


/* -------------------- Main Function -------------------- */

int main() {

    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Tree is empty.\n");
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter level-order elements (-1 for NULL):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    /* Construct tree */
    Node *root = buildTree(arr, n);

    /* Traversals */

    printf("\nInorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\nPostorder: ");
    postorder(root);

    printf("\nLevel Order: ");
    levelOrder(root);

    printf("\n");

    printf("\nHeight: %d", height(root));
    printf("\nDiameter: %d", diameter(root));

    /* Free allocated memory */
    freeTree(root);
    free(arr);

    return 0;
}
