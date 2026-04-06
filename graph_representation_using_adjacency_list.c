// Problem: Build a graph with adjacency list representation. Use linked lists or dynamic arrays.

// Input:
// - n (vertices)
// - m (edges)
// - edges (u, v)

// Output:
// - List of adjacency lists for each vertex
#include <stdio.h>
#include <stdlib.h>

// A node to represent an edge in the linked list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// The Graph structure holding an array of linked list heads
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Standard memory allocation helper for an Edge Node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Fatal: Node allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Initializes the graph and the array of pointers
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) exit(EXIT_FAILURE);
    
    graph->numVertices = vertices;
    
    // Allocate the array of list heads and initialize them to NULL
    graph->adjLists = (Node**)calloc(vertices, sizeof(Node*));
    if (!graph->adjLists) {
        free(graph);
        exit(EXIT_FAILURE);
    }
    
    return graph;
}

/**
 * Core Algorithm: Adds an edge to an undirected graph.
 * Uses Head-Insertion for strict O(1) time complexity.
 */
void addEdge(Graph* graph, int src, int dest) {
    // 1. Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src]; // Point new node to current head
    graph->adjLists[src] = newNode;       // Make new node the new head

    // 2. Add edge from dest to src (Because it is UNDIRECTED)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Outputs the Adjacency List
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Vertex %d: ", v);
        while (temp) {
            printf("-> %d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Elite Memory Management: Deep cleanup of all fragmented nodes
void freeGraph(Graph* graph) {
    if (!graph) return;
    
    for (int v = 0; v < graph->numVertices; v++) {
        Node* curr = graph->adjLists[v];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp); // Free the individual edge node
        }
    }
    free(graph->adjLists); // Free the array of head pointers
    free(graph);           // Free the base struct
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
        
        // Bounds validation
        if (u < 0 || u >= n || v < 0 || v >= n) {
            fprintf(stderr, "Error: Edge (%d, %d) out of bounds.\n", u, v);
            continue;
        }

        addEdge(graph, u, v);
    }

    // Print to specification
    printGraph(graph);

    // Prevent memory leaks
    freeGraph(graph);

    return 0;
}