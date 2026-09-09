#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char data[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char c) {
    s->data[++s->top] = c;
}

char pop(Stack *s) {
    return s->data[s->top--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int isBalanced(char *str) {
    Stack s;
    init(&s);

    for (int i = 0; str[i] != '\0'; i++) {

        // Opening bracket
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            push(&s, str[i]);
        }

        // Closing bracket
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {

            // No opening bracket available
            if (isEmpty(&s))
                return 0;

            // Top opening bracket doesn't match
            if (!isMatching(pop(&s), str[i]))
                return 0;
        }
    }

    // Stack must be empty at the end
    return isEmpty(&s);
}

int main() {
    char str[MAX];

    printf("Enter expression: ");
    fgets(str, MAX, stdin);

    if (isBalanced(str))
        printf("Balanced\n");
    else
        printf("Not Balanced\n");

    return 0;
}
