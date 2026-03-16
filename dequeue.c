// Problem: Deque (Double-Ended Queue)

// A Deque is a linear data structure that allows insertion and deletion of elements from both the front and the rear. It provides more flexibility than a standard queue or stack.

// Common Operations:
// 1. push_front(value): Insert an element at the front of the deque.
// 2. push_back(value): Insert an element at the rear of the deque.
// 3. pop_front(): Remove an element from the front of the deque.
// 4. pop_back(): Remove an element from the rear of the deque.
// 5. front(): Return the front element of the deque.
// 6. back(): Return the rear element of the deque.
// 7. empty(): Check whether the deque is empty.
// 8. size(): Return the number of elements in the deque.

// Additional Operations:
// - clear(): Remove all elements from the deque.
// - erase(): Remove one or more elements from the deque.
// - swap(): Swap contents of two deques.
// - emplace_front(): Insert an element at the front without copying.
// - emplace_back(): Insert an element at the rear without copying.
// - resize(): Change the size of the deque.
// - assign(): Replace elements with new values.
// - reverse(): Reverse the order of elements.
// - sort(): Sort the elements in ascending order.

// Time Complexity:
// - push_front, push_back, pop_front, pop_back, front, back, empty, size: O(1)
// - clear, erase, resize, assign, reverse: O(n)
// - sort: O(n log n)

// Input:
// - Sequence of deque operations with values (if applicable)

// Output:
// - Results of operations such as front, back, size, or the final state of the deque after all operations
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the Node structure
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Define the Deque structure
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Deque;

// Initialize an empty Deque
Deque* create_deque() {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    if (!dq) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    dq->front = NULL;
    dq->rear = NULL;
    dq->size = 0;
    return dq;
}

// 7. empty()
bool empty(Deque* dq) {
    return dq->size == 0;
}

// 8. size()
int get_size(Deque* dq) {
    return dq->size;
}

// 5. front()
int front(Deque* dq) {
    if (empty(dq)) {
        printf("Deque is empty! No front element.\n");
        return -1; // Error value
    }
    return dq->front->data;
}

// 6. back()
int back(Deque* dq) {
    if (empty(dq)) {
        printf("Deque is empty! No back element.\n");
        return -1; // Error value
    }
    return dq->rear->data;
}

// 1. push_front()
void push_front(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = dq->front;

    if (empty(dq)) {
        dq->rear = newNode;
    } else {
        dq->front->prev = newNode;
    }
    dq->front = newNode;
    dq->size++;
}

// 2. push_back()
void push_back(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = dq->rear;

    if (empty(dq)) {
        dq->front = newNode;
    } else {
        dq->rear->next = newNode;
    }
    dq->rear = newNode;
    dq->size++;
}

// 3. pop_front()
void pop_front(Deque* dq) {
    if (empty(dq)) return;
    
    Node* temp = dq->front;
    dq->front = dq->front->next;
    
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    
    free(temp);
    dq->size--;
}

// 4. pop_back()
void pop_back(Deque* dq) {
    if (empty(dq)) return;
    
    Node* temp = dq->rear;
    dq->rear = dq->rear->prev;
    
    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    
    free(temp);
    dq->size--;
}

// Additional: clear()
void clear(Deque* dq) {
    while (!empty(dq)) {
        pop_front(dq);
    }
    printf("Deque cleared.\n");
}

// The Entry Point
int main() {
    printf("--- Initializing Deque ---\n");
    Deque* myDeque = create_deque();

    printf("\n--- Pushing Elements ---\n");
    push_back(myDeque, 10);      // State: [10]
    push_back(myDeque, 20);      // State: [10, 20]
    push_front(myDeque, 5);      // State: [5, 10, 20]
    push_front(myDeque, 1);      // State: [1, 5, 10, 20]
    
    printf("Pushed 1, 5 to front. Pushed 10, 20 to back.\n");
    printf("Current Size: %d\n", get_size(myDeque));
    printf("Front Element: %d\n", front(myDeque));
    printf("Back Element: %d\n", back(myDeque));

    printf("\n--- Popping Elements ---\n");
    pop_front(myDeque);          // State: [5, 10, 20]
    printf("Popped front element.\n");
    printf("New Front Element: %d\n", front(myDeque));

    pop_back(myDeque);           // State: [5, 10]
    printf("Popped back element.\n");
    printf("New Back Element: %d\n", back(myDeque));
    printf("Current Size: %d\n", get_size(myDeque));

    printf("\n--- Cleaning Up ---\n");
    clear(myDeque);
    
    // Always free the main controller struct at the very end to prevent memory leaks!
    free(myDeque); 
    printf("Memory fully freed. Exiting safely.\n");

    return 0;
}