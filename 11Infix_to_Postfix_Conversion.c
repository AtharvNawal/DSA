#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Peek at the top of the stack
char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

// Pop an element from the stack
char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '\0';
}

// Push an element to the stack
void push(struct Stack* stack, char op) {
    stack->array[++stack->top] = op;
}

// Check if character is an operand
int isOperand(char ch) {
    return isalnum(ch);
}

// Get precedence of an operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

// Convert infix expression to postfix
void infixToPostfix(char* exp) {
    int i, k;
    struct Stack* stack = createStack(strlen(exp));
    if (!stack)
        return;
    
    for (i = 0, k = -1; exp[i]; ++i) {
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        else if (exp[i] == '(')
            push(stack, exp[i]);
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            pop(stack); // remove '('
        }
        else {
            while (!isEmpty(stack) && precedence(exp[i]) <= precedence(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
    }

    while (!isEmpty(stack))
        exp[++k] = pop(stack);

    exp[++k] = '\0';
    printf("Postfix Expression: %s\n", exp);
}

int main() {
    char exp[100];
    printf("Enter Infix expression: ");
    scanf("%s", exp);
    infixToPostfix(exp);
    return 0;
}