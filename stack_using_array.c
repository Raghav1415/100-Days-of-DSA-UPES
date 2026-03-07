// Problem: Implement a stack data structure using an array with the following operations: push, pop, and display.

// Input:
// - First line: integer n (number of operations)
// - Next n lines: operation type and value (if applicable)
//   - 1 value: push value
//   - 2: pop
//   - 3: display

// Output:
// - For display: print stack elements from top to bottom
// - For pop: print popped element or 'Stack Underflow'

// Example:
// Input:
// 5
// 1 10
// 1 20
// 3
// 2
// 3

// Output:
// 20 10
// 20
// 10
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Stack {
    int items[MAX];
    int top;
};

void push(struct Stack *s, int value) {
    if (s->top == MAX - 1) {
        return; // Stack Overflow
    }
    s->items[++(s->top)] = value;
}

void pop(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", s->items[s->top--]);
}

void display(struct Stack *s) {
    for (int i = s->top; i >= 0; i--) {
        printf("%d%s", s->items[i], (i == 0 ? "" : " "));
    }
    printf("\n");
}

int main() {
    struct Stack s;
    s.top = -1;
    
    int n, choice, val;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &choice);
        if (choice == 1) {
            scanf("%d", &val);
            push(&s, val);
        } else if (choice == 2) {
            pop(&s);
        } else if (choice == 3) {
            display(&s);
        }
    }
    return 0;
}