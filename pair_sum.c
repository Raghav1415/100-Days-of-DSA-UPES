// Problem: Given an array of integers, find two elements whose sum is closest to zero.

// Input:
// - First line: integer n
// - Second line: n space-separated integers

// Output:
// - Print the pair of elements whose sum is closest to zero

// Example:
// Input:
// 5
// 1 60 -10 70 -80

// Output:
// -10 1

// Explanation: Among all possible pairs, the sum of -10 and 1 is -9, which is the closest to zero compared to other pairs.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findMinSumBruteForce(int arr[], int n) {
    // We need at least two numbers to make a pair
    if (n < 2) {
        printf("Invalid Input\n");
        return;
    }

    // Initialize variables to store the best pair found so far
    int min_sum = INT_MAX;
    int first_num = 0;
    int second_num = 0;

    // Outer loop: Select the first element of the pair
    for (int i = 0; i < n - 1; i++) {
        
        // Inner loop: Select the second element (always to the right of 'i')
        for (int j = i + 1; j < n; j++) {
            int current_sum = arr[i] + arr[j];

            // abs() ensures we care about the DISTANCE from zero
            // e.g., -1 is closer to zero than 5.
            if (abs(current_sum) < abs(min_sum)) {
                min_sum = current_sum;
                first_num = arr[i];
                second_num = arr[j];
            }
        }
    }

    // Print the winners
    printf("%d %d\n", first_num, second_num);
}

int main() {
    int n;
    // Get the size of the array
    if (scanf("%d", &n) != 1) return 0;

    int arr[n];
    // Fill the array with user input
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) break;
    }

    findMinSumBruteForce(arr, n);

    return 0;
}