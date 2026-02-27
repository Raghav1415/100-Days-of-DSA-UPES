// Problem: Doubly Linked List Insertion and Traversal - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n
// - Second line: n space-separated integers

// Output:
// - Print the linked list elements in forward order, space-separated

// Example:
// Input:
// 5
// 10 20 30 40 50

// Output:
// 10 20 30 40 50

// Explanation:
// Each node has data, next, prev. Insert nodes sequentially, traverse from head using next pointer.
#include <stdio.h>
#include <stdlib.h>

// Defining the structure of a Doubly Linked List Node
struct Node {
    int data;
    struct Node* next; // Pointer to the next node
    struct Node* prev; // Pointer to the previous node
};

int main() {
    int n, val;
    struct Node *head = NULL, *tail = NULL;

    // Input: Number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        
        // 1. Create a new node in memory
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = val;
        newNode->next = NULL;
        newNode->prev = NULL;

        // 2. If list is empty, new node becomes the head
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            // 3. Link the current tail to the new node
            tail->next = newNode;
            // 4. Link the new node back to the current tail
            newNode->prev = tail;
            // 5. Move the tail pointer to the new node
            tail = newNode;
        }
    }

    // Traversal: Moving forward from head
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" ");
        temp = temp->next;
    }
    printf("\n");

    // Cleanup: Freeing memory to avoid leaks
    while (head != NULL) {
        struct Node* nextNode = head->next;
        free(head);
        head = nextNode;
    }

    return 0;
}