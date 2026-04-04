// Problem Statement:
// Check whether a given binary tree satisfies the Min-Heap property.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal

// Output Format:
// - Print YES if valid Min-Heap, otherwise NO

// Example:
// Input:
// 7
// 1 3 5 7 9 8 10

// Output:
// YES

// Explanation:
// Each parent node must be smaller than its children.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Core Algorithm: Validates the Min-Heap property in-place.
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
bool isMinHeap(int* arr, int n) {
    // In a zero-indexed array representing a complete binary tree,
    // we only need to check internal nodes (nodes that have children).
    // The last internal node is mathematically guaranteed to be at index (n/2) - 1.
    
    for (int i = 0; i <= (n / 2) - 1; i++) {
        int leftChildIdx = 2 * i + 1;
        int rightChildIdx = 2 * i + 2;

        // Check Left Child
        // Note: The bounds check (leftChildIdx < n) is strictly necessary 
        // to prevent segfaults on the last internal node which might only have a left child.
        if (leftChildIdx < n && arr[i] > arr[leftChildIdx]) {
            return false;
        }

        // Check Right Child
        if (rightChildIdx < n && arr[i] > arr[rightChildIdx]) {
            return false;
        }
    }

    return true; // All parent-child relationships are valid
}

int main() {
    int n;
    // Read total number of nodes
    if (scanf("%d", &n) != 1) return 1;

    // Handle edge case of empty input
    if (n <= 0) {
        printf("YES\n"); // An empty tree trivially satisfies the property
        return 0;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the level-order traversal directly into the array
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Execute validation and format output
    if (isMinHeap(arr, n)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    // Clean up heap allocation
    free(arr);

    return 0;
}