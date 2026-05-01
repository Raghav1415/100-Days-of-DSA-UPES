// Problem Statement
// Given n stalls located at different positions along a straight line and k cows, place the cows in the stalls such that the minimum distance between any two cows is maximized.

// This is an optimization problem where binary search on the answer is required.

// Input Format
// n k
// n space-separated integers representing stall positions

// Output Format
// Print the maximum possible minimum distance between any two cows.

// Sample Input
// 5 3
// 1 2 8 4 9

// Sample Output
// 3

// Explanation
// Cows can be placed at positions 1, 4, and 8. The minimum distance between any two cows is 3, which is the maximum possible.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * The Greedy Engine
 * Checks if we can place 'k' cows with at least 'min_dist' between them.
 */
bool canPlaceCows(int stalls[], int n, int k, int min_dist) {
    // Always place the first cow in the very first stall to maximize remaining space
    int cows_placed = 1;
    int last_pos = stalls[0];

    for (int i = 1; i < n; i++) {
        // If the distance from the last placed cow to this stall is valid...
        if (stalls[i] - last_pos >= min_dist) {
            cows_placed++;        // Drop a cow here
            last_pos = stalls[i]; // Update the measuring tape
            
            // If we successfully placed all cows, this distance is valid!
            if (cows_placed >= k) {
                return true;
            }
        }
    }
    // We ran out of stalls before placing all cows. This distance is too large.
    return false;
}

/**
 * Core Algorithm: Binary Search on Answer
 * Time Complexity: O(N log N) for sort + O(N * log(Max_Distance))
 * Space Complexity: O(1)
 */
int aggressiveCows(int stalls[], int n, int k) {
    // 1. You MUST sort the physical stalls first
    qsort(stalls, n, sizeof(int), compare);

    // 2. Define the Search Space (Distances, not indices)
    int low = 1; // Minimum possible distance
    int high = stalls[n - 1] - stalls[0]; // Maximum possible distance (first to last stall)
    int best_distance = 0;

    // 3. Binary Search the Distance
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canPlaceCows(stalls, n, k, mid)) {
            // We successfully placed them! But can we push them further apart?
            best_distance = mid; // Save this valid answer
            low = mid + 1;       // Force the search space higher
        } else {
            // It failed. The cows don't fit. We must shrink the target distance.
            high = mid - 1; 
        }
    }

    return best_distance;
}

int main() {
    int n, k;
    
    // Read number of stalls and cows
    if (scanf("%d %d", &n, &k) != 2 || n < 2 || k < 2) {
        return 1;
    }

    int* stalls = (int*)malloc(n * sizeof(int));
    if (!stalls) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read stall positions
    for (int i = 0; i < n; i++) {
        scanf("%d", &stalls[i]);
    }

    int result = aggressiveCows(stalls, n, k);
    printf("%d\n", result);

    free(stalls);
    return 0;
}