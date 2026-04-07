// Problem: Perform DFS starting from a given source vertex using recursion.

// Input:
// - n
// - adjacency list
// - starting vertex s

// Output:
// - DFS traversal order
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Graph Infrastructure ---
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

// O(1) Head Insertion (Undirected)
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
// ----------------------------

/**
 * Core DFS Recursive Utility.
 * Passes the visited array by reference to maintain thread safety.
 */
void dfsRecursive(Graph* graph, int vertex, bool* visited) {
    // 1. Mark the current node as visited and output it
    visited[vertex] = true;
    printf("%d ", vertex);

    // 2. Traverse the adjacency list of the current vertex
    Node* current = graph->adjLists[vertex];
    
    while (current != NULL) {
        int connectedVertex = current->vertex;
        
        // 3. If a connected vertex hasn't been visited, dive deeper into it (Recursion)
        if (!visited[connectedVertex]) {
            dfsRecursive(graph, connectedVertex, visited);
        }
        
        // 4. Move to the next adjacent node (Backtracking phase when recursion unwinds)
        current = current->next;
    }
}

/**
 * Wrapper function to initialize the DFS state.
 */
void performDFS(Graph* graph, int startVertex) {
    // Dynamically allocate the visited array to keep the function thread-safe
    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
    if (!visited) {
        fprintf(stderr, "Fatal: Visited array allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("DFS Traversal starting from %d: ", startVertex);
    dfsRecursive(graph, startVertex, visited);
    printf("\n");

    // Clean up local state
    free(visited);
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
            performDFS(graph, startVertex);
        } else {
            fprintf(stderr, "Error: Start vertex %d out of bounds.\n", startVertex);
        }
    }

    // Free all allocated memory
    freeGraph(graph);
    return 0;
}