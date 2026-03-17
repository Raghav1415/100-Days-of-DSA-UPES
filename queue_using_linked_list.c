// Problem Statement:
// Implement a Queue using a linked list supporting enqueue and dequeue operations.

// Input Format:
// - First line contains integer N
// - Next N lines contain queue operations

// Output Format:
// - Print dequeued elements
// - Print -1 if dequeue is attempted on an empty queue
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void initQueue(Queue* q) {
    q->head = q->tail = NULL;
}

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;

    newNode->data = value;
    newNode->next = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = newNode;
        return;
    }

    q->tail->next = newNode;
    q->tail = newNode;
}

int dequeue(Queue* q) {
    if (q->head == NULL) {
        return -1;
    }

    Node* temp = q->head;
    int data = temp->data;

    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(temp);
    return data;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Queue q;
    initQueue(&q);

    while (n--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int val;
            scanf("%d", &val);
            enqueue(&q, val);
        } else if (op == 2) {
            printf("%d\n", dequeue(&q));
        }
    }

    return 0;
}