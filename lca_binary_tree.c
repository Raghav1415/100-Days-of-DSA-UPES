// Problem Statement:
// Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Tree.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 represents NULL)
// - Third line contains two node values

// Output Format:
// - Print the LCA value

// Example:
// Input:
// 7
// 1 2 3 4 5 6 7
// 4 5

// Output:
// 2
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

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

// Utility function that traverses and sets boolean flags when nodes are found
Node* findLCAUtil(Node* root, int n1, int n2, bool* v1, bool* v2) {
    if (root == NULL) return NULL;

    // Send scouts down first (Post-order)
    Node* left_lca  = findLCAUtil(root->left, n1, n2, v1, v2);
    Node* right_lca = findLCAUtil(root->right, n1, n2, v1, v2);

    // If this node IS one of the targets, flag it.
    if (root->data == n1) {
        *v1 = true;
        return root;
    }
    if (root->data == n2) {
        *v2 = true;
        return root;
    }

    // If both left and right returned a target, THIS is the LCA.
    if (left_lca != NULL && right_lca != NULL) return root;

    // Otherwise, pass up whatever we found.
    return (left_lca != NULL) ? left_lca : right_lca;
}

// Secondary verification function
bool isNodePresent(Node* root, int target) {
    if (root == NULL) return false;
    if (root->data == target) return true;
    return isNodePresent(root->left, target) || isNodePresent(root->right, target);
}

// Main Wrapper Function
Node* findLCA(Node* root, int n1, int n2) {
    bool v1 = false, v2 = false;
    
    // Step 1: Find the potential LCA and populate our boolean flags
    Node* lca = findLCAUtil(root, n1, n2, &v1, &v2);

    // Step 2: Verification
    // Case A: Both nodes were explicitly found in separate branches.
    if (v1 && v2) return lca;

    // Case B: n1 was found, but n2 wasn't. Check if n2 is hiding under n1.
    if (v1 && !v2 && isNodePresent(lca, n2)) return lca;

    // Case C: n2 was found, but n1 wasn't. Check if n1 is hiding under n2.
    if (v2 && !v1 && isNodePresent(lca, n1)) return lca;

    // Case D: One or both nodes do not exist in the tree.
    return NULL; 
}

int main() {
    int n;
    // Read total nodes
    if (scanf("%d", &n) != 1) return 1;

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 1;

    // Read level-order traversal
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node* root = buildTree(arr, n);
    free(arr); 

    int n1, n2;
    // Read the two target nodes
    if (scanf("%d %d", &n1, &n2) != 2) return 1;

    Node* lca = findLCA(root, n1, n2);
    
    // Strict output formatting
    if (lca != NULL) {
        printf("%d\n", lca->data);
    } else {
        printf("One or both nodes missing. LCA not found.\n");
    }

    return 0;
}