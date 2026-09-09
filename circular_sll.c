#include <stdio.h>
#include <stdlib.h>

/* =========================================================
   NODE
   ========================================================= */

typedef struct Node {
    int data;
    struct Node *next;
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
    newNode->next = NULL;

    return newNode;
}


/* =========================================================
   DISPLAY / TRAVERSE
   ========================================================= */

void display(Node *head) {

    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *temp = head;

    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(HEAD)\n");
}


/* =========================================================
   LENGTH
   ========================================================= */

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


/* =========================================================
   INSERT AT BEGINNING
   ========================================================= */

void insertBeginning(Node **head, int data) {

    Node *newNode = createNode(data);

    /* Empty list */
    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
        return;
    }

    /*
       Find last node.
       Last node points to head.
    */
    Node *last = *head;

    while (last->next != *head)
        last = last->next;

    newNode->next = *head;
    last->next = newNode;

    *head = newNode;
}


/* =========================================================
   INSERT AT END
   ========================================================= */

void insertEnd(Node **head, int data) {

    Node *newNode = createNode(data);

    /* Empty list */
    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
        return;
    }

    Node *last = *head;

    while (last->next != *head)
        last = last->next;

    last->next = newNode;
    newNode->next = *head;
}


/* =========================================================
   INSERT AT POSITION
   Position is 1-based
   ========================================================= */

void insertPosition(Node **head, int data, int position) {

    if (position < 1) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        insertBeginning(head, data);
        return;
    }

    if (*head == NULL) {
        printf("Invalid position\n");
        return;
    }

    Node *temp = *head;

    for (int i = 1; i < position - 1; i++) {

        temp = temp->next;

        if (temp == *head) {
            printf("Invalid position\n");
            return;
        }
    }

    Node *newNode = createNode(data);

    newNode->next = temp->next;
    temp->next = newNode;
}


/* =========================================================
   DELETE FROM BEGINNING
   ========================================================= */

void deleteBeginning(Node **head) {

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    /* Only one node */
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }

    Node *last = *head;

    while (last->next != *head)
        last = last->next;

    Node *temp = *head;

    *head = (*head)->next;

    last->next = *head;

    free(temp);
}


/* =========================================================
   DELETE FROM END
   ========================================================= */

void deleteEnd(Node **head) {

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    /* Only one node */
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }

    Node *temp = *head;

    /*
       Find second-last node.
       Its next points to last node.
    */
    while (temp->next->next != *head)
        temp = temp->next;

    Node *last = temp->next;

    temp->next = *head;

    free(last);
}


/* =========================================================
   DELETE FROM POSITION
   Position is 1-based
   ========================================================= */

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

    for (int i = 1; i < position - 1; i++) {

        temp = temp->next;

        if (temp == *head) {
            printf("Invalid position\n");
            return;
        }
    }

    /*
       If temp->next is head,
       position doesn't exist.
    */
    if (temp->next == *head) {
        printf("Invalid position\n");
        return;
    }

    Node *deleteNode = temp->next;

    temp->next = deleteNode->next;

    free(deleteNode);
}


/* =========================================================
   SEARCH
   Returns 1-based position
   Returns -1 if not found
   ========================================================= */

int search(Node *head, int key) {

    if (head == NULL)
        return -1;

    Node *temp = head;
    int position = 1;

    do {

        if (temp->data == key)
            return position;

        temp = temp->next;
        position++;

    } while (temp != head);

    return -1;
}


/* =========================================================
   UPDATE FIRST OCCURRENCE
   ========================================================= */

void update(Node *head, int oldValue, int newValue) {

    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *temp = head;

    do {

        if (temp->data == oldValue) {
            temp->data = newValue;
            return;
        }

        temp = temp->next;

    } while (temp != head);

    printf("Element not found\n");
}


/* =========================================================
   REVERSE
   ========================================================= */

void reverse(Node **head) {

    if (*head == NULL || (*head)->next == *head)
        return;

    Node *prev = NULL;
    Node *curr = *head;
    Node *next;

    Node *oldHead = *head;

    do {

        next = curr->next;

        curr->next = prev;

        prev = curr;
        curr = next;

    } while (curr != *head);

    /*
       oldHead becomes the last node.
       prev becomes the new head.
    */

    oldHead->next = prev;

    *head = prev;
}


/* =========================================================
   FIND MIDDLE
   Slow-Fast Pointer
   ========================================================= */

Node* findMiddle(Node *head) {

    if (head == NULL)
        return NULL;

    Node *slow = head;
    Node *fast = head;

    /*
       Stop when fast reaches or crosses head again.
    */
    while (fast->next != head &&
           fast->next->next != head) {

        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}


/* =========================================================
   Nth NODE FROM END
   n = 1 -> last node
   ========================================================= */

Node* nthFromEnd(Node *head, int n) {

    if (head == NULL || n <= 0)
        return NULL;

    int len = length(head);

    if (n > len)
        return NULL;

    int positionFromBeginning = len - n + 1;

    Node *temp = head;

    for (int i = 1; i < positionFromBeginning; i++)
        temp = temp->next;

    return temp;
}


/* =========================================================
   CHECK IF LIST IS CIRCULAR
   ========================================================= */

int isCircular(Node *head) {

    if (head == NULL)
        return 0;

    Node *temp = head->next;

    while (temp != NULL && temp != head)
        temp = temp->next;

    return temp == head;
}


/* =========================================================
   REMOVE DUPLICATES
   Works for UNSORTED circular list
   ========================================================= */

void removeDuplicates(Node *head) {

    if (head == NULL)
        return;

    Node *current = head;

    do {

        Node *prev = current;
        Node *temp = current->next;

        while (temp != head) {

            if (temp->data == current->data) {

                prev->next = temp->next;

                Node *deleteNode = temp;
                temp = temp->next;

                free(deleteNode);

            } else {

                prev = temp;
                temp = temp->next;
            }
        }

        current = current->next;

    } while (current != head);
}


/* =========================================================
   SORT
   Bubble Sort by swapping DATA
   ========================================================= */

void sortList(Node *head) {

    if (head == NULL || head->next == head)
        return;

    int swapped;

    Node *ptr;

    do {

        swapped = 0;
        ptr = head;

        do {

            Node *next = ptr->next;

            /*
               Don't compare the last node with head.
            */
            if (next != head && ptr->data > next->data) {

                int temp = ptr->data;
                ptr->data = next->data;
                next->data = temp;

                swapped = 1;
            }

            ptr = ptr->next;

        } while (ptr != head);

    } while (swapped);
}


/* =========================================================
   CONCATENATE TWO CIRCULAR LISTS
   ========================================================= */

void concatenate(Node **head1, Node *head2) {

    if (head2 == NULL)
        return;

    if (*head1 == NULL) {
        *head1 = head2;
        return;
    }

    Node *last1 = *head1;
    Node *last2 = head2;

    while (last1->next != *head1)
        last1 = last1->next;

    while (last2->next != head2)
        last2 = last2->next;

    last1->next = head2;
    last2->next = *head1;
}


/* =========================================================
   FREE ENTIRE LIST
   ========================================================= */

void freeList(Node **head) {

    if (*head == NULL)
        return;

    Node *current = (*head)->next;

    while (current != *head) {

        Node *temp = current;
        current = current->next;

        free(temp);
    }

    free(*head);

    *head = NULL;
}


/* =========================================================
   MAIN
   ========================================================= */

int main() {

    Node *head = NULL;

    /* =========================
       INSERTION
       ========================= */

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    insertBeginning(&head, 5);

    insertPosition(&head, 15, 3);

    printf("List: ");
    display(head);


    /* =========================
       LENGTH
       ========================= */

    printf("Length = %d\n", length(head));


    /* =========================
       SEARCH
       ========================= */

    int pos = search(head, 20);

    if (pos != -1)
        printf("20 found at position %d\n", pos);
    else
        printf("20 not found\n");


    /* =========================
       UPDATE
       ========================= */

    update(head, 30, 35);

    printf("After update: ");
    display(head);


    /* =========================
       DELETE
       ========================= */

    deleteBeginning(&head);

    printf("After deleting beginning: ");
    display(head);

    deleteEnd(&head);

    printf("After deleting end: ");
    display(head);

    deletePosition(&head, 2);

    printf("After deleting position 2: ");
    display(head);


    /* =========================
       ADD MORE ELEMENTS
       ========================= */

    insertEnd(&head, 40);
    insertEnd(&head, 10);
    insertEnd(&head, 25);

    printf("Before sorting: ");
    display(head);


    /* =========================
       SORT
       ========================= */

    sortList(head);

    printf("After sorting: ");
    display(head);


    /* =========================
       MIDDLE
       ========================= */

    Node *middle = findMiddle(head);

    if (middle != NULL)
        printf("Middle = %d\n", middle->data);


    /* =========================
       NTH FROM END
       ========================= */

    Node *nth = nthFromEnd(head, 2);

    if (nth != NULL)
        printf("2nd node from end = %d\n", nth->data);


    /* =========================
       REVERSE
       ========================= */

    reverse(&head);

    printf("After reverse: ");
    display(head);


    /* =========================
       REMOVE DUPLICATES
       ========================= */

    removeDuplicates(head);

    printf("After removing duplicates: ");
    display(head);


    /* =========================
       CHECK CIRCULARITY
       ========================= */

    if (isCircular(head))
        printf("List is circular\n");
    else
        printf("List is not circular\n");


    /* =========================
       FREE MEMORY
       ========================= */

    freeList(&head);

    return 0;
}
