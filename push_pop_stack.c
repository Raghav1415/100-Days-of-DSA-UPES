// Problem: Implement push and pop operations on a stack and verify stack operations.

// Input:
// - First line: integer n
// - Second line: n integers to push
// - Third line: integer m (number of pops)

// Output:
// - Print remaining stack elements from top to bottom

// Example:
// Input:
// 5
// 10 20 30 40 50
// 2

// Output:
// 30 20 10
#include <stdio.h>

int main() {
    int n, m;
    int stack[100]; // Fixed size for simplicity
    int top = -1;

    // Step 1: Input the number of elements
    if (scanf("%d", &n) != 1) return 1;

    // Step 2: Push elements onto the stack
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        stack[++top] = value; // Increment top, then insert
    }

    // Step 3: Input the number of pops
    scanf("%d", &m);

    // Step 4: Perform the Pop operations
    // We simply move the top index down by m
    top -= m;

    // Step 5: Print remaining elements (Top to Bottom)
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }

    return 0;
}