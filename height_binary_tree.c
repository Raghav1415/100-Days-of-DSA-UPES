// Problem Statement:
// Find the height (maximum depth) of a given binary tree.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 represents NULL)

// Output Format:
// - Print the height of the tree

// Example:
// Input:
// 7
// 1 2 3 4 5 -1 -1

// Output:
// 3

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* newNode(int val) {
    if (val == -1) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

int getHeight(Node* root) {
    if (!root) return 0;
    int l = getHeight(root->left);
    int r = getHeight(root->right);
    return (l > r ? l : r) + 1;
}

Node* buildTree(int n, int* arr) {
    if (n == 0 || arr[0] == -1) return NULL;
    Node* root = newNode(arr[0]);
    Node** queue = (Node**)malloc(n * sizeof(Node*));
    int head = 0, tail = 0;
    queue[tail++] = root;
    int i = 1;
    while (i < n && head < tail) {
        Node* curr = queue[head++];
        if (i < n) {
            curr->left = newNode(arr[i++]);
            if (curr->left) queue[tail++] = curr->left;
        }
        if (i < n) {
            curr->right = newNode(arr[i++]);
            if (curr->right) queue[tail++] = curr->right;
        }
    }
    free(queue);
    return root;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    Node* root = buildTree(n, arr);
    printf("%d\n", getHeight(root));
    free(arr);
    return 0;
}