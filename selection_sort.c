// Problem: Implement Selection Sort - Implement the algorithm.

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
 * Core Algorithm: Minimum-Write Selection Sort
 * Time Complexity: O(N^2) in all cases (Best, Worst, Average)
 * Space Complexity: O(1) In-place
 * Swap Complexity: O(N) strict maximum
 */
void selectionSort(int arr[], int n) {
    // Outer loop moves the boundary of the sorted subarray
    for (int i = 0; i < n - 1; i++) {
        
        // 1. Assume the first unsorted element is the absolute minimum
        int min_idx = i;

        // 2. The Scanning Engine (Inner Loop)
        for (int j = i + 1; j < n; j++) {
            // We ONLY update the index pointer, never the actual array data
            if (arr[j] < arr[min_idx]) {
                min_idx = j; 
            }
        }

        // 3. The Trap Avoidance (Self-Swap Check)
        // If the minimum element is already at index 'i', do not waste CPU cycles 
        // overwriting memory with the exact same value.
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    // Dynamically allocate to handle competitive programming constraints safely
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
    selectionSort(arr, n);

    // Output formatted exactly as requested
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}