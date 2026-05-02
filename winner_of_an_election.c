// Problem Statement
// Given an array of candidate names where each name represents a vote cast for that candidate, determine the candidate who received the maximum number of votes. In case of a tie, return the lexicographically smallest candidate name.

// Input Format
// First line contains an integer n representing number of votes.
// Second line contains n space-separated strings representing candidate names.

// Output Format
// Print the name of the winning candidate followed by the number of votes received.

// Sample Input
// 13
// john johnny jackie johnny john jackie jamie jamie john johnny jamie johnny john

// Sample Output
// john 4

// Explanation
// Both john and johnny receive 4 votes, but john is lexicographically smaller, so john is declared the winner.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 55 // Safe buffer size for names

/**
 * Comparator function required by C's built-in qsort
 * Compares two strings lexicographically.
 */
int compareStrings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

/**
 * Core Algorithm: Sort and Linear Scan Frequency Counter
 * Time Complexity: O(N log N * L) where L is max string length
 * Space Complexity: O(1) auxiliary space (sort is in-place)
 */
void findWinner(char names[][MAX_NAME_LEN], int n) {
    // 1. Sort the entire array of names alphabetically
    qsort(names, n, MAX_NAME_LEN, compareStrings);

    int max_votes = 0;
    int current_votes = 1;
    char winner[MAX_NAME_LEN] = "";
    char current_candidate[MAX_NAME_LEN];
    
    // Initialize the engine with the first candidate
    strcpy(current_candidate, names[0]);

    // 2. The Linear Scan (The Tally)
    for (int i = 1; i < n; i++) {
        // If the current vote matches the one we are tallying...
        if (strcmp(names[i], current_candidate) == 0) {
            current_votes++;
        } else {
            // The block ended. Did this candidate beat the record?
            // Note: STRICTLY greater (>). If it's a tie, we do NOT overwrite,
            // preserving the alphabetically smaller winner.
            if (current_votes > max_votes) {
                max_votes = current_votes;
                strcpy(winner, current_candidate);
            }
            
            // Reset the tally engine for the new candidate block
            strcpy(current_candidate, names[i]);
            current_votes = 1;
        }
    }
    
    // 3. The Final Flush
    // We must check the final block of votes after the loop finishes
    if (current_votes > max_votes) {
        max_votes = current_votes;
        strcpy(winner, current_candidate);
    }

    // Output formatted exactly as requested
    printf("%s %d\n", winner, max_votes);
}

int main() {
    int n;
    
    // Read the number of votes safely
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    // Dynamically allocate a 2D array to handle massive inputs without blowing the stack
    char (*names)[MAX_NAME_LEN] = malloc(n * MAX_NAME_LEN);
    if (!names) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the space-separated strings
    for (int i = 0; i < n; i++) {
        scanf("%54s", names[i]); // %54s prevents buffer overflow
    }

    // Execute the algorithm
    findWinner(names, n);

    free(names);
    return 0;
}