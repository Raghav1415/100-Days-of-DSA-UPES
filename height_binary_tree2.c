// Problem: Height of Binary Tree

// Implement the solution for this problem.

// Input:
// - Input specifications

// Output:
// - Output specifications
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Allocates a new node and handles potential out-of-memory errors
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

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calculates height based on edges. Root only = 0. Empty = -1.
int getHeight(Node* root) {
    if (!root) return -1; 
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int main() {
    /* * Constructing the following sample tree:
     * 1
     * / \
     * 2   3
     * / \
     * 4   5
     * /
     * 6
     */
    
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->left->left->left = newNode(6);

    // The longest path is 1 -> 2 -> 4 -> 6 (3 edges)
    printf("Height of the tree (edges): %d\n", getHeight(root));

    // Note: A production-grade program must recursively free() this memory 
    // before exiting to prevent memory leaks.
    
    return 0;
}