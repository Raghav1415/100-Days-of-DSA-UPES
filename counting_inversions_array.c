// Problem: Count number of inversions using modified merge sort.
// Inversion if i < j and a[i] > a[j].
#include <stdio.h>
#include <stdlib.h>

// Function to merge two halves and count inversions
long long mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;    // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;    // Starting index to be sorted
    long long inv_count = 0;

    // Conditions are checked to make sure that i and j don't exceed their subarray limits.
    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // Inversion found! 
            // All remaining elements in the left subarray (from i to mid) are greater than arr[j]
            temp[k++] = arr[j++];
            inv_count = inv_count + (mid - i + 1);
        }
    }

    // Copy the remaining elements of left subarray (if any)
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy the remaining elements of right subarray (if any)
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy back the merged elements to original array
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

// Function to divide the array and accumulate inversion counts
long long mergeSortAndCount(int arr[], int temp[], int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Count inversions in the left half
        inv_count += mergeSortAndCount(arr, temp, left, mid);

        // Count inversions in the right half
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);

        // Count inversions occurring across the split
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

int main() {
    int arr[] = {8, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Allocate temporary array to be used during the merge process
    int *temp = (int *)malloc(n * sizeof(int));
    
    printf("Given array is \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    long long inversions = mergeSortAndCount(arr, temp, 0, n - 1);
    
    printf("Number of inversions are: %lld \n", inversions);
    
    free(temp); // Always free allocated memory
    return 0;
}