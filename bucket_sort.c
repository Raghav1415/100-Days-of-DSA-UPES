// Problem: Given n real numbers in [0,1), sort using bucket sort algorithm.
// Distribute into buckets, sort each, concatenate.
#include <stdio.h>
#include <stdlib.h>

// Node structure for our dynamic bucket lists
typedef struct Node {
    float data;
    struct Node* next;
} Node;

/**
 * On-the-fly Insertion Sort for Linked Lists.
 * Automatically threads the new value into its correct sorted position.
 */
Node* insertSorted(Node* head, float val) {
    // 1. Allocate the new node safely
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = val;
    newNode->next = NULL;

    // 2. Base Case: If the bucket is empty, or the new value is the smallest yet
    if (!head || head->data >= val) {
        newNode->next = head;
        return newNode; // The new node is the new head of the list
    }

    // 3. Scan the bucket to find the exact insertion hole
    Node* current = head;
    while (current->next != NULL && current->next->data < val) {
        current = current->next;
    }
    
    // 4. Splice the node into the list
    newNode->next = current->next;
    current->next = newNode;

    return head; // The head remains unchanged
}

/**
 * Core Algorithm: Bucket Sort for range [0.0, 1.0)
 * Time Complexity: O(N) average, O(N^2) worst case (if all fall in 1 bucket)
 * Space Complexity: O(N) 
 */
void bucketSort(float arr[], int n) {
    if (n <= 0) return;

    // 1. Create an array of 'n' bucket pointers
    // calloc is CRITICAL here because it safely initializes all pointers to NULL
    Node** buckets = (Node**)calloc(n, sizeof(Node*));
    if (!buckets) {
        fprintf(stderr, "Fatal: Memory allocation failed for bucket array.\n");
        exit(EXIT_FAILURE);
    }

    // 2. The Scatter Phase
    for (int i = 0; i < n; i++) {
        // Multiply by N to map a [0, 1) float to an integer index [0, N-1]
        int bucketIndex = n * arr[i];
        
        // Edge case trap: strictly guard against 1.0 overflowing the array bounds
        if (bucketIndex >= n) {
            bucketIndex = n - 1;
        }

        // Insert the value into the correct bucket, sorting it immediately
        buckets[bucketIndex] = insertSorted(buckets[bucketIndex], arr[i]);
    }

    // 3. The Gather Phase (Concatenation & Cleanup)
    int arr_idx = 0;
    for (int i = 0; i < n; i++) {
        Node* current = buckets[i];
        
        // Drain the bucket from smallest to largest
        while (current != NULL) {
            arr[arr_idx++] = current->data; // Overwrite original array
            
            // Surgical memory cleanup: free the node the second we are done with it
            Node* temp = current;
            current = current->next;
            free(temp); 
        }
    }

    // Free the primary pointer array
    free(buckets);
}

int main() {
    int n;
    
    // Safely read the array size
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    // Dynamically allocate the main array
    float* arr = (float*)malloc(n * sizeof(float));
    if (!arr) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Read the array elements (expecting values like 0.78, 0.12, etc.)
    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }

    // Execute the optimized sort
    bucketSort(arr, n);

    // Output formatted correctly for floating-point values
    for (int i = 0; i < n; i++) {
        printf("%.4f ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}