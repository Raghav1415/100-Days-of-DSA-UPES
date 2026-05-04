// Problem: Given intervals, merge all overlapping ones.
// Sort first, then compare with previous.
#include <stdio.h>
#include <stdlib.h>

// A structure to represent a timeline interval
typedef struct {
    int start;
    int end;
} Interval;

/**
 * Comparator function required by C's built-in qsort
 * Sorts primarily by start time. If start times tie, sorts by end time.
 */
int compareIntervals(const void* a, const void* b) {
    Interval* intA = (Interval*)a;
    Interval* intB = (Interval*)b;
    
    if (intA->start != intB->start) {
        return intA->start - intB->start;
    }
    return intA->end - intB->end;
}

/**
 * Core Algorithm: In-Place Interval Merging
 * Time Complexity: O(N log N) for the sort, O(N) for the sweep
 * Space Complexity: O(1) Auxiliary Space
 * 
 * Returns the new logical size of the array.
 */
int mergeIntervals(Interval intervals[], int n) {
    // Edge case: 0 or 1 intervals are already "merged"
    if (n <= 1) return n;

    // 1. Sort the array chronologically by start time
    qsort(intervals, n, sizeof(Interval), compareIntervals);

    // 2. The In-Place Engine
    // write_index tracks the position of the last successfully merged interval
    int write_index = 0; 

    for (int i = 1; i < n; i++) {
        // If the current interval overlaps with the interval at our write pointer...
        if (intervals[i].start <= intervals[write_index].end) {
            
            // Merge them! Stretch the end time if the current interval reaches further.
            if (intervals[i].end > intervals[write_index].end) {
                intervals[write_index].end = intervals[i].end;
            }
        } 
        // No overlap. The previous merged interval is completely locked in.
        else {
            write_index++; // Move the write pointer forward
            
            // Copy the current interval into the new locked slot
            intervals[write_index] = intervals[i]; 
        }
    }

    // The logical size of the new array is the index + 1
    return write_index + 1; 
}

int main() {
    // Example Input: Unsorted, overlapping intervals
    Interval intervals[] = {{1, 3}, {8, 10}, {2, 6}, {15, 18}};
    int n = sizeof(intervals) / sizeof(intervals[0]);

    printf("Original Intervals:\n");
    for (int i = 0; i < n; i++) {
        printf("[%d, %d] ", intervals[i].start, intervals[i].end);
    }
    printf("\n\n");

    // Execute the algorithm and capture the new logical size
    int new_n = mergeIntervals(intervals, n);

    printf("Merged Intervals:\n");
    for (int i = 0; i < new_n; i++) {
        printf("[%d, %d] ", intervals[i].start, intervals[i].end);
    }
    printf("\n");

    return 0;
}