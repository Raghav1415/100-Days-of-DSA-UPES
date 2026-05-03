// Problem: Implement merge sort (divide, sort halves, merge).
// Print sorted array.
#include <stdio.h>
#include <stdlib.h>

/**
 * The Merge Engine
 * Combines two sorted sub-arrays into a single sorted segment using the pre-allocated buffer.
 */
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;      // Pointer for the left half
    int j = mid + 1;   // Pointer for the right half
    int k = left;      // Pointer for the temporary buffer

    // Compare elements from both halves and copy the strictly smaller one into temp
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Flush any remaining elements in the left half
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Flush any remaining elements in the right half
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Write the sorted segment back to the original array
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = temp[idx];
    }
}

/**
 * Core Algorithm: The Recursive Divide Phase
 */
void mergeSortRecursive(int arr[], int temp[], int left, int right) {
    if (left < right) {
        // Safe midpoint calculation to prevent integer overflow on massive arrays
        int mid = left + (right - left) / 2; 

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

    // Fire the recursive engine
    mergeSortRecursive(arr, temp, 0, n - 1);

    // Clean up
    free(temp); 
}

int main() {
    int n;
    
    // Safely read the size of the array
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

    // Output formatted strictly as requested
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}