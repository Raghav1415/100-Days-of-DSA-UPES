// Problem: Count Occurrences of an Element in Linked List - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n (number of nodes)
// - Second line: n space-separated integers (linked list elements)
// - Third line: integer key (element to be counted)

// Output:
// - Print the number of times the key appears in the linked list

// Example:
// Input:
// 6
// 10 20 30 20 40 20
// 20

// Output:
// 3

// Explanation:
// Traverse the linked list from head to end. Each time a node's data matches the given key, increment a counter. After traversal, print the final count.
#include <stdio.h>
#include <stdlib.h>

// Defining the structure of a single node
struct Node {
    int data;
    struct Node* next;
};

// Function to add a new node at the end of the list
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

int main() {
    int n, val, key, count = 0;
    struct Node* head = NULL;

    // Input: Number of elements
    if (scanf("%d", &n) != 1) return 0;

    // Input: n integers
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        append(&head, val);
    }

    // Input: Key to search
    scanf("%d", &key);

    // Traversal and counting
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            count++;
        }
        current = current->next;
    }

    printf("%d\n", count);

    // Memory Cleanup (Crucial in C!)
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
