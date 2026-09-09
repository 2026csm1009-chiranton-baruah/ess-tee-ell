#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   RED-BLACK TREE
   ========================================================= */

typedef enum {
    RED,
    BLACK
} Color;


typedef struct Node {
    int data;
    Color color;

    struct Node *left;
    struct Node *right;
    struct Node *parent;

} Node;


/* =========================================================
   GLOBAL SENTINEL NIL NODE
   ========================================================= */

Node *NIL;


/* =========================================================
   INITIALIZE NIL
   ========================================================= */

void initializeNIL() {

    NIL = (Node *)malloc(sizeof(Node));

    if (NIL == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    NIL->color = BLACK;

    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
}


/* =========================================================
   CREATE NODE
   ========================================================= */

Node* createNode(int data) {

    Node *newNode =
        (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = data;

    newNode->color = RED;

    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;

    return newNode;
}


/* =========================================================
   LEFT ROTATION
   ========================================================= */

void leftRotate(Node **root, Node *x) {

    Node *y = x->right;

    /*
        Move y's left subtree
    */

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    /*
        Connect y to x's parent
    */

    y->parent = x->parent;

    if (x->parent == NIL) {

        *root = y;

    }

    else if (x == x->parent->left) {

        x->parent->left = y;

    }

    else {

        x->parent->right = y;
    }

    /*
        Put x below y
    */

    y->left = x;

    x->parent = y;
}


/* =========================================================
   RIGHT ROTATION
   ========================================================= */

void rightRotate(Node **root, Node *y) {

    Node *x = y->left;

    /*
        Move x's right subtree
    */

    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    /*
        Connect x to y's parent
    */

    x->parent = y->parent;

    if (y->parent == NIL) {

        *root = x;

    }

    else if (y == y->parent->left) {

        y->parent->left = x;

    }

    else {

        y->parent->right = x;
    }

    /*
        Put y below x
    */

    x->right = y;

    y->parent = x;
}


/* =========================================================
   INSERT FIX-UP
   ========================================================= */

void insertFixup(Node **root, Node *z) {

    while (z->parent->color == RED) {

        /*
           Parent is left child
        */

        if (z->parent == z->parent->parent->left) {

            Node *y =
                z->parent->parent->right;

            /*
               CASE 1:
               Uncle is RED
            */

            if (y->color == RED) {

                z->parent->color = BLACK;

                y->color = BLACK;

                z->parent->parent->color = RED;

                z = z->parent->parent;
            }

            /*
               Uncle is BLACK
            */

            else {

                /*
                   CASE 2:
                   z is right child
                */

                if (z == z->parent->right) {

                    z = z->parent;

                    leftRotate(root, z);
                }

                /*
                   CASE 3:
                   z is left child
                */

                z->parent->color = BLACK;

                z->parent->parent->color = RED;

                rightRotate(
                    root,
                    z->parent->parent
                );
            }
        }

        /*
           Parent is right child
           (mirror cases)
        */

        else {

            Node *y =
                z->parent->parent->left;

            /*
               CASE 1:
               Uncle is RED
            */

            if (y->color == RED) {

                z->parent->color = BLACK;

                y->color = BLACK;

                z->parent->parent->color = RED;

                z = z->parent->parent;
            }

            else {

                /*
                   CASE 2:
                   z is left child
                */

                if (z == z->parent->left) {

                    z = z->parent;

                    rightRotate(root, z);
                }

                /*
                   CASE 3
                */

                z->parent->color = BLACK;

                z->parent->parent->color = RED;

                leftRotate(
                    root,
                    z->parent->parent
                );
            }
        }
    }

    /*
       Root must always be BLACK
    */

    (*root)->color = BLACK;

    (*root)->parent = NIL;
}


/* =========================================================
   INSERT
   ========================================================= */

void insert(Node **root, int data) {

    Node *z = createNode(data);

    Node *y = NIL;

    Node *x = *root;

    /*
       Normal BST insertion
    */

    while (x != NIL) {

        y = x;

        if (data < x->data)
            x = x->left;

        else if (data > x->data)
            x = x->right;

        else {
            /*
               Duplicate ignored
            */

            free(z);
            return;
        }
    }

    z->parent = y;

    if (y == NIL) {

        *root = z;

    }

    else if (data < y->data) {

        y->left = z;

    }

    else {

        y->right = z;
    }

    /*
       New nodes are initially RED
    */

    z->color = RED;

    insertFixup(root, z);
}


/* =========================================================
   SEARCH
   ========================================================= */

Node* search(Node *root, int key) {

    while (root != NIL) {

        if (root->data == key)
            return root;

        if (key < root->data)
            root = root->left;

        else
            root = root->right;
    }

    return NIL;
}


/* =========================================================
   MINIMUM
   ========================================================= */

Node* minimum(Node *root) {

    if (root == NIL)
        return NIL;

    while (root->left != NIL)
        root = root->left;

    return root;
}


/* =========================================================
   MAXIMUM
   ========================================================= */

Node* maximum(Node *root) {

    if (root == NIL)
        return NIL;

    while (root->right != NIL)
        root = root->right;

    return root;
}


/* =========================================================
   SUCCESSOR
   ========================================================= */

Node* successor(Node *x) {

    if (x == NIL)
        return NIL;

    /*
       Right subtree exists
    */

    if (x->right != NIL)
        return minimum(x->right);

    Node *y = x->parent;

    while (y != NIL &&
           x == y->right) {

        x = y;
        y = y->parent;
    }

    return y;
}


/* =========================================================
   PREDECESSOR
   ========================================================= */

Node* predecessor(Node *x) {

    if (x == NIL)
        return NIL;

    /*
       Left subtree exists
    */

    if (x->left != NIL)
        return maximum(x->left);

    Node *y = x->parent;

    while (y != NIL &&
           x == y->left) {

        x = y;
        y = y->parent;
    }

    return y;
}


/* =========================================================
   TRANSPLANT
   Replace subtree u with subtree v
   ========================================================= */

void transplant(Node **root,
                Node *u,
                Node *v) {

    if (u->parent == NIL) {

        *root = v;

    }

    else if (u == u->parent->left) {

        u->parent->left = v;

    }

    else {

        u->parent->right = v;
    }

    v->parent = u->parent;
}


/* =========================================================
   DELETE FIX-UP
   ========================================================= */

void deleteFixup(Node **root, Node *x) {

    while (x != *root &&
           x->color == BLACK) {

        /*
           x is left child
        */

        if (x == x->parent->left) {

            Node *w = x->parent->right;

            /*
               CASE 1:
               Sibling is RED
            */

            if (w->color == RED) {

                w->color = BLACK;

                x->parent->color = RED;

                leftRotate(root, x->parent);

                w = x->parent->right;
            }

            /*
               CASE 2:
               Sibling's children are BLACK
            */

            if (w->left->color == BLACK &&
                w->right->color == BLACK) {

                w->color = RED;

                x = x->parent;
            }

            else {

                /*
                   CASE 3:
                   Far child is BLACK
                */

                if (w->right->color == BLACK) {

                    w->left->color = BLACK;

                    w->color = RED;

                    rightRotate(root, w);

                    w = x->parent->right;
                }

                /*
                   CASE 4
                */

                w->color = x->parent->color;

                x->parent->color = BLACK;

                w->right->color = BLACK;

                leftRotate(root, x->parent);

                x = *root;
            }
        }

        /*
           x is right child
           Mirror cases
        */

        else {

            Node *w = x->parent->left;

            /*
               CASE 1
            */

            if (w->color == RED) {

                w->color = BLACK;

                x->parent->color = RED;

                rightRotate(root, x->parent);

                w = x->parent->left;
            }

            /*
               CASE 2
            */

            if (w->right->color == BLACK &&
                w->left->color == BLACK) {

                w->color = RED;

                x = x->parent;
            }

            else {

                /*
                   CASE 3
                */

                if (w->left->color == BLACK) {

                    w->right->color = BLACK;

                    w->color = RED;

                    leftRotate(root, w);

                    w = x->parent->left;
                }

                /*
                   CASE 4
                */

                w->color = x->parent->color;

                x->parent->color = BLACK;

                w->left->color = BLACK;

                rightRotate(root, x->parent);

                x = *root;
            }
        }
    }

    x->color = BLACK;
}


/* =========================================================
   DELETE
   ========================================================= */

void deleteNode(Node **root, int key) {

    Node *z = search(*root, key);

    if (z == NIL) {
        printf("Key %d not found\n", key);
        return;
    }

    Node *y = z;

    Color originalColor = y->color;

    Node *x;


    /*
       CASE 1:
       No left child
    */

    if (z->left == NIL) {

        x = z->right;

        transplant(root, z, z->right);
    }

    /*
       CASE 2:
       No right child
    */

    else if (z->right == NIL) {

        x = z->left;

        transplant(root, z, z->left);
    }

    /*
       CASE 3:
       Two children
    */

    else {

        /*
           Use inorder successor
        */

        y = minimum(z->right);

        originalColor = y->color;

        x = y->right;

        /*
           Successor is direct child
        */

        if (y->parent == z) {

            x->parent = y;

        }

        else {

            transplant(root, y, y->right);

            y->right = z->right;

            y->right->parent = y;
        }

        transplant(root, z, y);

        y->left = z->left;

        y->left->parent = y;

        y->color = z->color;
    }

    free(z);

    /*
       If a BLACK node was removed,
       fix the tree.
    */

    if (originalColor == BLACK)
        deleteFixup(root, x);
}


/* =========================================================
   INORDER
   ========================================================= */

void inorder(Node *root) {

    if (root == NIL)
        return;

    inorder(root->left);

    printf("%d(%c) ",
           root->data,
           root->color == RED ? 'R' : 'B');

    inorder(root->right);
}


/* =========================================================
   PREORDER
   ========================================================= */

void preorder(Node *root) {

    if (root == NIL)
        return;

    printf("%d(%c) ",
           root->data,
           root->color == RED ? 'R' : 'B');

    preorder(root->left);

    preorder(root->right);
}


/* =========================================================
   POSTORDER
   ========================================================= */

void postorder(Node *root) {

    if (root == NIL)
        return;

    postorder(root->left);

    postorder(root->right);

    printf("%d(%c) ",
           root->data,
           root->color == RED ? 'R' : 'B');
}


/* =========================================================
   LEVEL ORDER
   ========================================================= */

void levelOrder(Node *root) {

    if (root == NIL)
        return;

    Node *queue[1000];

    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        Node *current = queue[front++];

        printf("%d(%c) ",
               current->data,
               current->color == RED ? 'R' : 'B');

        if (current->left != NIL)
            queue[rear++] = current->left;

        if (current->right != NIL)
            queue[rear++] = current->right;
    }
}


/* =========================================================
   HEIGHT
   Number of nodes
   ========================================================= */

int height(Node *root) {

    if (root == NIL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 +
           (leftHeight > rightHeight ?
            leftHeight : rightHeight);
}


/* =========================================================
   COUNT NODES
   ========================================================= */

int countNodes(Node *root) {

    if (root == NIL)
        return 0;

    return 1 +
           countNodes(root->left) +
           countNodes(root->right);
}


/* =========================================================
   COUNT RED NODES
   ========================================================= */

int countRedNodes(Node *root) {

    if (root == NIL)
        return 0;

    return (root->color == RED) +
           countRedNodes(root->left) +
           countRedNodes(root->right);
}


/* =========================================================
   COUNT BLACK NODES
   ========================================================= */

int countBlackNodes(Node *root) {

    if (root == NIL)
        return 0;

    return (root->color == BLACK) +
           countBlackNodes(root->left) +
           countBlackNodes(root->right);
}


/* =========================================================
   BST VALIDATION
   ========================================================= */

int isBSTUtil(Node *root,
              long long min,
              long long max) {

    if (root == NIL)
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

    return isBSTUtil(
        root,
        -9223372036854775807LL,
        9223372036854775807LL
    );
}


/* =========================================================
   CHECK RED-BLACK PROPERTY
   ========================================================= */

/*
   Returns black height if valid.
   Returns -1 if invalid.
*/

int checkRB(Node *root) {

    if (root == NIL)
        return 1;

    /*
       Red node cannot have RED child
    */

    if (root->color == RED) {

        if (root->left->color == RED ||
            root->right->color == RED)
            return -1;
    }

    int leftBH = checkRB(root->left);
    int rightBH = checkRB(root->right);

    if (leftBH == -1 ||
        rightBH == -1)
        return -1;

    /*
       Both paths must have same
       black height.
    */

    if (leftBH != rightBH)
        return -1;

    /*
       Count current BLACK node
    */

    if (root->color == BLACK)
        return leftBH + 1;

    return leftBH;
}


/* =========================================================
   COMPLETE RED-BLACK VALIDATION
   ========================================================= */

int isRedBlackTree(Node *root) {

    if (root == NIL)
        return 1;

    /*
       Property:
       Root must be BLACK.
    */

    if (root->color != BLACK)
        return 0;

    /*
       BST property
    */

    if (!isBST(root))
        return 0;

    /*
       Red-black properties
    */

    return checkRB(root) != -1;
}


/* =========================================================
   FREE TREE
   ========================================================= */

void freeTree(Node *root) {

    if (root == NIL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


/* =========================================================
   MAIN
   ========================================================= */

int main() {

    initializeNIL();

    Node *root = NIL;


    /* =====================================================
       INSERT
       ===================================================== */

    int values[] = {
        50, 30, 70,
        20, 40, 60, 80,
        10, 25, 35, 45,
        55, 65, 75, 90
    };

    int n = sizeof(values) /
            sizeof(values[0]);


    for (int i = 0; i < n; i++)
        insert(&root, values[i]);


    /* =====================================================
       TRAVERSALS
       ===================================================== */

    printf("Inorder:\n");

    inorder(root);

    printf("\n\n");


    printf("Preorder:\n");

    preorder(root);

    printf("\n\n");


    printf("Postorder:\n");

    postorder(root);

    printf("\n\n");


    printf("Level Order:\n");

    levelOrder(root);

    printf("\n\n");


    /* =====================================================
       SEARCH
       ===================================================== */

    int key = 40;

    Node *found = search(root, key);

    if (found != NIL)
        printf("%d found, color = %s\n",
               key,
               found->color == RED ?
               "RED" : "BLACK");

    else
        printf("%d not found\n", key);


    /* =====================================================
       MINIMUM / MAXIMUM
       ===================================================== */

    Node *minNode = minimum(root);
    Node *maxNode = maximum(root);

    printf("Minimum = %d\n",
           minNode->data);

    printf("Maximum = %d\n",
           maxNode->data);


    /* =====================================================
       SUCCESSOR
       ===================================================== */

    Node *succ = successor(found);

    if (succ != NIL)
        printf("Successor of %d = %d\n",
               key,
               succ->data);


    /* =====================================================
       PREDECESSOR
       ===================================================== */

    Node *pred = predecessor(found);

    if (pred != NIL)
        printf("Predecessor of %d = %d\n",
               key,
               pred->data);


    /* =====================================================
       HEIGHT
       ===================================================== */

    printf("Height = %d\n",
           height(root));


    /* =====================================================
       NODE COUNTS
       ===================================================== */

    printf("Total nodes = %d\n",
           countNodes(root));

    printf("Red nodes = %d\n",
           countRedNodes(root));

    printf("Black nodes = %d\n",
           countBlackNodes(root));


    /* =====================================================
       VALIDATION
       ===================================================== */

    if (isBST(root))
        printf("BST property: VALID\n");
    else
        printf("BST property: INVALID\n");


    if (isRedBlackTree(root))
        printf("Red-Black property: VALID\n");
    else
        printf("Red-Black property: INVALID\n");


    /* =====================================================
       DELETE
       ===================================================== */

    printf("\nDeleting 70...\n");

    deleteNode(&root, 70);

    printf("Inorder after deletion:\n");

    inorder(root);

    printf("\n");


    if (isRedBlackTree(root))
        printf("Tree remains a valid Red-Black Tree\n");
    else
        printf("Red-Black Tree property violated!\n");


    /* =====================================================
       DELETE MORE
       ===================================================== */

    printf("\nDeleting 30...\n");

    deleteNode(&root, 30);

    printf("Inorder:\n");

    inorder(root);

    printf("\n");


    printf("\nDeleting 50...\n");

    deleteNode(&root, 50);

    printf("Inorder:\n");

    inorder(root);

    printf("\n");


    /* =====================================================
       FREE MEMORY
       ===================================================== */

    freeTree(root);

    free(NIL);

    return 0;
}
