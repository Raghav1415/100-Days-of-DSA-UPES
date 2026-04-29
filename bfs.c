// Problem: Perform BFS from a given source using queue.

// //Input:
// - n
// - adjacency list
// - source s

// Output:
// - BFS traversal order
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Graph Infrastructure (O(1) Head Insertion) ---
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) exit(EXIT_FAILURE);
    graph->numVertices = vertices;
    graph->adjLists = (Node**)calloc(vertices, sizeof(Node*));
    if (!graph->adjLists) exit(EXIT_FAILURE);
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Assuming Undirected Graph for standard BFS testing
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
// --------------------------------------------------

/**
 * Core Algorithm: Breadth-First Search.
 * Uses a strictly bounded flat array queue and early-visited marking.
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */
void performBFS(Graph* graph, int startVertex) {
    int n = graph->numVertices;
    
    // 1. Initialize State Arrays
    bool* visited = (bool*)calloc(n, sizeof(bool));
    int* queue = (int*)malloc(n * sizeof(int));
    if (!visited || !queue) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // 2. Queue Engine Setup
    int front = 0;
    int rear = 0;

    // 3. The Catalyst (Early Marking)
    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS Traversal starting from %d: ", startVertex);

    // 4. The Wave Propagation
    while (front < rear) {
        // Dequeue
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Scan Neighbors
        Node* temp = graph->adjLists[currentVertex];
        while (temp != NULL) {
            int connectedVertex = temp->vertex;

            // CRITICAL: Check and mark BEFORE enqueueing
            if (!visited[connectedVertex]) {
                visited[connectedVertex] = true; 
                queue[rear++] = connectedVertex; 
            }
            temp = temp->next;
        }
    }
    printf("\n");

    // Clean up local state
    free(visited);
    free(queue);
}

// Deep cleanup to prevent heap leaks
void freeGraph(Graph* graph) {
    if (!graph) return;
    for (int v = 0; v < graph->numVertices; v++) {
        Node* curr = graph->adjLists[v];
        while (curr != NULL) {
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
    
    // Read Vertices (n) and Edges (m)
    if (scanf("%d %d", &n, &m) != 2) return 1;

    Graph* graph = createGraph(n);

    // Read the m edge pairs
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Strict bounds checking
        if (u >= 0 && u < n && v >= 0 && v < n) {
            addEdge(graph, u, v);
        }
    }

    int startVertex;
    // Read the starting vertex
    if (scanf("%d", &startVertex) == 1) {
        if (startVertex >= 0 && startVertex < n) {
            performBFS(graph, startVertex);
        } else {
            fprintf(stderr, "Error: Start vertex %d out of bounds.\n", startVertex);
        }
    }

    // Clean up
    freeGraph(graph);
    return 0;
}
