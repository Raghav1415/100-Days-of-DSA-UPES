// Problem: Implement Binary Search Iterative - Implement the algorithm.

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
 * Comparator function required by C's built-in qsort
 */
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Core Algorithm: Iterative Binary Search
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 * 
 * Returns the index of the target if found, or -1 if not found.
 */
int binarySearchIterative(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;

    // We continue searching as long as our boundaries haven't crossed
    while (low <= high) {
        // TRAP AVOIDANCE: Safe midpoint calculation to prevent integer overflow
        int mid = low + (high - low) / 2;

        // Check if the exact middle happens to be our target
        if (arr[mid] == target) {
            return mid; 
        }

        // If the middle element is LESS than our target, the target 
        // mathematically MUST be in the right half of the array.
        if (arr[mid] < target) {
            low = mid + 1; // Discard the entire left half
        } 
        // Otherwise, the middle element is GREATER than our target.
        // The target mathematically MUST be in the left half.
        else {
            high = mid - 1; // Discard the entire right half
        }
    }

    // If the loop finishes and low > high, the target does not exist.
    return -1;
}

int main() {
    int n;
    
    // Read array size
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the unsorted elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 1. We MUST sort the array first. Using C's native QuickSort.
    qsort(arr, n, sizeof(int), compare);

    // Let's print the sorted array to satisfy your example output request
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 2. Now we can actually demonstrate the Binary Search
    // Let's hardcode a search for '34' as a demonstration
    int target = 34;
    int result = binarySearchIterative(arr, n, target);

    if (result != -1) {
        printf("Search Result: Target %d found at index %d.\n", target, result);
    } else {
        printf("Search Result: Target %d not found.\n", target);
    }

    free(arr);
    return 0;
}