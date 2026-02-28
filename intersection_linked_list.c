// Problem: Find Intersection Point of Two Linked Lists - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n
// - Second line: n space-separated integers (first list)
// - Third line: integer m
// - Fourth line: m space-separated integers (second list)

// Output:
// - Print value of intersection node or 'No Intersection'

// Example:
// Input:
// 5
// 10 20 30 40 50
// 4
// 15 25 30 40 50

// Output:
// 30

// Explanation:
// Calculate lengths, advance pointer in longer list, traverse both simultaneously. First common node is intersection.
#include <stdio.h>
#include <stdlib.h>

// Defining the structure of our building block
struct Node {
    int data;
    struct Node* next;
};

// Helper to create a new node in memory
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return NULL;
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

// Function to find intersection point
void findIntersection(struct Node* head1, struct Node* head2) {
    struct Node *ptr1 = head1, *ptr2 = head2;
    int len1 = 0, len2 = 0;

    // 1. Calculate lengths
    while (ptr1) { len1++; ptr1 = ptr1->next; }
    while (ptr2) { len2++; ptr2 = ptr2->next; }

    ptr1 = head1;
    ptr2 = head2;

    // 2. Adjust for the difference in length
    int diff = abs(len1 - len2);
    if (len1 > len2) {
        for (int i = 0; i < diff; i++) ptr1 = ptr1->next;
    } else {
        for (int i = 0; i < diff; i++) ptr2 = ptr2->next;
    }

    // 3. Traverse together until they meet
    while (ptr1 && ptr2) {
        if (ptr1->data == ptr2->data) {
            printf("%d\n", ptr1->data);
            return;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    printf("No Intersection\n");
}

int main() {
    int n, m, val;
    struct Node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL;

    // Input first list
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        struct Node* newNode = createNode(val);
        if (!head1) head1 = newNode;
        else tail1->next = newNode;
        tail1 = newNode;
    }

    // Input second list
    if (scanf("%d", &m) != 1) return 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &val);
        struct Node* newNode = createNode(val);
        if (!head2) head2 = newNode;
        else tail2->next = newNode;
        tail2 = newNode;
    }

    findIntersection(head1, head2);

    return 0;
}