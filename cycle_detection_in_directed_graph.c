// Problem: Detect cycle in directed graph using DFS and recursion stack.

// Output:
// - YES if cycle exists
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Directed Graph Infrastructure ---
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

// CRITICAL DIFFERENCE: Directed graphs only insert ONE edge.
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}
// -------------------------------------

/**
 * Core DFS Engine for Directed Graph Cycle Detection.
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */
bool dfsCheckCycle(Graph* graph, int currentVertex, bool* visited, bool* recStack) {
    // 1. Mark the node as visited globally
    visited[currentVertex] = true;
    
    // 2. Mark the node as currently active in THIS specific recursive path
    recStack[currentVertex] = true;

    // 3. Scan all outbound directed edges
    Node* temp = graph->adjLists[currentVertex];
    while (temp != NULL) {
        int neighbor = temp->vertex;

        // Condition A: The neighbor has never been visited. Plunge into it.
        if (!visited[neighbor]) {
            if (dfsCheckCycle(graph, neighbor, visited, recStack)) {
                return true; // Cycle detected deep in recursion
            }
        }
        // Condition B: The neighbor IS visited, AND it is currently in our active stack!
        // This is a BACK-EDGE. It mathematically proves a directed cycle.
        else if (recStack[neighbor]) {
            return true;
        }

        temp = temp->next;
    }

    // 4. THE CLEANUP (The trap juniors miss)
    // We have fully explored this node and all its descendants. 
    // We are now backtracking. We MUST remove it from the active path tracker.
    recStack[currentVertex] = false;
    
    return false;
}

/**
 * Wrapper Function: Checks all disconnected components.
 */
bool hasCycle(Graph* graph) {
    int n = graph->numVertices;
    
    // Allocate two separate state trackers
    bool* visited = (bool*)calloc(n, sizeof(bool));
    bool* recStack = (bool*)calloc(n, sizeof(bool));
    if (!visited || !recStack) exit(EXIT_FAILURE);

    // Master Loop to catch disconnected islands
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfsCheckCycle(graph, i, visited, recStack)) {
                free(visited);
                free(recStack);
                return true; 
            }
        }
    }

    free(visited);
    free(recStack);
    return false;
}

// Memory Cleanup
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
    if (scanf("%d %d", &n, &m) != 2) return 1;

    Graph* graph = createGraph(n);

    // Read directed edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < n && v >= 0 && v < n) {
            addEdge(graph, u, v);
        }
    }

    if (hasCycle(graph)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    freeGraph(graph);
    return 0;
}