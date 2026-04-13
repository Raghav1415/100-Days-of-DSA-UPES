// Problem: Given weighted graph with non-negative edges, compute shortest path from source using priority queue.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- 1. Graph Infrastructure (Weighted) ---
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
    graph->adjLists = (Node**)calloc(V, sizeof(Node*));
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    // Directed graph for shortest path mapping
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // If Undirected, uncomment below:
    // newNode = createNode(src, weight);
    // newNode->next = graph->adjLists[dest];
    // graph->adjLists[dest] = newNode;
}

// --- 2. Min-Heap Infrastructure ---
typedef struct MinHeapNode {
    int v;
    int dist;
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int* pos; // CRITICAL: Tracks where vertex 'v' currently lives in the heap array
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
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Swaps two nodes and updates their position tracker simultaneously
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b, int* posA, int* posB) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
    
    int tempPos = *posA;
    *posA = *posB;
    *posB = tempPos;
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
        // We must pass the pos[] pointers so the tracker updates during the swap
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx], 
                        &minHeap->pos[smallestNode->v], &minHeap->pos[idxNode->v]);

        minHeapify(minHeap, smallest);
    }
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;

    // Store the root node
    MinHeapNode* root = minHeap->array[0];

    // Replace root node with last node
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update positions
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// The Elite Operation: Updates a value in O(log V) without duplicating nodes
void decreaseKey(MinHeap* minHeap, int v, int dist) {
    // Look up the exact array index of vertex v in O(1) time
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist; // Update the distance

    // Bubble up to restore Min-Heap property
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

// --- 3. Dijkstra's Algorithm Engine ---
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V]; 
    MinHeap* minHeap = createMinHeap(V);

    // Initialize all distances to Infinity
    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v; // Vertex 'v' is currently at index 'v'
    }

    // Initialize the source node
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]); // Bubble source to the top of the heap

    minHeap->size = V; // Heap is now fully loaded

    // The Routing Engine
    while (minHeap->size != 0) {
        // Extract the vertex with the absolute minimum distance
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        free(minHeapNode); // Clean up the extracted node memory

        // Traverse all adjacent vertices of u and update their distances
        Node* temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->dest;

            // Relaxation Step:
            // IF node is still in heap AND current path is shorter than known path
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
                temp->weight + dist[u] < dist[v]) {
                
                dist[v] = dist[u] + temp->weight;
                
                // Instantly update the heap mathematically
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print final shortest paths
    printf("Vertex \t Distance from Source (%d)\n", src);
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) printf("%d \t INF\n", i);
        else printf("%d \t %d\n", i, dist[i]);
    }

    // Memory Cleanup
    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
}

// Standard Graph Cleanup
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
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

    // Read edges (u, v, weight)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u >= 0 && u < n && v >= 0 && v < n && w >= 0) {
            addEdge(graph, u, v, w);
        }
    }

    int source;
    if (scanf("%d", &source) == 1 && source >= 0 && source < n) {
        dijkstra(graph, source);
    }

    freeGraph(graph);
    return 0;
}