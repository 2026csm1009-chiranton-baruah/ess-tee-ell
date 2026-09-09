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
    newNode->prev = newNode;
    newNode->next = newNode;

    return newNode;
}

/* Insert at beginning */
void insertBeginning(Node **head, int data) {
    Node *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *last = (*head)->prev;

    newNode->next = *head;
    newNode->prev = last;

    last->next = newNode;
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

    Node *last = (*head)->prev;

    newNode->next = *head;
    newNode->prev = last;

    last->next = newNode;
    (*head)->prev = newNode;
}

/* Insert after a given value */
void insertAfter(Node *head, int key, int data) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = head;

    do {
        if (temp->data == key) {
            Node *newNode = createNode(data);

            newNode->next = temp->next;
            newNode->prev = temp;

            temp->next->prev = newNode;
            temp->next = newNode;

            return;
        }

        temp = temp->next;

    } while (temp != head);

    printf("Element %d not found.\n", key);
}

/* Insert before a given value */
void insertBefore(Node **head, int key, int data) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = *head;

    do {
        if (temp->data == key) {
            Node *newNode = createNode(data);

            newNode->next = temp;
            newNode->prev = temp->prev;

            temp->prev->next = newNode;
            temp->prev = newNode;

            if (temp == *head)
                *head = newNode;

            return;
        }

        temp = temp->next;

    } while (temp != *head);

    printf("Element %d not found.\n", key);
}

/* Delete from beginning */
void deleteBeginning(Node **head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = *head;

    if (temp->next == temp) {
        free(temp);
        *head = NULL;
        return;
    }

    Node *last = temp->prev;
    Node *newHead = temp->next;

    last->next = newHead;
    newHead->prev = last;

    *head = newHead;

    free(temp);
}

/* Delete from end */
void deleteEnd(Node **head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *last = (*head)->prev;

    if (last == *head) {
        free(last);
        *head = NULL;
        return;
    }

    Node *newLast = last->prev;

    newLast->next = *head;
    (*head)->prev = newLast;

    free(last);
}

/* Delete a node containing a given value */
void deleteValue(Node **head, int key) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = *head;

    do {
        if (temp->data == key) {

            if (temp->next == temp) {
                free(temp);
                *head = NULL;
                return;
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            if (temp == *head)
                *head = temp->next;

            free(temp);
            return;
        }

        temp = temp->next;

    } while (temp != *head);

    printf("Element %d not found.\n", key);
}

/* Search for a value */
Node *search(Node *head, int key) {
    if (head == NULL)
        return NULL;

    Node *temp = head;

    do {
        if (temp->data == key)
            return temp;

        temp = temp->next;

    } while (temp != head);

    return NULL;
}

/* Count nodes */
int length(Node *head) {
    if (head == NULL)
        return 0;

    int count = 0;
    Node *temp = head;

    do {
        count++;
        temp = temp->next;
    } while (temp != head);

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

    do {
        printf("%d", temp->data);
        temp = temp->next;

        if (temp != head)
            printf(" <-> ");

    } while (temp != head);

    printf(" -> HEAD\n");
}

/* Display backward */
void displayBackward(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *last = head->prev;
    Node *temp = last;

    printf("Backward: ");

    do {
        printf("%d", temp->data);
        temp = temp->prev;

        if (temp != last)
            printf(" <-> ");

    } while (temp != last);

    printf(" -> LAST\n");
}

/* Reverse the DCLL */
void reverse(Node **head) {
    if (*head == NULL || (*head)->next == *head)
        return;

    Node *current = *head;

    do {
        Node *temp = current->next;

        current->next = current->prev;
        current->prev = temp;

        current = temp;

    } while (current != *head);

    *head = (*head)->next;
}

/* Delete entire list */
void clear(Node **head) {
    if (*head == NULL)
        return;

    Node *current = (*head)->next;

    while (current != *head) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(*head);
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

    printf("\nAfter deletion:\n");
    displayForward(head);
    displayBackward(head);

    reverse(&head);

    printf("\nAfter reversal:\n");
    displayForward(head);
    displayBackward(head);

    clear(&head);

    return 0;
}
