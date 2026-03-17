// Problem Statement:
// Implement a Min Heap using an array where the smallest element is always at the root.

// Supported Operations:
// - insert x
// - extractMin
// - peek

// Input Format:
// - First line contains integer N
// - Next N lines contain heap operations

// Output Format:
// - Print results of extractMin and peek
// - Print -1 if operation cannot be performed

// Example:
// Input:
// 6
// insert 40
// insert 10
// insert 30
// peek
// extractMin
// peek

// Output:
// 10
// 10
// 30
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Moves a newly inserted element up to its correct position
void heapifyUp(MinHeap *h, int index) {
    while (index > 0 && h->data[(index - 1) / 2] > h->data[index]) {
        swap(&h->data[(index - 1) / 2], &h->data[index]);
        index = (index - 1) / 2;
    }
}

// Moves the root element down to restore heap property
void heapifyDown(MinHeap *h, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->size && h->data[left] < h->data[smallest])
        smallest = left;
    if (right < h->size && h->data[right] < h->data[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&h->data[index], &h->data[smallest]);
        heapifyDown(h, smallest);
    }
}

void insert(MinHeap *h, int x) {
    if (h->size == h->capacity) return; // In a real project, we'd realloc here
    h->data[h->size] = x;
    heapifyUp(h, h->size);
    h->size++;
}

int peek(MinHeap *h) {
    if (h->size <= 0) return -1;
    return h->data[0];
}

int extractMin(MinHeap *h) {
    if (h->size <= 0) return -1;
    int root = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return root;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    MinHeap h;
    h.capacity = N; 
    h.size = 0;
    h.data = (int *)malloc(N * sizeof(int));

    char op[20];
    for (int i = 0; i < N; i++) {
        scanf("%s", op);
        if (op[0] == 'i') { // insert
            int val;
            scanf("%d", &val);
            insert(&h, val);
        } else if (op[0] == 'e') { // extractMin
            printf("%d\n", extractMin(&h));
        } else if (op[0] == 'p') { // peek
            printf("%d\n", peek(&h));
        }
    }

    free(h.data);
    return 0;
}