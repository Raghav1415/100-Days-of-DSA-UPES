// Problem Statement:
// Convert a binary tree into its mirror image by swapping left and right children at every node.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 indicates NULL)

// Output Format:
// - Print inorder traversal of mirrored tree

// Example:
// Input:
// 7
// 1 2 3 4 5 6 7

// Output:
// 7 3 6 1 5 2 4

// Explanation:
// Each node’s left and right children are swapped recursively.
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
        
        if (i < n && arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;
        
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
 * Core Algorithm: Inverts the binary tree in-place.
 * Time Complexity: O(N), Space Complexity: O(H) for call stack.
 */
void mirrorTree(Node* root) {
    if (root == NULL) {
        return; // Base case: hit the bottom
    }

    // Step 1: The Address Swap
    // We physically swap the memory addresses held in the left and right pointers.
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Step 2: The Descent (Pre-Order)
    // Now we traverse down what IS CURRENTLY the left and right branches.
    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Standard In-Order Traversal (Left, Root, Right)
void printInOrder(Node* root) {
    if (root == NULL) return;
    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

// Crucial Memory Management: Post-Order deletion
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    // Read total number of nodes
    if (scanf("%d", &n) != 1) return 1;

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 1;

    // Read the array
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Build the initial tree
    Node* root = buildTree(arr, n);
    free(arr);

    // Perform the in-place mirroring
    mirrorTree(root);

    // Output the results strictly as requested
    printInOrder(root);
    printf("\n");

    // Clean up the heap
    freeTree(root);

    return 0;
}