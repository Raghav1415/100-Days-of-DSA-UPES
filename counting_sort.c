// Problem: Sort array of non-negative integers using counting sort.
// Find max, build freq array, compute prefix sums, build output.
#include <stdio.h>
#include <stdlib.h>

/**
 * Core Algorithm: Stable Counting Sort
 * Time Complexity: O(N + K) where K is the max element
 * Space Complexity: O(N + K)
 */
void countingSort(int arr[], int n) {
    if (n <= 1) return;

    // 1. Find the maximum element to bound our frequency array
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // TRAP AVOIDANCE: If max is abnormally huge compared to N, 
    // Counting Sort is the wrong algorithm. (We proceed assuming K is reasonable).

    // 2. Allocate the frequency array (calloc safely initializes everything to 0)
    int* count = (int*)calloc(max + 1, sizeof(int));
    if (!count) {
        fprintf(stderr, "Fatal: Memory allocation failed for count array.\n");
        exit(EXIT_FAILURE);
    }

    // 3. Allocate the temporary output array
    int* output = (int*)malloc(n * sizeof(int));
    if (!output) {
        fprintf(stderr, "Fatal: Memory allocation failed for output array.\n");
        free(count);
        exit(EXIT_FAILURE);
    }

    // 4. The Tally: Count the occurrences of each element
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 5. The Prefix Sum: Calculate cumulative frequencies
    // This transforms counts into exact, 1-based target indices for the output array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // 6. Build the Output Array (MUST iterate backwards for Stability)
    for (int i = n - 1; i >= 0; i--) {
        int current_val = arr[i];
        
        // Count array gives us the 1-based position, so subtract 1 for 0-based indexing
        int target_index = count[current_val] - 1; 
        
        output[target_index] = current_val;
        
        // Decrement the count so the next identical number goes to the left
        count[current_val]--; 
    }

    // 7. Flush the sorted output back into the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // Deep Memory Cleanup
    free(count);
    free(output);
}

int main() {
    int n;
    
    // Safely read the array size
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

    countingSort(arr, n);

    // Output formatted exactly as requested
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}