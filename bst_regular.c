#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   NODE
   ========================================================= */

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;


/* =========================================================
   CREATE NODE
   ========================================================= */

Node* createNode(int data) {

    Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/* =========================================================
   INSERT
   ========================================================= */

Node* insert(Node *root, int data) {

    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);

    else if (data > root->data)
        root->right = insert(root->right, data);

    /* Duplicate values ignored */

    return root;
}


/* =========================================================
   SEARCH
   ========================================================= */

Node* search(Node *root, int key) {

    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}


/* =========================================================
   SEARCH - ITERATIVE
   ========================================================= */

Node* searchIterative(Node *root, int key) {

    while (root != NULL) {

        if (root->data == key)
            return root;

        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}


/* =========================================================
   INORDER
   ========================================================= */

void inorder(Node *root) {

    if (root == NULL)
        return;

    inorder(root->left);

    printf("%d ", root->data);

    inorder(root->right);
}


/* =========================================================
   PREORDER
   ========================================================= */

void preorder(Node *root) {

    if (root == NULL)
        return;

    printf("%d ", root->data);

    preorder(root->left);

    preorder(root->right);
}


/* =========================================================
   POSTORDER
   ========================================================= */

void postorder(Node *root) {

    if (root == NULL)
        return;

    postorder(root->left);

    postorder(root->right);

    printf("%d ", root->data);
}


/* =========================================================
   LEVEL ORDER
   ========================================================= */

void levelOrder(Node *root) {

    if (root == NULL)
        return;

    /*
       Simple array-based queue.
       Increase SIZE if necessary.
    */
    #define SIZE 1000

    Node *queue[SIZE];

    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        Node *current = queue[front++];

        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }

    #undef SIZE
}


/* =========================================================
   MINIMUM NODE
   ========================================================= */

Node* findMin(Node *root) {

    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}


/* =========================================================
   MAXIMUM NODE
   ========================================================= */

Node* findMax(Node *root) {

    if (root == NULL)
        return NULL;

    while (root->right != NULL)
        root = root->right;

    return root;
}


/* =========================================================
   DELETE
   ========================================================= */

Node* deleteNode(Node *root, int key) {

    if (root == NULL)
        return NULL;

    /*
       Search for node
    */

    if (key < root->data) {

        root->left = deleteNode(root->left, key);
    }

    else if (key > root->data) {

        root->right = deleteNode(root->right, key);
    }

    else {

        /*
           CASE 1:
           No child
        */

        if (root->left == NULL && root->right == NULL) {

            free(root);
            return NULL;
        }

        /*
           CASE 2:
           Only right child
        */

        else if (root->left == NULL) {

            Node *temp = root->right;

            free(root);

            return temp;
        }

        /*
           CASE 3:
           Only left child
        */

        else if (root->right == NULL) {

            Node *temp = root->left;

            free(root);

            return temp;
        }

        /*
           CASE 4:
           Two children

           Replace with inorder successor
        */

        else {

            Node *successor = findMin(root->right);

            root->data = successor->data;

            root->right =
                deleteNode(root->right, successor->data);
        }
    }

    return root;
}


/* =========================================================
   HEIGHT
   Convention:
   Empty tree = 0
   Leaf = 1
   ========================================================= */

int height(Node *root) {

    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 +
           (leftHeight > rightHeight ?
            leftHeight : rightHeight);
}


/* =========================================================
   HEIGHT IN EDGES
   Empty tree = -1
   Leaf = 0
   ========================================================= */

int heightEdges(Node *root) {

    if (root == NULL)
        return -1;

    int leftHeight = heightEdges(root->left);
    int rightHeight = heightEdges(root->right);

    return 1 +
           (leftHeight > rightHeight ?
            leftHeight : rightHeight);
}


/* =========================================================
   COUNT NODES
   ========================================================= */

int countNodes(Node *root) {

    if (root == NULL)
        return 0;

    return 1 +
           countNodes(root->left) +
           countNodes(root->right);
}


/* =========================================================
   COUNT LEAF NODES
   ========================================================= */

int countLeaves(Node *root) {

    if (root == NULL)
        return 0;

    if (root->left == NULL &&
        root->right == NULL)
        return 1;

    return countLeaves(root->left) +
           countLeaves(root->right);
}


/* =========================================================
   COUNT INTERNAL NODES
   ========================================================= */

int countInternal(Node *root) {

    if (root == NULL)
        return 0;

    if (root->left == NULL &&
        root->right == NULL)
        return 0;

    return 1 +
           countInternal(root->left) +
           countInternal(root->right);
}


/* =========================================================
   SUM OF ALL NODES
   ========================================================= */

int sumNodes(Node *root) {

    if (root == NULL)
        return 0;

    return root->data +
           sumNodes(root->left) +
           sumNodes(root->right);
}


/* =========================================================
   DEPTH OF A KEY
   Root has depth 0
   ========================================================= */

int depth(Node *root, int key) {

    int d = 0;

    while (root != NULL) {

        if (root->data == key)
            return d;

        if (key < root->data)
            root = root->left;
        else
            root = root->right;

        d++;
    }

    return -1;
}


/* =========================================================
   SUCCESSOR
   Smallest value greater than key
   ========================================================= */

Node* successor(Node *root, int key) {

    Node *succ = NULL;

    while (root != NULL) {

        if (key < root->data) {

            succ = root;
            root = root->left;
        }

        else if (key > root->data) {

            root = root->right;
        }

        else {

            /*
               If right subtree exists,
               successor is its minimum.
            */

            if (root->right != NULL)
                succ = findMin(root->right);

            break;
        }
    }

    return succ;
}


/* =========================================================
   PREDECESSOR
   Largest value smaller than key
   ========================================================= */

Node* predecessor(Node *root, int key) {

    Node *pred = NULL;

    while (root != NULL) {

        if (key > root->data) {

            pred = root;
            root = root->right;
        }

        else if (key < root->data) {

            root = root->left;
        }

        else {

            /*
               If left subtree exists,
               predecessor is its maximum.
            */

            if (root->left != NULL)
                pred = findMax(root->left);

            break;
        }
    }

    return pred;
}


/* =========================================================
   LOWEST COMMON ANCESTOR
   For a BST
   ========================================================= */

Node* LCA(Node *root, int a, int b) {

    while (root != NULL) {

        if (a < root->data &&
            b < root->data) {

            root = root->left;
        }

        else if (a > root->data &&
                 b > root->data) {

            root = root->right;
        }

        else {

            /*
               They lie on different sides,
               or one is the root.
            */

            return root;
        }
    }

    return NULL;
}


/* =========================================================
   CHECK BST
   Using MIN/MAX RANGE
   ========================================================= */

int isBSTUtil(Node *root, long long min,
              long long max) {

    if (root == NULL)
        return 1;

    if (root->data <= min ||
        root->data >= max)
        return 0;

    return isBSTUtil(root->left,
                     min,
                     root->data)
        &&
           isBSTUtil(root->right,
                     root->data,
                     max);
}


int isBST(Node *root) {

    return isBSTUtil(root,
                     -9223372036854775807LL,
                     9223372036854775807LL);
}


/* =========================================================
   DIAMETER
   Diameter measured in NUMBER OF NODES
   ========================================================= */

int diameterUtil(Node *root, int *diameter) {

    if (root == NULL)
        return 0;

    int leftHeight =
        diameterUtil(root->left, diameter);

    int rightHeight =
        diameterUtil(root->right, diameter);

    /*
       Path passing through root
    */

    int currentDiameter =
        leftHeight + rightHeight + 1;

    if (currentDiameter > *diameter)
        *diameter = currentDiameter;

    return 1 +
           (leftHeight > rightHeight ?
            leftHeight : rightHeight);
}


int diameter(Node *root) {

    int d = 0;

    diameterUtil(root, &d);

    return d;
}


/* =========================================================
   MIRROR TREE
   Converts left <-> right
   Note: The resulting tree is generally NOT a BST.
   ========================================================= */

void mirror(Node *root) {

    if (root == NULL)
        return;

    Node *temp = root->left;

    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}


/* =========================================================
   FIND Kth SMALLEST
   k = 1 means smallest
   ========================================================= */

Node* kthSmallestUtil(Node *root, int *k) {

    if (root == NULL)
        return NULL;

    Node *result =
        kthSmallestUtil(root->left, k);

    if (result != NULL)
        return result;

    (*k)--;

    if (*k == 0)
        return root;

    return kthSmallestUtil(root->right, k);
}


Node* kthSmallest(Node *root, int k) {

    if (k <= 0)
        return NULL;

    return kthSmallestUtil(root, &k);
}


/* =========================================================
   RANGE SEARCH
   Prints values in [low, high]
   ========================================================= */

void rangeSearch(Node *root, int low, int high) {

    if (root == NULL)
        return;

    if (root->data > low)
        rangeSearch(root->left, low, high);

    if (root->data >= low &&
        root->data <= high)
        printf("%d ", root->data);

    if (root->data < high)
        rangeSearch(root->right, low, high);
}


/* =========================================================
   PRINT ROOT-TO-NODE PATH
   ========================================================= */

int printPath(Node *root, int key) {

    if (root == NULL)
        return 0;

    printf("%d ", root->data);

    if (root->data == key)
        return 1;

    if (key < root->data)
        return printPath(root->left, key);

    return printPath(root->right, key);
}


/* =========================================================
   BUILD BST FROM ARRAY
   ========================================================= */

Node* buildBST(int arr[], int n) {

    Node *root = NULL;

    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    return root;
}


/* =========================================================
   FREE TREE
   ========================================================= */

void freeTree(Node *root) {

    if (root == NULL)
        return;

    /*
       Postorder deletion:
       children first, then parent.
    */

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


/* =========================================================
   MAIN
   ========================================================= */

int main() {

    int arr[] = {
        50, 30, 70, 20, 40,
        60, 80, 10, 25, 35,
        45, 55, 65, 75, 90
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    /* =========================
       BUILD BST
       ========================= */

    Node *root = buildBST(arr, n);


    /* =========================
       TRAVERSALS
       ========================= */

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Level order: ");
    levelOrder(root);
    printf("\n");


    /* =========================
       SEARCH
       ========================= */

    int key = 40;

    if (search(root, key) != NULL)
        printf("%d found\n", key);
    else
        printf("%d not found\n", key);


    /* =========================
       MIN / MAX
       ========================= */

    Node *minNode = findMin(root);
    Node *maxNode = findMax(root);

    printf("Minimum = %d\n", minNode->data);
    printf("Maximum = %d\n", maxNode->data);


    /* =========================
       HEIGHT
       ========================= */

    printf("Height (nodes) = %d\n",
           height(root));

    printf("Height (edges) = %d\n",
           heightEdges(root));


    /* =========================
       COUNTS
       ========================= */

    printf("Total nodes = %d\n",
           countNodes(root));

    printf("Leaf nodes = %d\n",
           countLeaves(root));

    printf("Internal nodes = %d\n",
           countInternal(root));

    printf("Sum = %d\n",
           sumNodes(root));


    /* =========================
       DEPTH
       ========================= */

    printf("Depth of %d = %d\n",
           key,
           depth(root, key));


    /* =========================
       PREDECESSOR
       ========================= */

    Node *pred = predecessor(root, key);

    if (pred != NULL)
        printf("Predecessor of %d = %d\n",
               key, pred->data);


    /* =========================
       SUCCESSOR
       ========================= */

    Node *succ = successor(root, key);

    if (succ != NULL)
        printf("Successor of %d = %d\n",
               key, succ->data);


    /* =========================
       LCA
       ========================= */

    Node *lca = LCA(root, 35, 45);

    if (lca != NULL)
        printf("LCA of 35 and 45 = %d\n",
               lca->data);


    /* =========================
       DIAMETER
       ========================= */

    printf("Diameter (nodes) = %d\n",
           diameter(root));


    /* =========================
       Kth SMALLEST
       ========================= */

    Node *kth = kthSmallest(root, 5);

    if (kth != NULL)
        printf("5th smallest = %d\n",
               kth->data);


    /* =========================
       RANGE SEARCH
       ========================= */

    printf("Values between 30 and 65: ");

    rangeSearch(root, 30, 65);

    printf("\n");


    /* =========================
       ROOT TO NODE PATH
       ========================= */

    printf("Path to 45: ");

    if (!printPath(root, 45))
        printf("Not found");

    printf("\n");


    /* =========================
       CHECK BST
       ========================= */

    if (isBST(root))
        printf("Tree is a BST\n");
    else
        printf("Tree is NOT a BST\n");


    /* =========================
       DELETE
       ========================= */

    root = deleteNode(root, 70);

    printf("After deleting 70: ");

    inorder(root);

    printf("\n");


    /* =========================
       FREE MEMORY
       ========================= */

    freeTree(root);

    root = NULL;

    return 0;
}
