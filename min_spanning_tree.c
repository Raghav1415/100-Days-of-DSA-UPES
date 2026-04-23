// Problem Statement
// Given weighted undirected graph, compute total weight of Minimum Spanning Tree using Prim’s algorithm.

// Input Format
// n m
// u v w
// ...

// Output Format
// Total weight of MST.

// Sample Input
// 4 5
// 1 2 3
// 1 3 5
// 2 3 1
// 2 4 4
// 3 4 2

// Sample Output
// 6

// Explanation
// One possible MST edges: (2-3), (3-4), (1-2)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- 1. Graph Infrastructure (Undirected Weighted) ---
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
    // +1 for 1-based competitive programming inputs
    graph->adjLists = (Node**)calloc(V + 1, sizeof(Node*)); 
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    // Undirected Graph: Add edge in both directions
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// --- 2. Custom Min-Heap Infrastructure ---
typedef struct MinHeapNode {
    int v;
    int key; // The cheapest edge connecting this vertex to the MST
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int* pos; 
    MinHeapNode** array;
} MinHeap;

MinHeapNode* newMinHeapNode(int v, int key) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    // +1 for 1-based indexing
    minHeap->pos = (int*)malloc((capacity + 1) * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc((capacity + 1) * sizeof(MinHeapNode*));
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

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
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

void decreaseKey(MinHeap* minHeap, int v, int key) {
    int i = minHeap->pos[v];
    minHeap->array[i]->key = key;

    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
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

// --- 3. Prim's Algorithm Engine ---
void primMST(Graph* graph) {
    int V = graph->V;
    int key[V + 1];      // Tracks the minimum edge weight to include vertex V
    bool inMST[V + 1];   // Tracks if vertex V is already safely inside the MST
    MinHeap* minHeap = createMinHeap(V);

    // Initialization (1-based mapping)
    for (int v = 1; v <= V; ++v) {
        key[v] = INT_MAX;
        inMST[v] = false;
        minHeap->array[v - 1] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v - 1;
    }

    // Force the MST to start at vertex 1
    key[1] = 0;
    decreaseKey(minHeap, 1, key[1]);
    minHeap->size = V;

    int total_mst_weight = 0;

    // The MST Growth Engine
    while (minHeap->size != 0) {
        // Extract the node that has the cheapest connection to our growing tree
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        // The exact moment it is extracted, it is permanently locked into the MST
        inMST[u] = true;
        total_mst_weight += minHeapNode->key; // Add its connecting edge to our total
        
        free(minHeapNode); 

        // Scan all neighbors
        Node* temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->dest;
            int weight = temp->weight;

            // Prim's Rule: If the neighbor is NOT already in the tree, 
            // AND this new edge is cheaper than its current known connection...
            if (inMST[v] == false && weight < key[v]) {
                key[v] = weight;
                decreaseKey(minHeap, v, key[v]); // Surgically update its priority
            }
            temp = temp->next;
        }
    }

    printf("%d\n", total_mst_weight);

    // Memory Cleanup
    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);
}

// Standard Graph Cleanup
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

    // Read edges (u, v, weight)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u >= 1 && u <= n && v >= 1 && v <= n && w >= 0) {
            addEdge(graph, u, v, w);
        }
    }

    primMST(graph);

    freeGraph(graph);
    return 0;
}