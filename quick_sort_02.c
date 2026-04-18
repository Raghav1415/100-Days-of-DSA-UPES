// Problem: Implement Quick Sort using partition method (Lomuto or Hoare).
#include <stdio.h>
#include <stdlib.h>

/**
 * Utility function for fast, in-place memory swapping
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * The Partition Engine: Hoare's Scheme
 * Time Complexity: O(N) per partition
 */
int partition(int arr[], int low, int high) {
    // TRAP AVOIDANCE: Pick the middle element to prevent O(N^2) on sorted data.
    int pivot = arr[low + (high - low) / 2];
    
    // We start the pointers strictly OUTSIDE the array bounds 
    // because the do-while loops will instantly increment/decrement them.
    int i = low - 1;
    int j = high + 1;

    while (1) {
        // Move the left pointer to the right until we find something that 
        // belongs on the right side of the pivot (i.e., >= pivot).
        do {
            i++;
        } while (arr[i] < pivot);

        // Move the right pointer to the left until we find something that 
        // belongs on the left side of the pivot (i.e., <= pivot).
        do {
            j--;
        } while (arr[j] > pivot);

        // If the pointers have crossed or met, the partitioning is complete.
        // We return 'j', which is the new dividing boundary.
        if (i >= j) {
            return j;
        }

        // The pointers stopped because they found two elements on the WRONG sides.
        // Swap them to their correct sides.
        swap(&arr[i], &arr[j]);
    }
}

/**
 * Core Algorithm: The Recursive Divide Phase
 * Best/Average Time Complexity: O(N log N)
 * Worst Time Complexity: O(N^2) (Mitigated by middle-pivot selection)
 * Space Complexity: O(log N) due to recursive call stack
 */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is the partition index; arr[low...pi] are smaller than the pivot,
        // and arr[pi+1...high] are greater than or equal to the pivot.
        int pi = partition(arr, low, high);

        // Recursively sort the left and right partitions.
        // Notice Hoare's scheme includes 'pi' in the left partition, unlike Lomuto.
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    
    // Safely read the size of the array
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    // Dynamically allocate to handle large constraints safely
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
    quickSort(arr, 0, n - 1);

    // Output formatted exactly as requested
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}