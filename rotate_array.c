// Problem: Given an array of integers, rotate the array to the right by k positions.

// Input:
// - First line: integer n
// - Second line: n integers
// - Third line: integer k

// Output:
// - Print the rotated array

// Example:
// Input:
// 5
// 1 2 3 4 5
// 2

// Output:
// 4 5 1 2 3
#include <stdio.h>

// Helper function to reverse a portion of the array
// valid from index 'start' to 'end'
void reverse(int* arr, int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotate(int* nums, int numsSize, int k) {
    // Optimization: If k is greater than size, we only need the remainder.
    // e.g., rotating 5 items by 7 spots is the same as rotating by 2.
    k = k % numsSize; 
    
    if (k == 0) return; // No rotation needed

    // Step 1: Reverse the ENTIRE array
    reverse(nums, 0, numsSize - 1);

    // Step 2: Reverse the first k elements (the new front)
    reverse(nums, 0, k - 1);

    // Step 3: Reverse the remaining elements (the new back)
    reverse(nums, k, numsSize - 1);
}

int main() {
    int n;
    if (scanf("%d", &n) <= 0) return 0;

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int k;
    if (scanf("%d", &k) <= 0) return 0;

    rotate(arr, n, k);

    // Output the result
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}