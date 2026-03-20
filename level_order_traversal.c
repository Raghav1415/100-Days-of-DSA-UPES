// Problem: Level Order Traversal

// Implement the solution for this problem.

// Input:
// - Input specifications

// Output:
// - Output specifications
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue node for BFS
typedef struct QNode {
    Node* treeNode;
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode *front, *rear;
} Queue;

// Function prototypes
Node* newNode(int data);
void levelOrder(Node* root);
void enqueue(Queue* q, Node* treeNode);
Node* dequeue(Queue* q);

void levelOrder(Node* root) {
    if (!root) return;

    Queue q = {NULL, NULL};
    enqueue(&q, root);

    while (q.front != NULL) {
        Node* current = dequeue(&q);
        printf("%d ", current->data);

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }
}

// Minimalist main for demonstration
int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("Level Order Traversal: ");
    levelOrder(root);
    return 0;
}