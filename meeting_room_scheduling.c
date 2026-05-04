// Problem: Given meeting intervals, find minimum number of rooms required.
// Sort by start time and use min-heap on end times.
#include <stdio.h>
#include <stdlib.h>

// A simple structure to represent a meeting interval
typedef struct {
    int start;
    int end;
} Interval;

/**
 * Comparator function required by C's built-in qsort
 */
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Core Algorithm: Maximum Overlap via Two-Pointer Sweep-Line
 * Time Complexity: O(N log N) for sorting
 * Space Complexity: O(N) for separated start/end arrays
 */
int minMeetingRooms(Interval intervals[], int n) {
    if (n == 0) return 0;

    // 1. Allocate flat, contiguous arrays for starts and ends
    int* starts = (int*)malloc(n * sizeof(int));
    int* ends = (int*)malloc(n * sizeof(int));
    
    if (!starts || !ends) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // 2. Separate the temporal data
    for (int i = 0; i < n; i++) {
        starts[i] = intervals[i].start;
        ends[i] = intervals[i].end;
    }

    // 3. Sort both arrays independently. 
    // We no longer care WHICH meeting ends when, only THAT a meeting ends.
    qsort(starts, n, sizeof(int), compare);
    qsort(ends, n, sizeof(int), compare);

    // 4. The Sweep-Line Engine
    int rooms_needed = 0;
    int max_rooms = 0;
    int s_ptr = 0; // Pointer for start times
    int e_ptr = 0; // Pointer for end times

    // Walk through time chronologically
    while (s_ptr < n) {
        // If a meeting starts before the earliest ending meeting finishes...
        if (starts[s_ptr] < ends[e_ptr]) {
            rooms_needed++;     // We must open a new room
            s_ptr++;            // Move to the next starting meeting
            
            // Track the maximum concurrency we've seen so far
            if (rooms_needed > max_rooms) {
                max_rooms = rooms_needed;
            }
        } 
        // Otherwise, a previous meeting has ended, freeing up a room!
        else {
            rooms_needed--;     // A room is vacated
            e_ptr++;            // Move to the next ending meeting
        }
    }

    // Memory Cleanup
    free(starts);
    free(ends);

    return max_rooms;
}

int main() {
    // Example Input: [[0, 30], [5, 10], [15, 20]]
    Interval intervals[] = {
        {0, 30},
        {5, 10},
        {15, 20}
    };
    int n = sizeof(intervals) / sizeof(intervals[0]);

    int required_rooms = minMeetingRooms(intervals, n);
    printf("Minimum meeting rooms required: %d\n", required_rooms);

    return 0;
}