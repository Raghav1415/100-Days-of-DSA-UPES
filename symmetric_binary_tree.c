// Problem Statement:
// Check whether a given binary tree is symmetric around its center.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 indicates NULL)

// Output Format:
// - Print YES if symmetric, otherwise NO

// Example:
// Input:
// 7
// 1 2 2 3 4 4 3

// Output:
// YES

// Explanation:
// Left subtree is a mirror image of the right subtree.
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

// Builds tree from level-order array (-1 represents NULL)
Node* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    Node** queue = (Node**)malloc(n * sizeof(Node*));
    if (!queue) exit(EXIT_FAILURE);
    
    Node* root = newNode(arr[0]);
    queue[0] = root;
    int front = 0, rear = 1, i = 1;

    while (i < n && front < rear) {
        Node* curr = queue[front++];
        
        // Assign left child
        if (i < n && arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;
        
        // Assign right child
        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }
    free(queue);
    return root;
}

/**
 * Pure recursive function to check if two trees are structural and data mirrors.
 */
bool isMirror(Node* tree1, Node* tree2) {
    // Base Case 1: Both pointers hit NULL simultaneously. Perfect mirror.
    if (tree1 == NULL && tree2 == NULL) return true;

    // Base Case 2: One pointer hit NULL but the other didn't. Structural mismatch.
    if (tree1 == NULL || tree2 == NULL) return false;

    // Recursive Step: Check current data, then cross-check the subtrees.
    // tree1's LEFT must mirror tree2's RIGHT.
    // tree1's RIGHT must mirror tree2's LEFT.
    return (tree1->data == tree2->data) 
        && isMirror(tree1->left, tree2->right)
        && isMirror(tree1->right, tree2->left);
}

// Wrapper function
bool isSymmetric(Node* root) {
    // An empty tree is inherently symmetric
    if (root == NULL) return true;
    
    // Check if the left and right subtrees are mirrors of each other
    return isMirror(root->left, root->right);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 1;

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node* root = buildTree(arr, n);
    free(arr);

    // Evaluate and output strictly to specification
    if (isSymmetric(root)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    // Reminder: In production, memory must be freed here via a freeTree(root) call.
    return 0;
}