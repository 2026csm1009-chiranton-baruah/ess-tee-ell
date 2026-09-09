#include <stdio.h>
#include <stdlib.h>

/* =========================
   NODE STRUCTURE
   ========================= */

typedef struct Node {
    int data;
    struct Node *next;
} Node;


/* =========================
   CREATE NODE
   ========================= */

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}


/* =========================
   DISPLAY / TRAVERSE
   ========================= */

void display(Node *head) {
    Node *temp = head;

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}


/* =========================
   LENGTH
   ========================= */

int length(Node *head) {
    int count = 0;
    Node *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}


/* =========================
   INSERT AT BEGINNING
   ========================= */

void insertBeginning(Node **head, int data) {
    Node *newNode = createNode(data);

    newNode->next = *head;
    *head = newNode;
}


/* =========================
   INSERT AT END
   ========================= */

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
}


/* =========================
   INSERT AT POSITION
   Position is 1-based
   ========================= */

void insertPosition(Node **head, int data, int position) {

    if (position < 1) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        insertBeginning(head, data);
        return;
    }

    Node *temp = *head;

    for (int i = 1; i < position - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid position\n");
        return;
    }

    Node *newNode = createNode(data);

    newNode->next = temp->next;
    temp->next = newNode;
}


/* =========================
   DELETE FROM BEGINNING
   ========================= */

void deleteBeginning(Node **head) {

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *temp = *head;

    *head = (*head)->next;

    free(temp);
}


/* =========================
   DELETE FROM END
   ========================= */

void deleteEnd(Node **head) {

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    /* Only one node */
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node *temp = *head;

    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
}


/* =========================
   DELETE FROM POSITION
   Position is 1-based
   ========================= */

void deletePosition(Node **head, int position) {

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    if (position < 1) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        deleteBeginning(head);
        return;
    }

    Node *temp = *head;

    for (int i = 1; i < position - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position\n");
        return;
    }

    Node *deleteNode = temp->next;

    temp->next = deleteNode->next;

    free(deleteNode);
}


/* =========================
   SEARCH
   Returns position if found
   ========================= */

int search(Node *head, int key) {

    int position = 1;
    Node *temp = head;

    while (temp != NULL) {

        if (temp->data == key)
            return position;

        temp = temp->next;
        position++;
    }

    return -1;
}


/* =========================
   UPDATE
   ========================= */

void update(Node *head, int oldValue, int newValue) {

    Node *temp = head;

    while (temp != NULL) {

        if (temp->data == oldValue) {
            temp->data = newValue;
            return;
        }

        temp = temp->next;
    }

    printf("Element not found\n");
}


/* =========================
   REVERSE
   ========================= */

void reverse(Node **head) {

    Node *prev = NULL;
    Node *curr = *head;
    Node *next = NULL;

    while (curr != NULL) {

        next = curr->next;

        curr->next = prev;

        prev = curr;
        curr = next;
    }

    *head = prev;
}


/* =========================
   REVERSE RECURSIVELY
   ========================= */

Node* reverseRecursive(Node *head) {

    if (head == NULL || head->next == NULL)
        return head;

    Node *newHead = reverseRecursive(head->next);

    head->next->next = head;
    head->next = NULL;

    return newHead;
}


/* =========================
   FIND MIDDLE
   Slow-Fast Pointer
   ========================= */

Node* findMiddle(Node *head) {

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}


/* =========================
   FIND Nth NODE FROM END
   n = 1 means last node
   ========================= */

Node* nthFromEnd(Node *head, int n) {

    if (n <= 0)
        return NULL;

    Node *first = head;
    Node *second = head;

    for (int i = 0; i < n; i++) {

        if (first == NULL)
            return NULL;

        first = first->next;
    }

    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    return second;
}


/* =========================
   DETECT CYCLE
   Floyd's Algorithm
   ========================= */

int hasCycle(Node *head) {

    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {

        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return 1;
    }

    return 0;
}


/* =========================
   REMOVE DUPLICATES
   For UNSORTED list
   ========================= */

void removeDuplicates(Node *head) {

    Node *current = head;

    while (current != NULL) {

        Node *prev = current;
        Node *temp = current->next;

        while (temp != NULL) {

            if (temp->data == current->data) {

                prev->next = temp->next;
                free(temp);

                temp = prev->next;

            } else {

                prev = temp;
                temp = temp->next;
            }
        }

        current = current->next;
    }
}


/* =========================
   SORT LINKED LIST
   Bubble Sort by swapping data
   ========================= */

void sortList(Node *head) {

    if (head == NULL)
        return;

    int swapped;

    Node *ptr;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != NULL) {

            if (ptr->data > ptr->next->data) {

                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;

                swapped = 1;
            }

            ptr = ptr->next;
        }

    } while (swapped);
}


/* =========================
   CONCATENATE TWO LISTS
   ========================= */

void concatenate(Node **head1, Node *head2) {

    if (*head1 == NULL) {
        *head1 = head2;
        return;
    }

    Node *temp = *head1;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = head2;
}


/* =========================
   FREE ENTIRE LIST
   ========================= */

void freeList(Node **head) {

    Node *temp;

    while (*head != NULL) {

        temp = *head;
        *head = (*head)->next;

        free(temp);
    }
}


/* =========================
   MAIN
   ========================= */

int main() {

    Node *head = NULL;

    /* Insert */
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    insertBeginning(&head, 5);

    insertPosition(&head, 15, 3);

    printf("List: ");
    display(head);


    /* Length */
    printf("Length = %d\n", length(head));


    /* Search */
    int pos = search(head, 20);

    if (pos != -1)
        printf("20 found at position %d\n", pos);
    else
        printf("20 not found\n");


    /* Update */
    update(head, 30, 35);

    printf("After update: ");
    display(head);


    /* Delete */
    deleteBeginning(&head);

    printf("After deleting beginning: ");
    display(head);

    deleteEnd(&head);

    printf("After deleting end: ");
    display(head);

    deletePosition(&head, 2);

    printf("After deleting position 2: ");
    display(head);


    /* Add some elements */
    insertEnd(&head, 40);
    insertEnd(&head, 10);
    insertEnd(&head, 25);

    printf("Before sorting: ");
    display(head);


    /* Sort */
    sortList(head);

    printf("After sorting: ");
    display(head);


    /* Middle */
    Node *middle = findMiddle(head);

    if (middle != NULL)
        printf("Middle = %d\n", middle->data);


    /* Nth from end */
    Node *nth = nthFromEnd(head, 2);

    if (nth != NULL)
        printf("2nd node from end = %d\n", nth->data);


    /* Reverse */
    reverse(&head);

    printf("After reverse: ");
    display(head);


    /* Recursive reverse */
    head = reverseRecursive(head);

    printf("After recursive reverse: ");
    display(head);


    /* Remove duplicates */
    removeDuplicates(head);

    printf("After removing duplicates: ");
    display(head);


    /* Cycle detection */
    if (hasCycle(head))
        printf("Cycle exists\n");
    else
        printf("No cycle\n");


    /* Free memory */
    freeList(&head);

    return 0;
}
