// Problem Statement
// Given n boards of different lengths and k painters, each painter paints contiguous boards. Painting a unit length of board takes one unit of time.

// Determine the minimum time required to paint all boards.

// Input Format
// n k
// n space-separated integers representing board lengths

// Output Format
// Print the minimum time required to paint all boards.

// Sample Input
// 4 2
// 10 20 30 40

// Sample Output
// 60

// Explanation
// One painter paints boards of length 10, 20, and 30 (total 60), while the other paints board of length 40.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * The Greedy Validator
 * Simulates the painting process to see if 'k' painters can finish the job 
 * if they are strictly given 'max_time' to work.
 */
bool canPaint(int boards[], int n, int k, long long max_time) {
    int painters_needed = 1;
    long long current_painter_time = 0;

    for (int i = 0; i < n; i++) {
        // If assigning this board exceeds the painter's time limit...
        if (current_painter_time + boards[i] > max_time) {
            
            // We must hire a new painter
            painters_needed++;
            current_painter_time = boards[i]; // New painter starts with this board
            
            // If we run out of available painters, this time limit is impossible
            if (painters_needed > k) {
                return false;
            }
        } else {
            // Otherwise, keep assigning contiguous boards to the current painter
            current_painter_time += boards[i];
        }
    }
    return true; 
}

/**
 * Core Algorithm: Binary Search on Answer
 * Time Complexity: O(N * log(Sum - Max))
 * Space Complexity: O(1)
 */
long long minTimeToPaint(int boards[], int n, int k) {
    long long low = 0;
    long long high = 0;

    // Define the boundaries of our search space
    for (int i = 0; i < n; i++) {
        if (boards[i] > low) {
            low = boards[i]; // Bottleneck: The longest single board
        }
        high += boards[i];   // Worst case: One painter does everything
    }

    long long best_time = high;

    // Binary Search the theoretical time limits
    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (canPaint(boards, n, k, mid)) {
            // It is mathematically possible to finish in 'mid' time.
            // But can we push them to work even faster?
            best_time = mid;
            high = mid - 1; 
        } else {
            // 'mid' is too fast. We ran out of painters. Give them more time.
            low = mid + 1;
        }
    }

    return best_time;
}

int main() {
    int n, k;
    
    // Safely read board count and painter count
    if (scanf("%d %d", &n, &k) != 2) return 1;

    int* boards = (int*)malloc(n * sizeof(int));
    if (!boards) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the board lengths
    for (int i = 0; i < n; i++) {
        scanf("%d", &boards[i]);
    }

    long long result = minTimeToPaint(boards, n, k);
    printf("%lld\n", result);

    free(boards);
    return 0;
}