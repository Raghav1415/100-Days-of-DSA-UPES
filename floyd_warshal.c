// Problem: Given a weighted graph with n vertices, implement the Floyd-Warshall algorithm to compute the shortest distances between every pair of vertices. The graph may contain positive or negative edge weights, but it does not contain any negative weight cycles.

// Input:
// - First line: integer n representing the number of vertices
// - Next n lines: n space-separated integers representing the adjacency matrix of the graph
//   (use -1 to indicate no direct edge between two vertices)

// Output:
// - Print the shortest distance matrix where the value at row i and column j represents the shortest distance from vertex i to vertex j

// Example:
// Input:
// 4
// 0 5 -1 10
// -1 0 3 -1
// -1 -1 0 1
// -1 -1 -1 0

// Output:
// 0 5 8 9
// -1 0 3 4
// -1 -1 0 1
// -1 -1 -1 0

// Explanation:
// The Floyd-Warshall algorithm works by considering each vertex as an intermediate point and updating the shortest paths between all pairs of vertices. For example, the shortest path from vertex 1 to vertex 3 is improved via vertex 2 with total cost 8. This process is repeated for all vertices, resulting in the final shortest distance matrix.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a safe Infinity that won't overflow when added to another number
#define INF (INT_MAX / 2)

/**
 * Core Algorithm: Floyd-Warshall All-Pairs Shortest Path
 * Time Complexity: O(V^3)
 * Space Complexity: O(V^2)
 */
void floydWarshall(int** dist, int n) {
    // THE MASTER RULE: 'k' (the intermediate node) MUST be the outermost loop.
    // We process the graph layer by layer, unlocking one new shortcut node at a time.
    for (int k = 0; k < n; k++) {
        // 'i' is the source node
        for (int i = 0; i < n; i++) {
            // 'j' is the destination node
            for (int j = 0; j < n; j++) {
                
                // If we can reach 'k' from 'i', AND we can reach 'j' from 'k'
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    
                    // The Relaxation Step: Is the shortcut cheaper than the direct route?
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    
    // Read number of vertices
    if (scanf("%d", &n) != 1) return 1;

    // Dynamically allocate a 2D array for the distance matrix
    int** dist = (int**)malloc(n * sizeof(int*));
    if (!dist) exit(EXIT_FAILURE);
    
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
        if (!dist[i]) exit(EXIT_FAILURE);
        
        for (int j = 0; j < n; j++) {
            int weight;
            scanf("%d", &weight);
            
            // Input Mapping: Translate your -1 placeholder into our mathematical INF
            if (weight == -1 && i != j) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = weight;
            }
        }
    }

    // Execute the algorithm
    floydWarshall(dist, n);

    // Print the final shortest distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Output Mapping: Translate INF back to your required -1 format
            if (dist[i][j] == INF) {
                printf("-1 ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }

    // Deep memory cleanup
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);

    return 0;
}