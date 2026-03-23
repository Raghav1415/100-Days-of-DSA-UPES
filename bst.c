// Problem: BST Insert

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

// Recursive BST Insert. Returns the (potentially updated) root pointer.
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Note: If data == root->data, we do nothing (no duplicates allowed in standard BST)

    return root;
}

// Helper to verify our tree via In-Order Traversal (prints sorted)
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    Node* root = NULL;

    /* Inserting data: 50, 30, 20, 40, 70, 60, 80 */
    root = insert(root, 50); // The first insert captures the actual root
    
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("In-Order Traversal of the BST: ");
    inOrder(root);
    printf("\n");

    // Reminder: In production, always implement and call freeTree(root).
    return 0;
}