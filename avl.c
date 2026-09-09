#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

/* Create a new node */
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

/* Insert at beginning */
void insertBeginning(Node **head, int data) {
    Node *newNode = createNode(data);

    newNode->next = *head;

    if (*head != NULL)
        (*head)->prev = newNode;

    *head = newNode;
}

/* Insert at end */
void insertEnd(Node **head, int data) {
    Node *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

/* Insert after a given value */
void insertAfter(Node *head, int key, int data) {
    Node *temp = head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("Element %d not found.\n", key);
        return;
    }

    Node *newNode = createNode(data);

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;
}

/* Insert before a given value */
void insertBefore(Node **head, int key, int data) {
    Node *temp = *head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("Element %d not found.\n", key);
        return;
    }

    Node *newNode = createNode(data);

    newNode->next = temp;
    newNode->prev = temp->prev;

    if (temp->prev != NULL)
        temp->prev->next = newNode;
    else
        *head = newNode;

    temp->prev = newNode;
}

/* Delete from beginning */
void deleteBeginning(Node **head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = *head;
    *head = temp->next;

    if (*head != NULL)
        (*head)->prev = NULL;

    free(temp);
}

/* Delete from end */
void deleteEnd(Node **head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    if (temp->prev != NULL)
        temp->prev->next = NULL;
    else
        *head = NULL;

    free(temp);
}

/* Delete a node containing a given value */
void deleteValue(Node **head, int key) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = *head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("Element %d not found.\n", key);
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        *head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
}

/* Search for a value */
Node *search(Node *head, int key) {
    Node *temp = head;

    while (temp != NULL) {
        if (temp->data == key)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

/* Count nodes */
int length(Node *head) {
    int count = 0;
    Node *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

/* Display forward */
void displayForward(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = head;

    printf("Forward: ");

    while (temp != NULL) {
        printf("%d", temp->data);

        if (temp->next != NULL)
            printf(" <-> ");

        temp = temp->next;
    }

    printf("\n");
}

/* Display backward */
void displayBackward(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    printf("Backward: ");

    while (temp != NULL) {
        printf("%d", temp->data);

        if (temp->prev != NULL)
            printf(" <-> ");

        temp = temp->prev;
    }

    printf("\n");
}

/* Reverse the doubly linked list */
void reverse(Node **head) {
    Node *current = *head;
    Node *temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    if (temp != NULL)
        *head = temp->prev;
}

/* Delete the entire list */
void clear(Node **head) {
    Node *temp = *head;

    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
}

/* Main function */
int main(void) {
    Node *head = NULL;

    insertBeginning(&head, 20);
    insertBeginning(&head, 10);
    insertEnd(&head, 30);
    insertEnd(&head, 40);

    insertAfter(head, 20, 25);
    insertBefore(&head, 10, 5);

    displayForward(head);
    displayBackward(head);

    printf("Length: %d\n", length(head));

    if (search(head, 25) != NULL)
        printf("25 found.\n");
    else
        printf("25 not found.\n");

    deleteBeginning(&head);
    deleteEnd(&head);
    deleteValue(&head, 25);

    displayForward(head);
    displayBackward(head);

    reverse(&head);

    printf("After reversal:\n");
    displayForward(head);
    displayBackward(head);

    clear(&head);

    return 0;
}
