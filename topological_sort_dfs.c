// Problem: Print topological ordering of a Directed Acyclic Graph (DAG) using DFS.
#include <stdio.h>
#include <stdlib.h>

// --- Directed Graph Infrastructure ---
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* inDegree; // CRITICAL: New array to track incoming edges
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
    graph->inDegree = (int*)calloc(vertices, sizeof(int)); // Auto-initialized to 0
    
    if (!graph->adjLists || !graph->inDegree) exit(EXIT_FAILURE);
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    // Directed edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // Kahn's Core Mechanic: Increment the destination's in-degree
    graph->inDegree[dest]++;
}
// -------------------------------------

/**
 * Kahn's Algorithm (Iterative Topological Sort)
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */
void kahnsAlgorithm(Graph* graph) {
    int n = graph->numVertices;
    
    // Allocate our flat array Queue and an Output array
    int* queue = (int*)malloc(n * sizeof(int));
    int* topoOrder = (int*)malloc(n * sizeof(int));
    if (!queue || !topoOrder) exit(EXIT_FAILURE);

    int front = 0, rear = 0;
    int processCount = 0;

    // 1. The Initial Sweep
    // Find all nodes that have ZERO dependencies and enqueue them.
    for (int i = 0; i < n; i++) {
        if (graph->inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // 2. The Peeling Engine
    while (front < rear) {
        // Dequeue the current independent node
        int current = queue[front++];
        topoOrder[processCount++] = current; // Add to our final sorted array

        // Scan all nodes that depend on 'current'
        Node* temp = graph->adjLists[current];
        while (temp != NULL) {
            int dependentNode = temp->vertex;
            
            // "Peel" the edge away by decrementing the dependent's in-degree
            graph->inDegree[dependentNode]--;

            // If that node now has NO more dependencies, it is ready to execute!
            if (graph->inDegree[dependentNode] == 0) {
                queue[rear++] = dependentNode;
            }
            temp = temp->next;
        }
    }

    // 3. The Cycle Trap Failsafe
    // If we didn't process every single node, a cyclic dependency exists.
    if (processCount != n) {
        printf("FATAL ERROR: Cycle detected! Topological sort impossible.\n");
    } else {
        printf("Kahn's Topological Sort: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", topoOrder[i]);
        }
        printf("\n");
    }

    free(queue);
    free(topoOrder);
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
    free(graph->inDegree);
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

    kahnsAlgorithm(graph);

    freeGraph(graph);
    return 0;
}
