#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

char peek(Stack *s) {
    return s->data[s->top];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

/* Operator precedence */
int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '+' || op == '-')
        return 1;

    return 0;
}

/* Check whether operator is right associative */
int isRightAssociative(char op) {
    return op == '^';
}

/* Infix -> Postfix */
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    init(&s);

    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {

        char c = infix[i];

        /* Ignore spaces */
        if (isspace(c))
            continue;

        /* Operand */
        if (isalnum(c)) {
            postfix[j++] = c;
        }

        /* Opening parenthesis */
        else if (c == '(') {
            push(&s, c);
        }

        /* Closing parenthesis */
        else if (c == ')') {

            while (!isEmpty(&s) && peek(&s) != '(')
                postfix[j++] = pop(&s);

            if (!isEmpty(&s))
                pop(&s);        // Remove '('
        }

        /* Operator */
        else {
            while (!isEmpty(&s) &&
                   peek(&s) != '(' &&
                   (precedence(peek(&s)) > precedence(c) ||
                   (precedence(peek(&s)) == precedence(c) &&
                    !isRightAssociative(c)))) {

                postfix[j++] = pop(&s);
            }

            push(&s, c);
        }
    }

    /* Pop remaining operators */
    while (!isEmpty(&s))
        postfix[j++] = pop(&s);

    postfix[j] = '\0';
}

/* Reverse a string */
void reverse(char *str) {
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
}

/* Infix -> Prefix */
void infixToPrefix(char *infix, char *prefix) {
    char reversed[MAX];
    char postfix[MAX];

    strcpy(reversed, infix);

    /*
     * Reverse the infix expression.
     * While reversing:
     * '(' becomes ')'
     * ')' becomes '('
     */
    reverse(reversed);

    for (int i = 0; reversed[i] != '\0'; i++) {
        if (reversed[i] == '(')
            reversed[i] = ')';
        else if (reversed[i] == ')')
            reversed[i] = '(';
    }

    /*
     * Convert reversed expression to postfix.
     */
    infixToPostfix(reversed, postfix);

    /*
     * Reverse postfix to obtain prefix.
     */
    strcpy(prefix, postfix);
    reverse(prefix);
}

int main() {
    char infix[MAX];
    char postfix[MAX];
    char prefix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);

    infixToPostfix(infix, postfix);
    infixToPrefix(infix, prefix);

    printf("\nPostfix: %s\n", postfix);
    printf("Prefix:  %s\n", prefix);

    return 0;
}
