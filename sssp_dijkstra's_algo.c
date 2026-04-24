// Problem Statement
// Find shortest distances from source vertex in a weighted graph with non-negative weights.

// Input Format
// n m
// u v w
// source

// Output Format
// Distances to all vertices.

// Sample Input
// 5 6
// 1 2 2
// 1 3 4
// 2 3 1
// 2 4 7
// 3 5 3
// 4 5 1
// 1

// Sample Output
// 0 2 3 9 6

// Explanation
// Shortest distances computed via priority queue.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- Graph Infrastructure (Strictly Directed) ---
typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** adjLists;
} Graph;

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    // +1 to safely accommodate 1-based indexing
    graph->adjLists = (Node**)calloc(V + 1, sizeof(Node*));
    return graph;
}

void addDirectedEdge(Graph* graph, int src, int dest, int weight) {
    // The Trap Avoidance: We only insert the edge one way
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// --- Custom Min-Heap Infrastructure (O(1) lookups) ---
typedef struct MinHeapNode {
    int v;
    int dist;
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int* pos; 
    MinHeapNode** array;
} MinHeap;

MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc((capacity + 1) * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    // Array holds elements 0 to capacity-1, but maps to vertices 1 to capacity
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b, int* posA, int* posB) {
    MinHeapNode* temp = *a; *a = *b; *b = temp;
    int tempPos = *posA; *posA = *posB; *posB = tempPos;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx], 
                        &minHeap->pos[smallestNode->v], &minHeap->pos[idxNode->v]);

        minHeapify(minHeap, smallest);
    }
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        int parentIdx = (i - 1) / 2;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[parentIdx],
                        &minHeap->pos[minHeap->array[i]->v], 
                        &minHeap->pos[minHeap->array[parentIdx]->v]);
        i = parentIdx;
    }
}

bool isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

// --- Algorithm Engine ---
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V + 1]; // 1-based array
    MinHeap* minHeap = createMinHeap(V);

    // Initialization for 1-based indexing
    for (int v = 1; v <= V; ++v) {
        dist[v] = INT_MAX;
        // Store in heap array starting at index 0
        minHeap->array[v - 1] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v - 1; 
    }

    // Set the source distance
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    // Routing Sweep
    while (minHeap->size != 0) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        free(minHeapNode);

        Node* temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->dest;

            // Relaxation check
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
                temp->weight + dist[u] < dist[v]) {
                
                dist[v] = dist[u] + temp->weight;
                decreaseKey(minHeap, v, dist[v]); // Surgical O(log V) update
            }
            temp = temp->next;
        }
    }

    // Print space-separated output as requested
    for (int i = 1; i <= V; ++i) {
        if (dist[i] == INT_MAX) {
            printf("INF "); // Safety check for unreachable nodes
        } else {
            printf("%d ", dist[i]);
        }
    }
    printf("\n");

    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
}

// Memory Cleanup
void freeGraph(Graph* graph) {
    for (int i = 1; i <= graph->V; i++) {
        Node* curr = graph->adjLists[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph);
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 1;

    Graph* graph = createGraph(n);

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            addDirectedEdge(graph, u, v, w);
        }
    }

    int source;
    if (scanf("%d", &source) == 1 && source >= 1 && source <= n) {
        dijkstra(graph, source);
    }

    freeGraph(graph);
    return 0;
}