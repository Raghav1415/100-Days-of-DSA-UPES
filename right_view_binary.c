// Problem Statement:
// Print the nodes visible when the binary tree is viewed from the right side.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 indicates NULL)

// Output Format:
// - Print right view nodes

// Example:
// Input:
// 7
// 1 2 3 4 5 -1 6

// Output:
// 1 3 6

// Explanation:
// At each level, the rightmost node is visible from the right view.
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
    if (!node) exit(EXIT_FAILURE);
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Builds tree from level-order array (-1 represents NULL)
Node* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    Node** queue = (Node**)malloc(n * sizeof(Node*));
    Node* root = newNode(arr[0]);
    queue[0] = root;
    int front = 0, rear = 1, i = 1;

    while (i < n && front < rear) {
        Node* curr = queue[front++];
        
        // Left child
        if (i < n && arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;
        
        // Right child
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
 * Core DFS logic for Right View.
 * We visit ROOT -> RIGHT -> LEFT.
 */
void rightViewUtil(Node* root, int current_level, int* max_level) {
    if (root == NULL) return;

    // If this is the first time we've reached this level, it MUST be the rightmost node
    if (current_level > *max_level) {
        printf("%d ", root->data);
        *max_level = current_level; // Update the watermark
    }

    // Crucial: Explore the RIGHT subtree first!
    rightViewUtil(root->right, current_level + 1, max_level);
    
    // Then explore the LEFT subtree
    rightViewUtil(root->left, current_level + 1, max_level);
}

// Wrapper function to initialize state
void printRightView(Node* root) {
    int max_level = 0; // Tracks the deepest level we've printed so far
    rightViewUtil(root, 1, &max_level);
    printf("\n");
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

    // Print the right view
    printRightView(root);

    // Reminder: In production, memory must be freed here via a freeTree(root) call.
    return 0;
}