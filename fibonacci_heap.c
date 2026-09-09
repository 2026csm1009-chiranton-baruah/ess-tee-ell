#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ============================================================
   FIBONACCI HEAP NODE
   ============================================================ */

typedef struct FibNode {
    int key;

    int degree;
    int mark;

    struct FibNode *parent;
    struct FibNode *child;

    struct FibNode *left;
    struct FibNode *right;
} FibNode;


/* ============================================================
   FIBONACCI HEAP
   ============================================================ */

typedef struct {
    FibNode *min;
    int n;
} FibHeap;


/* ============================================================
   CREATE NODE
   ============================================================ */

FibNode* createNode(int key)
{
    FibNode *node = (FibNode*)malloc(sizeof(FibNode));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->key = key;
    node->degree = 0;
    node->mark = 0;

    node->parent = NULL;
    node->child = NULL;

    node->left = node;
    node->right = node;

    return node;
}


/* ============================================================
   CREATE HEAP
   ============================================================ */

FibHeap* createHeap()
{
    FibHeap *H = (FibHeap*)malloc(sizeof(FibHeap));

    if (H == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    H->min = NULL;
    H->n = 0;

    return H;
}


/* ============================================================
   INSERT NODE INTO ROOT LIST
   ============================================================ */

void insertIntoRootList(FibHeap *H, FibNode *x)
{
    if (H->min == NULL) {

        x->left = x;
        x->right = x;

        H->min = x;

    } else {

        x->left = H->min;
        x->right = H->min->right;

        H->min->right->left = x;
        H->min->right = x;

        if (x->key < H->min->key)
            H->min = x;
    }
}


/* ============================================================
   INSERT
   ============================================================ */

FibNode* fibInsert(FibHeap *H, int key)
{
    FibNode *x = createNode(key);

    insertIntoRootList(H, x);

    H->n++;

    return x;
}


/* ============================================================
   FIND MINIMUM
   ============================================================ */

FibNode* fibFindMin(FibHeap *H)
{
    return H->min;
}


/* ============================================================
   REMOVE NODE FROM ITS CIRCULAR LIST
   ============================================================ */

void removeFromList(FibNode *x)
{
    x->left->right = x->right;
    x->right->left = x->left;

    x->left = x;
    x->right = x;
}


/* ============================================================
   ADD NODE AS CHILD OF PARENT
   ============================================================ */

void fibLink(FibHeap *H, FibNode *y, FibNode *x)
{
    /*
        Remove y from root list.
    */
    removeFromList(y);

    y->parent = x;
    y->mark = 0;

    /*
        Add y to x's child list.
    */

    if (x->child == NULL) {

        x->child = y;

        y->left = y;
        y->right = y;

    } else {

        y->left = x->child;
        y->right = x->child->right;

        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
}


/* ============================================================
   CONSOLIDATE
   ============================================================ */

void consolidate(FibHeap *H)
{
    /*
        Maximum possible degree is O(log n).

        We allocate a reasonably large array dynamically.
    */

    int maxDegree = 0;
    int temp = H->n;

    while (temp > 0) {
        maxDegree++;
        temp >>= 1;
    }

    maxDegree += 10;

    FibNode **A =
        (FibNode**)calloc(maxDegree, sizeof(FibNode*));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }


    /*
        Save all roots first.

        We cannot safely traverse and modify the root list
        simultaneously.
    */

    int rootCount = 0;

    if (H->min != NULL) {

        FibNode *w = H->min;

        do {
            rootCount++;
            w = w->right;
        } while (w != H->min);
    }

    FibNode **roots =
        (FibNode**)malloc(rootCount * sizeof(FibNode*));

    if (roots == NULL) {
        free(A);
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    if (rootCount > 0) {

        FibNode *w = H->min;

        for (int i = 0; i < rootCount; i++) {
            roots[i] = w;
            w = w->right;
        }
    }


    /*
        Isolate all roots.
    */

    for (int i = 0; i < rootCount; i++) {
        roots[i]->left = roots[i];
        roots[i]->right = roots[i];
    }


    /*
        Consolidate roots having the same degree.
    */

    for (int i = 0; i < rootCount; i++) {

        FibNode *x = roots[i];
        int d = x->degree;

        while (A[d] != NULL) {

            FibNode *y = A[d];

            if (x->key > y->key) {
                FibNode *tempNode = x;
                x = y;
                y = tempNode;
            }

            fibLink(H, y, x);

            A[d] = NULL;
            d++;
        }

        A[d] = x;
    }

    free(roots);


    /*
        Rebuild root list.
    */

    H->min = NULL;

    for (int i = 0; i < maxDegree; i++) {

        if (A[i] != NULL) {

            A[i]->left = A[i];
            A[i]->right = A[i];

            if (H->min == NULL) {

                H->min = A[i];

            } else {

                A[i]->left = H->min;
                A[i]->right = H->min->right;

                H->min->right->left = A[i];
                H->min->right = A[i];

                if (A[i]->key < H->min->key)
                    H->min = A[i];
            }
        }
    }

    free(A);
}


/* ============================================================
   EXTRACT MINIMUM
   ============================================================ */

FibNode* fibExtractMin(FibHeap *H)
{
    FibNode *z = H->min;

    if (z == NULL)
        return NULL;


    /*
        Move all children of z into the root list.
    */

    if (z->child != NULL) {

        FibNode *child = z->child;

        int count = z->degree;

        for (int i = 0; i < count; i++) {

            FibNode *next = child->right;

            /*
                Remove child from child list.
            */

            child->left->right = child->right;
            child->right->left = child->left;

            /*
                Add child to root list.
            */

            child->parent = NULL;
            child->mark = 0;

            child->left = H->min;
            child->right = H->min->right;

            H->min->right->left = child;
            H->min->right = child;

            child = next;
        }

        z->child = NULL;
    }


    /*
        Remove z from root list.
    */

    if (z->right == z) {

        H->min = NULL;

    } else {

        H->min = z->right;

        removeFromList(z);

        consolidate(H);
    }

    H->n--;

    /*
        Make z a standalone node.
    */

    z->left = z;
    z->right = z;

    return z;
}


/* ============================================================
   CUT
   ============================================================ */

void cut(FibHeap *H, FibNode *x, FibNode *y)
{
    /*
        Remove x from y's child list.
    */

    if (x->right == x) {

        y->child = NULL;

    } else {

        if (y->child == x)
            y->child = x->right;

        x->left->right = x->right;
        x->right->left = x->left;
    }

    y->degree--;


    /*
        Add x to root list.
    */

    x->parent = NULL;
    x->mark = 0;

    x->left = H->min;
    x->right = H->min->right;

    H->min->right->left = x;
    H->min->right = x;
}


/* ============================================================
   CASCADING CUT
   ============================================================ */

void cascadingCut(FibHeap *H, FibNode *y)
{
    FibNode *z = y->parent;

    if (z != NULL) {

        if (y->mark == 0) {

            y->mark = 1;

        } else {

            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}


/* ============================================================
   DECREASE KEY
   ============================================================ */

void fibDecreaseKey(FibHeap *H, FibNode *x, int newKey)
{
    if (x == NULL)
        return;

    if (newKey > x->key) {
        printf("New key is greater than current key.\n");
        return;
    }

    x->key = newKey;

    FibNode *y = x->parent;

    /*
        Heap-order violation.
    */

    if (y != NULL && x->key < y->key) {

        cut(H, x, y);
        cascadingCut(H, y);
    }

    if (x->key < H->min->key)
        H->min = x;
}


/* ============================================================
   SEARCH
   ============================================================ */

FibNode* fibSearch(FibNode *root, int key)
{
    if (root == NULL)
        return NULL;

    FibNode *current = root;

    do {

        if (current->key == key)
            return current;

        FibNode *result =
            fibSearch(current->child, key);

        if (result != NULL)
            return result;

        current = current->right;

    } while (current != root);

    return NULL;
}


FibNode* searchHeap(FibHeap *H, int key)
{
    if (H->min == NULL)
        return NULL;

    return fibSearch(H->min, key);
}


/* ============================================================
   DELETE NODE
   ============================================================ */

void fibDelete(FibHeap *H, FibNode *x)
{
    if (x == NULL)
        return;

    /*
        Standard approach:

        decrease key to -infinity,
        then extract minimum.
    */

    fibDecreaseKey(H, x, INT_MIN);

    FibNode *removed = fibExtractMin(H);

    if (removed != NULL)
        free(removed);
}


/* ============================================================
   UNION / MERGE
   ============================================================ */

FibHeap* fibUnion(FibHeap *H1, FibHeap *H2)
{
    FibHeap *H = createHeap();

    H->min = H1->min;

    /*
        Both root lists are circular.

        Concatenate them.
    */

    if (H1->min == NULL) {

        H->min = H2->min;

    } else if (H2->min == NULL) {

        H->min = H1->min;

    } else {

        FibNode *a = H1->min;
        FibNode *b = H2->min;

        FibNode *aRight = a->right;
        FibNode *bLeft = b->left;

        a->right = b;
        b->left = a;

        aRight->left = bLeft;
        bLeft->right = aRight;

        if (b->key < H->min->key)
            H->min = b;
    }

    H->n = H1->n + H2->n;

    return H;
}


/* ============================================================
   DISPLAY ROOT LIST
   ============================================================ */

void displayRootList(FibHeap *H)
{
    if (H->min == NULL) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Root list: ");

    FibNode *current = H->min;

    do {

        printf("%d ", current->key);

        current = current->right;

    } while (current != H->min);

    printf("\n");

    printf("Minimum = %d\n", H->min->key);
}


/* ============================================================
   DISPLAY CHILDREN / TREE
   ============================================================ */

void displayTree(FibNode *node, int depth)
{
    if (node == NULL)
        return;

    FibNode *current = node;

    do {

        for (int i = 0; i < depth; i++)
            printf("    ");

        printf("%d", current->key);

        if (current->mark)
            printf(" [marked]");

        printf("\n");

        if (current->child != NULL)
            displayTree(current->child, depth + 1);

        current = current->right;

    } while (current != node);
}


/* ============================================================
   DISPLAY ENTIRE HEAP
   ============================================================ */

void displayHeap(FibHeap *H)
{
    if (H->min == NULL) {
        printf("Heap is empty.\n");
        return;
    }

    printf("\n========== FIBONACCI HEAP ==========\n");

    printf("Number of nodes: %d\n", H->n);
    printf("Minimum: %d\n\n", H->min->key);

    printf("Trees:\n");

    FibNode *current = H->min;

    do {

        printf("\nTree rooted at %d:\n", current->key);

        displayTree(current, 1);

        current = current->right;

    } while (current != H->min);

    printf("\n====================================\n");
}


/* ============================================================
   FREE TREE
   ============================================================ */

void freeTree(FibNode *node)
{
    if (node == NULL)
        return;

    /*
        First save all children.
    */

    if (node->child != NULL) {

        FibNode *child = node->child;
        FibNode *start = child;

        do {

            FibNode *next = child->right;

            freeTree(child);

            child = next;

        } while (child != start);
    }

    free(node);
}


/*
    The recursive freeTree above cannot safely be used directly
    on circular sibling lists because freed nodes are referenced
    while traversing.

    Therefore use this safer function.
*/

void freeCircularList(FibNode *start)
{
    if (start == NULL)
        return;

    FibNode *current = start;

    while (1) {

        FibNode *next = current->right;

        /*
            Save whether this was the final node.
        */

        int last = (next == start);

        /*
            Free children recursively.
        */

        if (current->child != NULL)
            freeCircularList(current->child);

        free(current);

        if (last)
            break;

        current = next;
    }
}


/* ============================================================
   FREE ENTIRE HEAP
   ============================================================ */

void freeHeap(FibHeap *H)
{
    if (H == NULL)
        return;

    if (H->min != NULL)
        freeCircularList(H->min);

    free(H);
}


/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    FibHeap *H = createHeap();

    int choice;
    int key;
    int newKey;

    while (1) {

        printf("\n\n========== FIBONACCI HEAP ==========\n");

        printf("1.  Insert\n");
        printf("2.  Find Minimum\n");
        printf("3.  Extract Minimum\n");
        printf("4.  Decrease Key\n");
        printf("5.  Delete Node\n");
        printf("6.  Search\n");
        printf("7.  Display Root List\n");
        printf("8.  Display Entire Heap\n");
        printf("9.  Exit\n");

        printf("====================================\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
            {
                printf("Enter key: ");
                scanf("%d", &key);

                fibInsert(H, key);

                printf("Inserted %d.\n", key);

                break;
            }


            case 2:
            {
                FibNode *min = fibFindMin(H);

                if (min == NULL)
                    printf("Heap is empty.\n");
                else
                    printf("Minimum = %d\n", min->key);

                break;
            }


            case 3:
            {
                FibNode *min = fibExtractMin(H);

                if (min == NULL) {

                    printf("Heap is empty.\n");

                } else {

                    printf("Extracted minimum = %d\n",
                           min->key);

                    free(min);
                }

                break;
            }


            case 4:
            {
                printf("Enter current key: ");
                scanf("%d", &key);

                FibNode *node = searchHeap(H, key);

                if (node == NULL) {

                    printf("Node not found.\n");

                } else {

                    printf("Enter new smaller key: ");
                    scanf("%d", &newKey);

                    fibDecreaseKey(H, node, newKey);

                    printf("Key decreased.\n");
                }

                break;
            }


            case 5:
            {
                printf("Enter key to delete: ");
                scanf("%d", &key);

                FibNode *node = searchHeap(H, key);

                if (node == NULL) {

                    printf("Node not found.\n");

                } else {

                    fibDelete(H, node);

                    printf("Node deleted.\n");
                }

                break;
            }


            case 6:
            {
                printf("Enter key to search: ");
                scanf("%d", &key);

                FibNode *node = searchHeap(H, key);

                if (node == NULL)
                    printf("Node not found.\n");
                else
                    printf("Node %d found.\n", node->key);

                break;
            }


            case 7:
            {
                displayRootList(H);
                break;
            }


            case 8:
            {
                displayHeap(H);
                break;
            }


            case 9:
            {
                freeHeap(H);

                printf("Program terminated.\n");

                return 0;
            }


            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
