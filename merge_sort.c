// Problem: Implement Merge Sort - Implement the algorithm.

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
 * The Merge Engine
 * Combines two sorted sub-arrays into a single sorted segment.
 */
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;      // Pointer for the left half
    int j = mid + 1;   // Pointer for the right half
    int k = left;      // Pointer for the temporary array

    // Compare elements from both halves and copy the smaller one into temp
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // If there are leftover elements in the left half, copy them over
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // If there are leftover elements in the right half, copy them over
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // CRITICAL: Copy the sorted elements from temp back into the original array
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = temp[idx];
    }
}

/**
 * Core Algorithm: The Recursive Divide Phase
 */
void mergeSortRecursive(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Prevents integer overflow

        // Recursively divide the left and right halves
        mergeSortRecursive(arr, temp, left, mid);
        mergeSortRecursive(arr, temp, mid + 1, right);

        // Stitch them back together
        merge(arr, temp, left, mid, right);
    }
}

/**
 * Wrapper Function: Handles single-allocation memory management
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) strict maximum
 */
void mergeSort(int arr[], int n) {
    if (n <= 1) return;

    // Allocate the auxiliary array EXACTLY ONCE
    int* temp = (int*)malloc(n * sizeof(int));
    if (!temp) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    mergeSortRecursive(arr, temp, 0, n - 1);

    free(temp); // Clean up
}

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    // Dynamically allocate the main array
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
    mergeSort(arr, n);

    // Output formatted exactly as requested
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}