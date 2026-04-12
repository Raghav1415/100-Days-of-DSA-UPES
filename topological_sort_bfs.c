// Problem: Implement topological sorting using in-degree array and queue (Kahnâ€™s Algorithm).
#include <stdio.h>
#include <stdlib.h>

// --- Graph Infrastructure ---
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* inDegree; 
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) exit(EXIT_FAILURE);
    
    graph->numVertices = vertices;
    graph->adjLists = (Node**)calloc(vertices, sizeof(Node*));
    graph->inDegree = (int*)calloc(vertices, sizeof(int));
    
    if (!graph->adjLists || !graph->inDegree) exit(EXIT_FAILURE);
    return graph;
}

void addDirectedEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // Increment the destination's in-degree (dependency count)
    graph->inDegree[dest]++;
}
// ----------------------------

/**
 * Kahn's Algorithm (Iterative Topological Sort using BFS Queue)
 */
void topologicalSortKahns(Graph* graph) {
    int n = graph->numVertices;
    
    int* queue = (int*)malloc(n * sizeof(int));
    int* topoOrder = (int*)malloc(n * sizeof(int));
    if (!queue || !topoOrder) exit(EXIT_FAILURE);

    int front = 0, rear = 0;
    int processCount = 0;

    // 1. Initial Sweep: Enqueue all vertices with 0 in-degree
    for (int i = 0; i < n; i++) {
        if (graph->inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // 2. Queue Engine: Process and Peel
    while (front < rear) {
        int current = queue[front++];
        topoOrder[processCount++] = current; 

        Node* temp = graph->adjLists[current];
        while (temp != NULL) {
            int dependentNode = temp->vertex;
            
            // Sever the dependency
            graph->inDegree[dependentNode]--;

            // If all prerequisites are met, enqueue
            if (graph->inDegree[dependentNode] == 0) {
                queue[rear++] = dependentNode;
            }
            temp = temp->next;
        }
    }

    // 3. Validation and Output
    if (processCount != n) {
        printf("NO TOPOLOGICAL SORT: Graph contains a cycle.\n");
    } else {
        printf("Topological Sort: ");
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
    
    // Read Vertices (n) and Edges (m)
    if (scanf("%d %d", &n, &m) != 2) return 1;

    Graph* graph = createGraph(n);

    // Read directed edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Ensure bounds are valid
        if (u >= 0 && u < n && v >= 0 && v < n) {
            addDirectedEdge(graph, u, v);
        } else {
            fprintf(stderr, "Edge out of bounds.\n");
        }
    }

    topologicalSortKahns(graph);

    freeGraph(graph);
    return 0;
}