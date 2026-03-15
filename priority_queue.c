// Problem Statement:
// Implement a Priority Queue using an array. An element with smaller value has higher priority.

// Supported Operations:
// - insert x
// - delete
// - peek

// Input Format:
// - First line contains integer N
// - Next N lines contain operations

// Output Format:
// - Print the deleted or peeked element
// - Print -1 if the queue is empty

// Example:
// Input:
// 5
// insert 30
// insert 10
// insert 20
// delete
// peek

// Output:
// 10
// 20
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

// Global array to act as our priority queue
int pq[MAX_SIZE];
int size = 0; // Keeps track of how many elements are in the queue

// Function to insert a value while maintaining priority (smallest at the end)
void insert(int val) {
    if (size >= MAX_SIZE) {
        return; // Safety check: Queue is full
    }
    
    int i = size - 1;
    
    // Shift elements to the right to make room for the new value
    // We keep values strictly larger than 'val' on the left
    while (i >= 0 && pq[i] < val) {
        pq[i + 1] = pq[i];
        i--;
    }
    
    // Place the new value in its correct prioritized spot
    pq[i + 1] = val;
    size++;
}

// Function to remove and print the highest priority element
void delete_op() {
    if (size == 0) {
        printf("-1\n");
        return;
    }
    // The smallest element is at the end, so we print it and reduce the size
    printf("%d\n", pq[size - 1]);
    size--;
}

// Function to look at the highest priority element without removing it
void peek() {
    if (size == 0) {
        printf("-1\n");
        return;
    }
    printf("%d\n", pq[size - 1]);
}

int main() {
    int n;
    
    // Read the number of operations
    if (scanf("%d", &n) != 1) return 0;
    
    while (n > 0) {
        char op[10];
        scanf("%s", op);
        
        if (strcmp(op, "insert") == 0) {
            int val;
            scanf("%d", &val);
            insert(val);
        } else if (strcmp(op, "delete") == 0) {
            delete_op();
        } else if (strcmp(op, "peek") == 0) {
            peek();
        }
        n--;
    }
    
    return 0;
}