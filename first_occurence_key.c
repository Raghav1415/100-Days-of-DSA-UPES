// Problem: Delete First Occurrence of a Key - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n
// - Second line: n space-separated integers
// - Third line: integer key

// Output:
// - Print the linked list elements after deletion, space-separated

// Example:
// Input:
// 5
// 10 20 30 40 50
// 30

// Output:
// 10 20 40 50

// Explanation:
// Traverse list, find first node with key, remove it by adjusting previous node's next pointer.
#include <stdio.h>
#include <stdlib.h>

// Defining the structure of our node
struct Node {
    int data;
    struct Node* next;
};

int main() {
    int n, key;
    struct Node *head = NULL, *tail = NULL, *temp;

    // 1. Reading input size
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    // 2. Building the linked list
    for (int i = 0; i < n; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        scanf("%d", &newNode->data);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // 3. Reading the key to delete
    scanf("%d", &key);

    // 4. Deletion Logic
    struct Node *current = head, *prev = NULL;

    while (current != NULL) {
        if (current->data == key) {
            // If the key is at the head
            if (prev == NULL) {
                head = current->next;
            } else {
                // Bypass the current node
                prev->next = current->next;
            }
            free(current); // Release memory
            break; // We only delete the FIRST occurrence
        }
        prev = current;
        current = current->next;
    }

    // 5. Printing the result
    temp = head;
    while (temp != NULL) {
        printf("%d%s", temp->data, (temp->next ? " " : ""));
        temp = temp->next;
    }
    printf("\n");

    return 0;
}