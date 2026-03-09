// Problem: Convert an infix expression to postfix notation using stack.

// Input:
// - Single line: infix expression (operands are single characters)

// Output:
// - Print the postfix expression

// Example:
// Input:
// A+B*C

// Output:
// ABC*+

// Explanation:
// Operator precedence: * > +
// Use stack to handle operator precedence and associativity
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Simple Stack Structure
char stack[MAX];
int top = -1;

void push(char item) {
    stack[++top] = item;
}

char pop() {
    return stack[top--];
}

// Function to determine operator precedence
int precedence(char symbol) {
    switch(symbol) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char symbol, next;

    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];

        // If it's an operand, add it to output
        if (isalnum(symbol)) {
            postfix[j++] = symbol;
        } 
        else if (symbol == '(') {
            push(symbol);
        } 
        else if (symbol == ')') {
            while ((next = pop()) != '(') {
                postfix[j++] = next;
            }
        } 
        else { // It's an operator
            while (top != -1 && precedence(stack[top]) >= precedence(symbol)) {
                postfix[j++] = pop();
            }
            push(symbol);
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0'; // Null-terminate the string
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter Infix Expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix Expression: %s\n", postfix);

    return 0;
}