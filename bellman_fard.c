// Problem: Compute shortest path from source and detect negative weight cycles using Bellman-Ford.

// Input:
// - n vertices
// - m edges (u,v,w)

// Output:
// - Shortest distances OR NEGATIVE CYCLE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// --- Flat Edge List Infrastructure ---
typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edge; // A single contiguous array of all edges
} Graph;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) exit(EXIT_FAILURE);
    
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    
    if (!graph->edge) exit(EXIT_FAILURE);
    return graph;
}
// -------------------------------------

/**
 * Core Algorithm: Bellman-Ford
 * Time Complexity: O(V * E)
 * Space Complexity: O(V)
 */
void BellmanFord(Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    
    int* dist = (int*)malloc(V * sizeof(int));
    if (!dist) exit(EXIT_FAILURE);

    // 1. Initialization
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // 2. The V-1 Sweeps (Dynamic Programming core)
    for (int i = 1; i <= V - 1; i++) {
        bool updated = false; // Early stopping optimization
        
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;

            // Trap Avoidance: Ensure 'u' is reachable to prevent INT_MAX overflow
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                updated = true;
            }
        }
        
        // If no distances changed in this sweep, the shortest paths are locked.
        if (!updated) break; 
    }

    // 3. The Nth Sweep (Negative Cycle Detection)
    // If we can STILL relax an edge after V-1 sweeps, a negative cycle mathematically exists.
    for (int j = 0; j < E; j++) {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("NEGATIVE CYCLE\n");
            free(dist);
            return;
        }
    }

    // 4. Print valid shortest paths
    printf("Vertex \t Distance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d \t INF\n", i);
        } else {
            printf("%d \t %d\n", i, dist[i]);
        }
    }

    free(dist);
}

int main() {
    int V, E;
    
    // Read Vertices (V) and Edges (E)
    if (scanf("%d %d", &V, &E) != 2) return 1;

    Graph* graph = createGraph(V, E);

    // Read all edges
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    int source;
    // Read the starting vertex
    if (scanf("%d", &source) == 1 && source >= 0 && source < V) {
        BellmanFord(graph, source);
    } else {
        fprintf(stderr, "Invalid source vertex.\n");
    }

    // Memory Cleanup
    free(graph->edge);
    free(graph);

    return 0;
}