// Problem: Given an array of integers, count the frequency of each distinct element and print the result.

// Input:
// - First line: integer n (size of array)
// - Second line: n integers

// Output:
// - Print each element followed by its frequency in the format element:count

// Example:
// Input:
// 5
// 1 2 2 3 1

// Output:
// 1:2 2:2 3:1
#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 1;

    int arr[n], visited[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        visited[i] = 0; // Initialize tracking array
    }

    for (int i = 0; i < n; i++) {
        // Skip if we already counted this specific element
        if (visited[i] == 1) continue;

        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1; // Mark as counted
            }
        }
        printf("%d:%d%s", arr[i], count, (i == n - 1) ? "" : " ");
    }
    printf("\n");

    return 0;
}