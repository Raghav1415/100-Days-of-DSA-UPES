// Problem Statement:
// Perform zigzag (spiral) level order traversal of a binary tree. Alternate levels should be traversed left-to-right and right-to-left.

// Input Format:
// - First line contains integer N
// - Second line contains level-order traversal (-1 indicates NULL)

// Output Format:
// - Print traversal in zigzag order

// Example:
// Input:
// 7
// 1 2 3 4 5 6 7

// Output:
// 1 3 2 4 5 6 7

// Explanation:
// Level 1 is printed left-to-right, level 2 right-to-left, and so on.
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
 * Prints the zigzag level order traversal in true O(N) time.
 * Utilizes two stacks and a direction flag to inherently reverse levels.
 */
void zigzagTraversal(Node* root, int n) {
    if (!root) return;

    // The maximum width of a binary tree is (N+1)/2. 
    // Sizing the stacks to N guarantees we never overflow.
    Node** currentLevel = (Node**)malloc(n * sizeof(Node*));
    Node** nextLevel = (Node**)malloc(n * sizeof(Node*));
    
    int currTop = -1;
    int nextTop = -1;

    bool leftToRight = true;

    // Initialize the first stack with the root
    currentLevel[++currTop] = root;

    while (currTop >= 0) {
        // Pop the top node from the current level
        Node* currNode = currentLevel[currTop--];
        printf("%d ", currNode->data);

        // Push children into the next level stack.
        // The order we push dictates the reverse pop order on the next iteration.
        if (leftToRight) {
            if (currNode->left) nextLevel[++nextTop] = currNode->left;
            if (currNode->right) nextLevel[++nextTop] = currNode->right;
        } else {
            if (currNode->right) nextLevel[++nextTop] = currNode->right;
            if (currNode->left) nextLevel[++nextTop] = currNode->left;
        }

        // When the current level is exhausted, transition to the next level
        if (currTop == -1) {
            leftToRight = !leftToRight; // Flip the direction
            
            // Fast Pointer Swap (O(1) operation) instead of copying arrays
            Node** temp = currentLevel;
            currentLevel = nextLevel;
            nextLevel = temp;
            
            // Transfer the stack size
            currTop = nextTop;
            nextTop = -1;
        }
    }

    // Clean up
    free(currentLevel);
    free(nextLevel);
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

    zigzagTraversal(root, n);

    // Reminder: Tree memory should be freed via a recursive freeTree(root) call.
    return 0;
}