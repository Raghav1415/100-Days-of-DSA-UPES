// Problem: Sort an array using insertion sort.
// Stable sort. Good for nearly sorted arrays.
#include <stdio.h>
#include <stdlib.h>

/**
 * Core Algorithm: Shift-Optimized Insertion Sort
 * Worst-Case Time Complexity: O(N^2)
 * Best-Case Time Complexity: O(N) (Nearly sorted arrays)
 * Space Complexity: O(1) In-place
 */
void insertionSort(int arr[], int n) {
    // We start at index 1 because an array of 1 element (index 0) is inherently sorted.
    for (int i = 1; i < n; i++) {
        
        // 1. Extract the element to insert (This creates our "hole")
        int key = arr[i];
        
        // 2. Initialize the pointer for the sorted section to the left
        int j = i - 1;

        // 3. The Shifting Engine
        // Move elements of arr[0..i-1] that are greater than the key
        // to one position ahead of their current position.
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift right (1 memory write)
            j = j - 1;           // Move the inspection pointer left
        }
        
        // 4. Drop the key into the finalized hole
        arr[j + 1] = key;
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    insertionSort(arr, n);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}