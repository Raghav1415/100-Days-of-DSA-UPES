// Problem Statement:
// Given a queue of integers, reverse the queue using a stack.

// Input Format:
// - First line contains integer N
// - Second line contains N space-separated integers

// Output Format:
// - Print the reversed queue

// Example:
// Input:
// 5
// 10 20 30 40 50

// Output:
// 50 40 30 20 10
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node *front, *rear;
} Queue;

typedef struct {
    int* items;
    int top;
    int capacity;
} Stack;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(Queue* q) {
    if (q->front == NULL) return -1;
    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return data;
}

void initStack(Stack* s, int capacity) {
    s->capacity = capacity;
    s->top = -1;
    s->items = (int*)malloc(capacity * sizeof(int));
}

void push(Stack* s, int value) {
    s->items[++(s->top)] = value;
}

int pop(Stack* s) {
    return s->items[(s->top)--];
}

void reverseQueue(Queue* q, int n) {
    Stack s;
    initStack(&s, n);
    while (q->front != NULL) {
        push(&s, dequeue(q));
    }
    while (s.top != -1) {
        enqueue(q, pop(&s));
    }
    free(s.items);
}

void printQueue(Queue* q) {
    Node* temp = q->front;
    while (temp) {
        printf("%d%s", temp->data, temp->next ? " " : "");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n, val;
    if (scanf("%d", &n) != 1) return 1;
    Queue q;
    initQueue(&q);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &val) == 1) enqueue(&q, val);
    }
    reverseQueue(&q, n);
    printQueue(&q);
    return 0;
}