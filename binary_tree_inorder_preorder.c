// Problem Statement:
// Construct a binary tree from given preorder and inorder traversal arrays.

// Input Format:
// - First line contains integer N
// - Second line contains preorder traversal
// - Third line contains inorder traversal

// Output Format:
// - Print postorder traversal of constructed tree

// Example:
// Input:
// 5
// 1 2 4 5 3
// 4 2 5 1 3

// Output:
// 4 5 2 3 1

// Explanation:
// Preorder identifies root, inorder splits left and right subtrees.
#include <stdio.h>
#include <stdlib.h>

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

// Utility function to find the index of a value in the inorder array
// Note: In a true production C environment, replace this with a Hash Table lookup for O(N) overall time.
int searchInorder(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1; // Should never be reached if input arrays are valid
}

/**
 * Core Algorithm: Reconstructs the tree.
 * Notice that preIndex is a POINTER. This is mandatory.
 */
Node* buildTreeUtil(int inorder[], int preorder[], int inStart, int inEnd, int* preIndex) {
    // Base case: If the start index exceeds the end index, this subtree is empty.
    if (inStart > inEnd) return NULL;

    // Pick the current node from Preorder traversal using preIndex and increment it.
    // The dereference (*) happens before the post-increment (++).
    Node* tNode = newNode(preorder[(*preIndex)++]);

    // If this node has no children (it's a leaf), return it immediately to save search time.
    if (inStart == inEnd) return tNode;

    // Else find the index of this node in the Inorder traversal.
    int inIndex = searchInorder(inorder, inStart, inEnd, tNode->data);

    // Using the index, construct the left and right subtrees.
    // LEFT subtree uses elements strictly to the left of inIndex.
    tNode->left = buildTreeUtil(inorder, preorder, inStart, inIndex - 1, preIndex);
    
    // RIGHT subtree uses elements strictly to the right of inIndex.
    tNode->right = buildTreeUtil(inorder, preorder, inIndex + 1, inEnd, preIndex);

    return tNode;
}

// Wrapper function to initialize the preIndex pointer
Node* buildTree(int inorder[], int preorder[], int n) {
    int preIndex = 0;
    return buildTreeUtil(inorder, preorder, 0, n - 1, &preIndex);
}

// Target output: Post-order traversal (Left, Right, Root)
void printPostorder(Node* node) {
    if (node == NULL) return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->data);
}

// Crucial Memory Management
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

    int* preorder = (int*)malloc(n * sizeof(int));
    int* inorder = (int*)malloc(n * sizeof(int));
    if (!preorder || !inorder) exit(EXIT_FAILURE);

    // Read the preorder array
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

    // Read the inorder array
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    // Reconstruct the tree
    Node* root = buildTree(inorder, preorder, n);

    // Print the requested Postorder sequence
    printPostorder(root);
    printf("\n");

    // Clean up all allocated heap memory
    freeTree(root);
    free(preorder);
    free(inorder);

    return 0;
}