// Problem: Polynomial Using Linked List - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n (number of terms)
// - Next n lines: two integers (coefficient and exponent)

// Output:
// - Print polynomial in standard form, e.g., 10x^4 + 20x^3 + 30x^2 + 40x + 50

// Example:
// Input:
// 5
// 10 4
// 20 3
// 30 2
// 40 1
// 50 0

// Output:
// 10x^4 + 20x^3 + 30x^2 + 40x + 50

// Explanation:
// Each node stores coefficient and exponent. Traverse nodes to print polynomial in decreasing exponent order.
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int pow;
    struct Node* next;
};

// Function to create and link a new term
struct Node* createNode(int c, int p) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return NULL;
    newNode->coeff = c;
    newNode->pow = p;
    newNode->next = NULL;
    return newNode;
}

void displayPolynomial(struct Node* ptr) {
    int isFirst = 1; 

    while (ptr != NULL) {
        // Handle signs for non-first terms
        if (!isFirst && ptr->coeff > 0) {
            printf(" + ");
        } else if (ptr->coeff < 0) {
            printf(" - ");
        }

        // Print coefficient (absolute value if not first)
        int absCoeff = (ptr->coeff < 0) ? -ptr->coeff : ptr->coeff;
        
        if (ptr->pow == 0) {
            printf("%d", absCoeff);
        } else if (ptr->pow == 1) {
            printf("%dx", absCoeff);
        } else {
            printf("%dx^%d", absCoeff, ptr->pow);
        }

        ptr = ptr->next;
        isFirst = 0;
    }
    printf("\n");
}

int main() {
    int n, c, p;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    struct Node *head = NULL, *tail = NULL;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &c, &p);
        struct Node* newNode = createNode(c, p);
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    displayPolynomial(head);

    // Clean up memory (The "Pro" move)
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}