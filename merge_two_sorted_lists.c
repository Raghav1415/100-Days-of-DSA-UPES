// Problem: Merge Two Sorted Linked Lists - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n
// - Second line: n space-separated integers (first list)
// - Third line: integer m
// - Fourth line: m space-separated integers (second list)

// Output:
// - Print the merged linked list elements, space-separated

// Example:
// Input:
// 5
// 10 20 30 40 50
// 4
// 15 25 35 45

// Output:
// 10 15 20 25 30 35 40 45 50

// Explanation:
// Compare nodes of both lists, append smaller to result, continue until all nodes are merged.
#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node in the heap
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to merge two sorted lists
struct Node* mergeSortedLists(struct Node* l1, struct Node* l2) {
    // Create a dummy node to act as the starting point
    struct Node dummy;
    struct Node* tail = &dummy;
    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Attach the remaining nodes of whichever list is not empty
    tail->next = (l1 != NULL) ? l1 : l2;

    return dummy.next;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    int n, m, val;
    struct Node *list1 = NULL, *list2 = NULL, *temp = NULL;

    // Input for first list
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        struct Node* newNode = createNode(val);
        if (list1 == NULL) {
            list1 = newNode;
            temp = list1;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }

    // Input for second list
    if (scanf("%d", &m) != 1) return 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &val);
        struct Node* newNode = createNode(val);
        if (list2 == NULL) {
            list2 = newNode;
            temp = list2;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }

    struct Node* mergedHead = mergeSortedLists(list1, list2);
    printList(mergedHead);

    return 0;
}