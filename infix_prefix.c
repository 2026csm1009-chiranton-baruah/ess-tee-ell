/*
Infix:  A+B*(C-D)
Prefix: +A*B-CD
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

typedef struct {
    char data[MAX];
    int top;
} Stack;

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

int precedence(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

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

/* Infix -> Postfix */
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    s.top = -1;

    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isspace(c))
            continue;

        /* Operand */
        if (isalnum(c)) {
            postfix[j++] = c;
        }

        /* Opening bracket */
        else if (c == '(') {
            push(&s, c);
        }

        /* Closing bracket */
        else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(')
                postfix[j++] = pop(&s);

            if (!isEmpty(&s))
                pop(&s);     // remove '('
        }

        /* Operator */
        else {
            while (!isEmpty(&s) &&
                   peek(&s) != '(' &&
                   precedence(peek(&s)) > precedence(c)) {
                postfix[j++] = pop(&s);
            }

            push(&s, c);
        }
    }

    while (!isEmpty(&s))
        postfix[j++] = pop(&s);

    postfix[j] = '\0';
}

/* Infix -> Prefix */
void infixToPrefix(char *infix, char *prefix) {
    char temp[MAX];
    char postfix[MAX];

    strcpy(temp, infix);

    /* Step 1: Reverse */
    reverse(temp);

    /* Step 2: Swap brackets */
    for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] == '(')
            temp[i] = ')';
        else if (temp[i] == ')')
            temp[i] = '(';
    }

    /* Step 3: Convert to postfix */
    infixToPostfix(temp, postfix);

    /* Step 4: Reverse postfix */
    strcpy(prefix, postfix);
    reverse(prefix);
}

int main() {
    char infix[MAX];
    char prefix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);

    infixToPrefix(infix, prefix);

    printf("Prefix: %s\n", prefix);

    return 0;
}
