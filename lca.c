// Problem Statement:
// Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree.

// Input Format:
// - First line contains integer N
// - Second line contains N space-separated integers
// - Third line contains two node values

// Output Format:
// - Print the LCA value

// Example:
// Input:
// 7
// 6 2 8 0 4 7 9
// 2 8

// Output:
// 6
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Standard memory allocation helper with safety check
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

// Standard BST Insert 
Node* insert(Node* root, int data) {
    if (root == NULL) return newNode(data);

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

/**
 * Finds the Lowest Common Ancestor of two nodes in a BST.
 * Operates in O(1) auxiliary space and O(H) time.
 */
Node* findLCA(Node* root, int n1, int n2) {
    while (root != NULL) {
        // If both values are less than the current node, the LCA must be strictly to the left.
        if (root->data > n1 && root->data > n2) {
            root = root->left;
        }
        // If both values are greater than the current node, the LCA must be strictly to the right.
        else if (root->data < n1 && root->data < n2) {
            root = root->right;
        }
        // We have found the split point (or one of the targets IS the current node).
        // This is mathematically guaranteed to be the Lowest Common Ancestor.
        else {
            break;
        }
    }
    return root;
}

int main() {
    int n;
    // Read the number of nodes
    if (scanf("%d", &n) != 1) return 1;

    Node* root = NULL;
    
    // Read the space-separated integers and build the BST
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    int n1, n2;
    // Read the two target nodes for the LCA search
    if (scanf("%d %d", &n1, &n2) != 2) return 1;

    // Find and print the LCA
    Node* lca = findLCA(root, n1, n2);
    if (lca != NULL) {
        printf("%d\n", lca->data);
    }

    // Reminder: In production, memory must be freed here via a freeTree(root) call.
    return 0;
}