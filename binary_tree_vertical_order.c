// Problem Statement:
// Given a binary tree, print its vertical order traversal. Nodes that lie on the same vertical line should be printed together from top to bottom and from left to right.

// Input Format:
// - First line contains integer N (number of nodes)
// - Second line contains N space-separated integers representing level-order traversal (-1 indicates NULL)

// Output Format:
// - Print nodes column by column from leftmost to rightmost vertical line

// Example:
// Input:
// 7
// 1 2 3 4 5 6 7

// Output:
// 4
// 2
// 1 5 6
// 3
// 7

// Explanation:
// Vertical lines are formed based on horizontal distance from root. Nodes sharing the same distance are printed together.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// A linked list node to group tree nodes sharing the same Vertical Column (HD)
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// A queue node for our BFS that tracks the Tree Node AND its Horizontal Distance
typedef struct QNode {
    Node* treeNode;
    int hd;
} QNode;

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
 * Prints the vertical order traversal in O(N) time.
 * Uses a shifted array to handle negative Horizontal Distances.
 */
void printVerticalOrder(Node* root, int n) {
    if (!root) return;

    // In the absolute worst-case skewed tree, HD ranges from -N to +N.
    // We create arrays of size 2N + 1 to act as our "Hash Map".
    int mapSize = 2 * n + 1;
    int offset = n; // Offset shifts HD=0 to index N.

    ListNode** head = (ListNode**)calloc(mapSize, sizeof(ListNode*));
    ListNode** tail = (ListNode**)calloc(mapSize, sizeof(ListNode*));

    // Array-based Queue for BFS
    QNode* queue = (QNode*)malloc(n * sizeof(QNode));
    int front = 0, rear = 0;

    int min_hd = offset;
    int max_hd = offset;

    // Enqueue the root at HD = 0 (which maps to index 'offset')
    queue[rear++] = (QNode){root, offset};

    while (front < rear) {
        QNode current = queue[front++];
        Node* node = current.treeNode;
        int hd = current.hd;

        // Track our actual boundaries to avoid printing empty arrays later
        if (hd < min_hd) min_hd = hd;
        if (hd > max_hd) max_hd = hd;

        // Create a new list node for the current Tree Node
        ListNode* ln = (ListNode*)malloc(sizeof(ListNode));
        ln->data = node->data;
        ln->next = NULL;

        // Append to the list for this specific HD
        if (head[hd] == NULL) {
            head[hd] = ln;
            tail[hd] = ln;
        } else {
            tail[hd]->next = ln; // O(1) insertion at the end
            tail[hd] = ln;
        }

        // Enqueue children with updated HDs
        if (node->left) {
            queue[rear++] = (QNode){node->left, hd - 1};
        }
        if (node->right) {
            queue[rear++] = (QNode){node->right, hd + 1};
        }
    }

    // Print the columns from leftmost (min_hd) to rightmost (max_hd)
    for (int i = min_hd; i <= max_hd; i++) {
        ListNode* curr = head[i];
        while (curr != NULL) {
            printf("%d ", curr->data);
            ListNode* temp = curr;
            curr = curr->next;
            free(temp); // Clean up the list node
        }
        printf("\n");
    }

    free(head);
    free(tail);
    free(queue);
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

    printVerticalOrder(root, n);

    // Reminder: Tree memory (the actual Nodes) should be freed here via freeTree(root)
    return 0;
}