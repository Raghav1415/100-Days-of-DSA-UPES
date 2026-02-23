// Problem: Count Nodes in Linked List

// Input:
// - First line: integer n
// - Second line: n space-separated integers

// Output:
// - Print the result

// Example:
// Input:
// 5
// 10 20 30 40 50

// Output:
// 10 20 30 40 50
#include <stdio.h>
#include <stdlib.h>

// Defining the node structure
struct node {
    int data;               // [cite: 16]
    struct node *link;      // 
};

// Global head pointer
struct node* head = NULL;

// Function to create a node and insert it at the end
void insertEnd(int val) {
    struct node* pNew = (struct node*)malloc(sizeof(struct node));
    if (pNew == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    pNew->data = val;
    pNew->link = NULL;

    if (head == NULL) {
        head = pNew;
        return;
    }

    struct node* temp = head;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    temp->link = pNew;
}

// Function to display the list (Matches your example output)
void displayList() {
    if (head == NULL) {
        return; 
    }
    struct node* temp = head;       // 
    while (temp != NULL) {          // 
        printf("%d ", temp->data);  // 
        temp = temp->link;          // 
    }
    printf("\n");
}

// Function to count the nodes (Matches your problem title)
int countNodes() {
    int count = 0;                  // 
    struct node* temp = head;       // 
    
    while (temp != NULL) {          // 
        count = count + 1;          // 
        temp = temp->link;          // 
    }
    return count;                   // 
}

int main() {
    int n, value;

    // Read the number of elements
    if (scanf("%d", &n) != 1) return 1;

    // Read the elements and build the list
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        insertEnd(value);
    }

    // Print the elements exactly as requested in your Example Output
    displayList();

    // Actually solving the title's problem
    int total_nodes = countNodes();
    // printf("Total Nodes: %d\n", total_nodes); // Uncomment to print the count

    return 0;
}