#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char data) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int isLeaf(Node *root) {
    return root != NULL &&
           root->left == NULL &&
           root->right == NULL;
}

void decode(Node *root, const char *encoded) {
    Node *current = root;

    for (int i = 0; encoded[i] != '\0'; i++) {

        if (encoded[i] == '0')
            current = current->left;
        else if (encoded[i] == '1')
            current = current->right;

        // Reached a character
        if (isLeaf(current)) {
            printf("%c", current->data);
            current = root;
        }
    }

    printf("\n");
}

int main() {

    /*
             (*)
            /   \
          (*)    A
         /  \
        B    C

        B = 00
        C = 01
        A = 1
    */

    Node *root = createNode('*');

    root->left = createNode('*');
    root->right = createNode('A');

    root->left->left = createNode('B');
    root->left->right = createNode('C');

    char encoded[] = "00011001";

    printf("Decoded string: ");
    decode(root, encoded);

    return 0;
}
