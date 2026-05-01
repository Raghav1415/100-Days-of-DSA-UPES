// Problem: Find the integer square root of a given non-negative integer using Binary Search. The integer square root of a number is defined as the greatest integer whose square is less than or equal to the given number.

// Input:
// - First line: an integer n

// Output:
// - Print the integer square root of n

// Examples:
// Input:
// 64

// Output:
// 8

// Input:
// 20

// Output:
// 4

// Input:
// 1

// Output:
// 1

// Explanation:
// Binary Search is applied on the range 0 to n. At each step, the middle value is squared and compared with n. If mid * mid equals n, mid is the square root. If mid * mid is less than n, search continues in the right half; otherwise, in the left half. The final answer is the largest integer whose square does not exceed n.
#include <stdio.h>

/**
 * Core Algorithm: Integer Square Root via Binary Search
 * Time Complexity: O(log N)
 * Space Complexity: O(1)
 */
int integerSquareRoot(int n) {
    // Edge Cases: The square root of 0 is 0, and 1 is 1.
    // Handling these upfront prevents a divide-by-zero error later (n / mid).
    if (n == 0 || n == 1) {
        return n;
    }

    int low = 1;
    int high = n;
    int ans = 0;

    while (low <= high) {
        // Safe midpoint calculation to prevent pointer overflow
        int mid = low + (high - low) / 2;

        // TRAP AVOIDANCE: Using division instead of (mid * mid <= n)
        if (mid <= n / mid) {
            ans = mid;       // This is a valid candidate, save it
            low = mid + 1;   // Try to find a larger valid candidate
        } else {
            // mid is too large, the answer must be in the lower half
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    int n;
    
    // Read the input gracefully
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    // Execute and print
    printf("%d\n", integerSquareRoot(n));

    return 0;
}