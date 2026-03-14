// Problem: Circular Queue Using Array - Implement using linked list with dynamic memory allocation.

// Input:
// - First line: integer n (number of elements to enqueue)
// - Second line: n space-separated integers
// - Third line: integer m (number of dequeue operations)

// Output:
// - Print queue elements from front to rear after operations, space-separated

// Example:
// Input:
// 5
// 10 20 30 40 50
// 2

// Output:
// 30 40 50 10 20

// Explanation:
// Use array and front/rear pointers. Rear wraps around to start after reaching array end. Dequeue removes elements from front. Display remaining elements in correct order.
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100 // Maximum capacity

void display(int queue[], int front, int rear, int current_size) {
    if (current_size == 0) return;
    
    int i = front;
    for (int count = 0; count < current_size; count++) {
        printf("%d ", queue[i]);
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    int queue[SIZE];
    int front = 0, rear = -1, current_size = 0;
    int n, m, val;

    // Input number of elements to enqueue
    if (scanf("%d", &n) != 1) return 1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        // Enqueue logic
        rear = (rear + 1) % SIZE;
        queue[rear] = val;
        current_size++;
    }

    // Input number of dequeue operations
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        if (current_size > 0) {
            // Dequeue logic: move the front and reduce size
            front = (front + 1) % SIZE;
            current_size--;
        }
    }

    display(queue, front, rear, current_size);

    return 0;
}