// Problem: Implement Insertion Sort - Implement the algorithm.

// Input:
// - First line: integer n
// - Second line: n space-separated integers

// Output:
// - Print the sorted array or search result

// Example:
// Input:
// 5
// 64 34 25 12 22

// Output:
// 12 22 25 34 64
#include <stdio.h>
#include <stdlib.h>

/**
 * Core Algorithm: Shift-Optimized Insertion Sort
 * Worst-Case Time Complexity: O(N^2)
 * Best-Case Time Complexity: O(N) (If already sorted)
 * Space Complexity: O(1) In-place
 */
void insertionSort(int arr[], int n) {
    // The loop starts at 1 because a single element (index 0) is already "sorted"
    for (int i = 1; i < n; i++) {
        
        // 1. Extract the element we want to insert
        int key = arr[i];
        
        // 2. Start comparing with the element right before it
        int j = i - 1;

        // 3. The Shifting Engine
        // Move elements of arr[0..i-1], that are greater than the key,
        // to one position ahead of their current position.
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift right (ONLY 1 Memory Write)
            j = j - 1;           // Move the pointer left
        }
        
        // 4. Drop the key into the finalized hole
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    // Dynamically allocate memory to handle any valid input size constraints
    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Execute the optimized sort
    insertionSort(arr, n);

    // Output formatted exactly as requested
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}