// Problem Statement:
// Construct a Binary Tree from the given level-order traversal.

// Input Format:
// - First line contains integer N
// - Second line contains N space-separated integers (-1 represents NULL)

// Output Format:
// - Print inorder traversal of the constructed tree

// Example:
// Input:
// 7
// 1 2 3 4 5 -1 6

// Output:
// 4 2 5 1 3 6y
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

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void buildTree() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return;

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    Node* root = newNode(arr[0]);
    if (!root) return;

    Node** queue = (Node**)malloc(n * sizeof(Node*));
    int head = 0, tail = 0;
    queue[tail++] = root;

    int i = 1;
    while (i < n && head < tail) {
        Node* parent = queue[head++];

        if (i < n) {
            parent->left = newNode(arr[i++]);
            if (parent->left) queue[tail++] = parent->left;
        }
        if (i < n) {
            parent->right = newNode(arr[i++]);
            if (parent->right) queue[tail++] = parent->right;
        }
    }

    inorder(root);
    printf("\n");
    free(arr);
    free(queue);
}

int main() {
    buildTree();
    return 0;
}