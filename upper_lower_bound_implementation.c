// Problem: Given a sorted array of integers and a target value x, implement the Lower Bound and Upper Bound operations using Binary Search.

// Lower Bound: The index of the first element in the array that is greater than or equal to x.
// Upper Bound: The index of the first element in the array that is strictly greater than x.

// Input:
// - First line: integer n representing the size of the array
// - Second line: n space-separated sorted integers
// - Third line: integer x (the target value)

// Output:
// - Print two integers:
//   1) Index of the lower bound of x
//   2) Index of the upper bound of x

// Example:
// Input:
// 7
// 1 2 4 4 4 5 7
// 4

// Output:
// 2 5

// Explanation:
// For the given array [1, 2, 4, 4, 4, 5, 7] and x = 4:
// - The lower bound is at index 2, which is the first occurrence of 4.
// - The upper bound is at index 5, which is the first element greater than 4 (i.e., 5).
// Binary Search is used to find both bounds efficiently in O(log n) time.
#include <stdio.h>
#include <stdlib.h>

/**
 * Lower Bound: Index of the FIRST element >= x.
 * Time Complexity: O(log N)
 */
int lowerBound(int arr[], int n, int x) {
    int low = 0;
    int high = n; // CRITICAL: Start at 'n', not 'n-1'. The bound might be outside the array.

    while (low < high) {
        // Prevents integer overflow for massive arrays
        int mid = low + (high - low) / 2; 

        // If mid is greater than OR EQUAL to target, the boundary must be to the left (or here)
        if (arr[mid] >= x) {
            high = mid; 
        } else {
            // arr[mid] is strictly less than target, so boundary is definitely to the right
            low = mid + 1; 
        }
    }
    
    return low; // low and high converge to the exact lower bound index
}

/**
 * Upper Bound: Index of the FIRST element STRICTLY > x.
 * Time Complexity: O(log N)
 */
int upperBound(int arr[], int n, int x) {
    int low = 0;
    int high = n;

    while (low < high) {
        int mid = low + (high - low) / 2;

        // THE ONLY DIFFERENCE: We only move 'high' down if we find something STRICTLY greater
        if (arr[mid] > x) {
            high = mid;
        } else {
            // If arr[mid] is <= target, the upper boundary hasn't been reached yet
            low = mid + 1;
        }
    }
    
    return low;
}

int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1 || n < 0) return 1;

    // Dynamically allocate to handle large inputs cleanly
    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the sorted array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int x;
    // Read the target value
    if (scanf("%d", &x) != 1) {
        free(arr);
        return 1;
    }

    // Execute O(log N) searches
    int lb = lowerBound(arr, n, x);
    int ub = upperBound(arr, n, x);

    // Output formatted exactly as requested
    printf("%d %d\n", lb, ub);

    free(arr);
    return 0;
}