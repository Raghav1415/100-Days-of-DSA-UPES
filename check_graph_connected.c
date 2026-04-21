// Problem Statement
// Using BFS or DFS, check if the entire graph is connected.

// Input Format
// n m
// edges

// Output Format
// CONNECTED
// NOT CONNECTED

// Sample Input
// 4 2
// 1 2
// 3 4

// Sample Output
// NOT CONNECTED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Graph Infrastructure (Adjacency List) ---
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
    
    // Allocate 'vertices + 1' to safely handle 1-based indexing
    graph->adjLists = (Node**)calloc(vertices + 1, sizeof(Node*));
    if (!graph->adjLists) exit(EXIT_FAILURE);
    
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    // Undirected Graph
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
// ---------------------------------------------

/**
 * Core DFS Engine. Acts as the "paintbrush".
 */
void dfs(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    
    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (!visited[connectedVertex]) {
            dfs(graph, connectedVertex, visited);
        }
        temp = temp->next;
    }
}

/**
 * Wrapper Function: The Single Paintbrush Test
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */
bool isConnected(Graph* graph) {
    int n = graph->numVertices;
    if (n == 0) return true; // Trivial case
    
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));
    if (!visited) exit(EXIT_FAILURE);

    // 1. Drop the single paintbrush at the first node
    dfs(graph, 1, visited);

    // 2. The Verification Scan
    for (int i = 1; i <= n; i++) {
        // If any node remains unpainted, the graph is fractured
        if (!visited[i]) {
            free(visited);
            return false; 
        }
    }

    // If we scanned the whole array and found no 'false', it is fully connected
    free(visited);
    return true;
}

// Deep memory cleanup
void freeGraph(Graph* graph) {
    if (!graph) return;
    for (int v = 0; v <= graph->numVertices; v++) {
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
    
    if (scanf("%d %d", &n, &m) != 2) return 1;

    Graph* graph = createGraph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            addEdge(graph, u, v);
        }
    }

    if (isConnected(graph)) {
        printf("CONNECTED\n");
    } else {
        printf("NOT CONNECTED\n");
    }

    freeGraph(graph);
    return 0;
}