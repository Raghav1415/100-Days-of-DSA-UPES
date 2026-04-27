// Problem: Implement Bubble Sort - Implement the algorithm.

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
#include <stdbool.h>

/**
 * Core Algorithm: Optimized Bubble Sort
 * Worst-Case Time Complexity: O(N^2)
 * Best-Case Time Complexity: O(N) (If already sorted)
 * Space Complexity: O(1) In-place
 */
void bubbleSort(int arr[], int n) {
    bool swapped;
    
    // Outer loop controls the number of passes
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        // Inner loop: Notice the 'n - i - 1'. 
        // We ignore the last 'i' elements because they are already sorted!
        for (int j = 0; j < n - i - 1; j++) {
            
            // If the left element is strictly greater than the right element, swap them
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
                swapped = true; // Flag that a mutation occurred
            }
        }
        
        // THE TRAP AVOIDANCE: Early Exit
        // If we just did a full pass and didn't swap anything, it's fully sorted.
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    // Dynamically allocate the array to handle competitive programming constraints
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
    bubbleSort(arr, n);

    // Output the sorted array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}