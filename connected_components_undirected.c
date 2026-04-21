// Problem Statement
// Using DFS or BFS, count number of connected components.

// Input Format
// n m
// edges

// Output Format
// Number of connected components.

// Sample Input
// 6 3
// 1 2
// 2 3
// 5 6

// Sample Output
// 3

// Explanation
// Components: {1,2,3}, {4}, {5,6}
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
    
    // CRITICAL: Allocate 'vertices + 1' to safely handle 1-based indexing (1 to N)
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
 * It will mark all reachable nodes from the starting vertex as true.
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
 * Wrapper Function: Counts the number of isolated components.
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */
int countComponents(Graph* graph) {
    int n = graph->numVertices;
    
    // Allocate visited array using n + 1 for 1-based indexing
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));
    if (!visited) exit(EXIT_FAILURE);

    int componentCount = 0;

    // THE MASTER LOOP: Iterate through all vertices 1 to N
    for (int i = 1; i <= n; i++) {
        // If we find a node that NO previous DFS has touched...
        if (!visited[i]) {
            // We have discovered a completely new, isolated island!
            componentCount++;
            
            // Drop the paintbrush to map out the rest of this new island
            dfs(graph, i, visited); 
        }
    }

    free(visited);
    return componentCount;
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
    
    // Read Vertices (n) and Edges (m)
    if (scanf("%d %d", &n, &m) != 2) return 1;

    Graph* graph = createGraph(n);

    // Read the m edge pairs
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Strict bounds checking against 1-based boundaries
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            addEdge(graph, u, v);
        }
    }

    int components = countComponents(graph);
    
    // Output Format requested
    printf("%d\n", components);

    freeGraph(graph);
    return 0;
}