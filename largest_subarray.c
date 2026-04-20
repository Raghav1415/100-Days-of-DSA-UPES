// Problem Statement
// Given an array of integers containing both positive and negative values, find the length of the longest contiguous subarray whose sum is equal to zero.

// Input Format
// An integer array arr[].

// Output Format
// Print the length of the longest subarray with sum equal to zero.

// Sample Input
// 15 -2 2 -8 1 7 10 23

// Sample Output
// 5

// Explanation
// The subarray [-2, 2, -8, 1, 7] has a sum of 0 and is the longest such subarray.
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10007 // A prime number to reduce collisions

// --- Custom Hash Map Infrastructure ---
typedef struct HashNode {
    int prefix_sum;
    int index;
    struct HashNode* next;
} HashNode;

HashNode* hashTable[HASH_SIZE];

void initHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// Map any integer (positive or negative) to a valid array index
int getHash(int sum) {
    int h = sum % HASH_SIZE;
    return (h < 0) ? h + HASH_SIZE : h;
}

// O(1) average lookup time
int lookup(int sum) {
    int h = getHash(sum);
    HashNode* curr = hashTable[h];
    while (curr != NULL) {
        if (curr->prefix_sum == sum) {
            return curr->index;
        }
        curr = curr->next;
    }
    return -1; // -1 means this prefix_sum has not been seen yet
}

// O(1) insertion
void insertHash(int sum, int index) {
    int h = getHash(sum);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) exit(EXIT_FAILURE);
    
    newNode->prefix_sum = sum;
    newNode->index = index;
    
    // Insert at head of the chain
    newNode->next = hashTable[h];
    hashTable[h] = newNode;
}

void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = hashTable[i];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}
// --------------------------------------

/**
 * Core Algorithm: Longest Zero-Sum Subarray
 * Time Complexity: O(N) 
 * Space Complexity: O(N) for the Hash Map
 */
int maxLenZeroSumSubarray(int arr[], int n) {
    initHashTable();
    
    int max_len = 0;
    int current_prefix_sum = 0;

    for (int i = 0; i < n; i++) {
        current_prefix_sum += arr[i];

        // Case 1: The element itself is 0, and we haven't found anything longer yet
        if (arr[i] == 0 && max_len == 0) {
            max_len = 1;
        }

        // Case 2: The prefix sum from the absolute beginning (index 0) to 'i' is exactly 0
        if (current_prefix_sum == 0) {
            max_len = i + 1;
        }

        // Case 3: We have seen this exact prefix sum before!
        int prev_index = lookup(current_prefix_sum);
        if (prev_index != -1) {
            // Calculate the length of the subarray that sums to 0
            int current_len = i - prev_index;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            // CRITICAL: We only insert the prefix sum if we haven't seen it before.
            // Why? Because we want the *longest* subarray, so we must preserve 
            // the earliest possible (smallest) index for any given prefix sum.
            insertHash(current_prefix_sum, i);
        }
    }

    freeHashTable();
    return max_len;
}

int main() {
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array: ");
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    int max_length = maxLenZeroSumSubarray(arr, n);
    printf("Length of the longest 0-sum subarray is: %d\n", max_length);

    return 0;
}