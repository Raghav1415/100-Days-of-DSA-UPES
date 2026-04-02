// Problem Statement:
// Construct a binary tree from given inorder and postorder traversal arrays.

// Input Format:
// - First line contains integer N
// - Second line contains inorder traversal
// - Third line contains postorder traversal

// Output Format:
// - Print preorder traversal of constructed tree

// Example:
// Input:
// 5
// 4 2 5 1 3
// 4 5 2 3 1

// Output:
// 1 2 4 5 3

// Explanation:
// Postorder gives root at end, inorder divides left and right subtrees.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Standard memory allocation helper with safety abort
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

// Utility function to find the index of a value in the inorder array
int searchInorder(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1; // Fallback for invalid inputs
}

/**
 * Core Algorithm: Reconstructs the tree from Inorder and Postorder.
 * CRITICAL: postIndex is passed by reference to maintain global state.
 */
Node* buildTreeUtil(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    // Base case: Subtree is empty
    if (inStart > inEnd) return NULL;

    // Pick the current node from Postorder traversal (reading right-to-left)
    // Dereference happens first, then we post-decrement the pointer.
    Node* tNode = newNode(postorder[(*postIndex)--]);

    // Optimization: If this node has no children, return immediately
    if (inStart == inEnd) return tNode;

    // Find the boundary index in the Inorder traversal
    int inIndex = searchInorder(inorder, inStart, inEnd, tNode->data);

    // CRITICAL TRAP AVOIDANCE: You MUST build the RIGHT subtree first!
    // Because we are reading Postorder backwards, the next element is in the right branch.
    tNode->right = buildTreeUtil(inorder, postorder, inIndex + 1, inEnd, postIndex);
    
    // Once the entire right branch is built, the postIndex will be correctly 
    // positioned to start building the left branch.
    tNode->left = buildTreeUtil(inorder, postorder, inStart, inIndex - 1, postIndex);

    return tNode;
}

// Wrapper function to initialize the postIndex pointer
Node* buildTree(int inorder[], int postorder[], int n) {
    int postIndex = n - 1; // Start at the absolute end of the Postorder array
    return buildTreeUtil(inorder, postorder, 0, n - 1, &postIndex);
}

// Target output: Preorder traversal (Root, Left, Right)
void printPreorder(Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

// Memory Management: Prevent heap leaks
void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    int n;
    // Read total number of nodes
    if (scanf("%d", &n) != 1) return 1;

    int* inorder = (int*)malloc(n * sizeof(int));
    int* postorder = (int*)malloc(n * sizeof(int));
    if (!inorder || !postorder) exit(EXIT_FAILURE);

    // Read the inorder array
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    // Read the postorder array
    for (int i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }

    // Reconstruct the tree
    Node* root = buildTree(inorder, postorder, n);

    // Print the requested Preorder sequence
    printPreorder(root);
    printf("\n");

    // Clean up heap allocations
    freeTree(root);
    free(inorder);
    free(postorder);

    return 0;
}