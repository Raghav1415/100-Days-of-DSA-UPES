// Problem: Evaluate Postfix Expression - Implement using linked list with dynamic memory allocation.

// Input:
// - Postfix expression with operands and operators

// Output:
// - Print the integer result

// Example:
// Input:
// 2 3 1 * + 9 -

// Output:
// -4

// Explanation:
// Use stack to store operands, apply operators by popping operands, push result back. Final stack top is result.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Structure for a Stack Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to push an item to the stack
void push(Node** top, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory Allocation Failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop an item from the stack
int pop(Node** top) {
    if (*top == NULL) {
        fprintf(stderr, "Stack Underflow: Invalid Expression\n");
        exit(1);
    }
    Node* temp = *top;
    int value = temp->data;
    *top = (*top)->next;
    free(temp);
    return value;
}

int evaluatePostfix(char* exp) {
    Node* stack = NULL;
    char* token = strtok(exp, " ");

    while (token != NULL) {
        // If the token is a number (handles multi-digit and negatives)
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atoi(token));
        } 
        else {
            // Token is an operator
            int val2 = pop(&stack);
            int val1 = pop(&stack);

            switch (token[0]) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': push(&stack, val1 / val2); break;
            }
        }
        token = strtok(NULL, " ");
    }
    return pop(&stack);
}

int main() {
    char expression[] = "2 3 1 * + 9 -";
    printf("Result: %d\n", evaluatePostfix(expression));
    return 0;
}