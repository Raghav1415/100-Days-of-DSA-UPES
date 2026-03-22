// Problem: Count Leaf Nodes

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

// Pure recursive function to count leaves. No global or mutable state.
int countLeaves(Node* root) {
    if (!root) return 0;
    
    if (!root->left && !root->right) return 1;
    
    return countLeaves(root->left) + countLeaves(root->right);
}

int main() {
    /* * Constructing tree:
     * 1
     * /   \
     * 2     3
     * / \   / \
     * 4   5 6   7
     * \
     * 8
     * Leaves should be: 4, 5, 8, 7 (Total: 4)
     */
    
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->right->left->right = newNode(8);

    printf("Total leaf nodes: %d\n", countLeaves(root));

    // Reminder: Production code requires a freeTree(root) call here.
    
    return 0;
}