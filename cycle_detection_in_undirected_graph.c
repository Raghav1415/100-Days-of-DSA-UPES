// Problem: Using DFS and parent tracking, detect if undirected graph has a cycle.

// Output:
// - YES or NO
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
    graph->adjLists = (Node**)calloc(vertices, sizeof(Node*));
    if (!graph->adjLists) exit(EXIT_FAILURE);
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    // Undirected Graph: Insert at head for both src and dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
// ---------------------------------------------

/**
 * Core DFS Engine for Cycle Detection.
 * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the call stack
 */
bool dfsCheckCycle(Graph* graph, int currentVertex, int parentVertex, bool* visited) {
    // 1. Mark the current node as active
    visited[currentVertex] = true;

    // 2. Scan all adjacent connections
    Node* temp = graph->adjLists[currentVertex];
    while (temp != NULL) {
        int neighbor = temp->vertex;

        // Condition A: If the neighbor is unvisited, dive into it
        if (!visited[neighbor]) {
            // Pass 'currentVertex' as the new 'parentVertex'
            if (dfsCheckCycle(graph, neighbor, currentVertex, visited)) {
                return true; // Cycle confirmed deep in the recursion, bubble it up
            }
        }
        // Condition B: Neighbor IS visited, BUT it is NOT the parent we just came from
        else if (neighbor != parentVertex) {
            // This is the mathematical proof of a cycle. 
            // We hit a node we've seen before via a completely different path.
            return true;
        }

        // Move to the next adjacent node
        temp = temp->next;
    }

    return false; // No cycles found from this path
}

/**
 * Wrapper Function: Checks all disconnected components.
 */
bool hasCycle(Graph* graph) {
    int n = graph->numVertices;
    bool* visited = (bool*)calloc(n, sizeof(bool));
    if (!visited) exit(EXIT_FAILURE);

    // Trap Avoidance: We MUST loop through every node in case of disconnected islands.
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // -1 signifies the absolute start node has no parent
            if (dfsCheckCycle(graph, i, -1, visited)) {
                free(visited);
                return true; 
            }
        }
    }

    free(visited);
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