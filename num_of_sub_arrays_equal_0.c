// Problem: Given an array of integers, count the number of subarrays whose sum is equal to zero.

// Input:
// - First line: integer n
// - Second line: n integers

// Output:
// - Print the count of subarrays having sum zero

// Example:
// Input:
// 6
// 1 -1 2 -2 3 -3

// Output:
// 6

// Explanation: A subarray is a continuous part of the array. For the input array 1 -1 2 -2 3 -3, the following subarrays have sum zero: [1, -1], [2, -2], [3, -3], [1, -1, 2, -2], [2, -2, 3, -3], and [1, -1, 2, -2, 3, -3]. Since there are 6 such subarrays, the output is 6.
#include <stdio.h>
#include <stdlib.h>

// Master Level: Using long long for sums to prevent overflow
typedef struct {
    long long value;
} PrefixSum;

// Comparison for qsort: keeping it efficient
int compare(const void *a, const void *b) {
    long long va = ((PrefixSum *)a)->value;
    long long vb = ((PrefixSum *)b)->value;
    return (va > vb) - (va < vb);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // Allocate n+1 to include the initial sum of 0
    PrefixSum *ps = malloc((n + 1) * sizeof(PrefixSum));
    ps[0].value = 0;
    
    long long running_sum = 0;
    for (int i = 1; i <= n; i++) {
        int temp;
        scanf("%d", &temp);
        running_sum += temp;
        ps[i].value = running_sum;
    }

    // Sort all prefix sums: O(n log n)
    qsort(ps, n + 1, sizeof(PrefixSum), compare);

    long long count = 0;
    long long duplicates = 1;

    // Count identical prefix sums
    for (int i = 1; i <= n; i++) {
        if (ps[i].value == ps[i - 1].value) {
            duplicates++;
        } else {
            // Combinatorial formula: nC2 = n*(n-1)/2
            count += (duplicates * (duplicates - 1)) / 2;
            duplicates = 1;
        }
    }
    count += (duplicates * (duplicates - 1)) / 2;

    printf("%lld\n", count);

    free(ps);
    return 0;
}