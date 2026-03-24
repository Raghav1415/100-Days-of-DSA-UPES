// Problem: BST Search

// Implement the solution for this problem.

// Input:
// - Input specifications

// Output:
// - Output specifications
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Standard memory allocation helper
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Searches for a target value in a BST iteratively.
 * Returns the pointer to the node if found, otherwise NULL.
 */
Node* search(Node* root, int target) {
    Node* current = root; // Start at the top

    while (current != NULL) {
        if (current->data == target) {
            return current; // Match found
        } 
        
        if (target < current->data) {
            current = current->left; // Target is smaller, go left
        } else {
            current = current->right; // Target is larger, go right
        }
    }

    return NULL; // We hit a dead end, target does not exist
}

int main() {
    /* Constructing the following BST:
     * 50
     * /  \
     * 30    70
     * /  \  /  \
     * 20   40 60  80
     */
    Node* root = newNode(50);
    root->left = newNode(30);
    root->right = newNode(70);
    root->left->left = newNode(20);
    root->left->right = newNode(40);
    root->right->left = newNode(60);
    root->right->right = newNode(80);

    int target1 = 60;
    Node* result1 = search(root, target1);
    if (result1) {
        printf("Found: %d\n", result1->data);
    } else {
        printf("Target %d not found.\n", target1);
    }

    int target2 = 99;
    Node* result2 = search(root, target2);
    if (result2) {
        printf("Found: %d\n", result2->data);
    } else {
        printf("Target %d not found.\n", target2);
    }

    // Reminder: Implement freeTree(root) in production.
    return 0;
}