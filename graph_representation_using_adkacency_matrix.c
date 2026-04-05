// Problem: Build a graph with n vertices and m edges using adjacency matrix representation.
// The graph may be directed or undirected.

// Input:
// - n (vertices)
// - m (edges)
// - m pairs (u, v)

// Output:
// - n x n adjacency matrix
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Creates a 2D adjacency matrix safely using a SINGLE contiguous block of memory.
 * This guarantees O(1) row access while maintaining perfect CPU cache locality.
 */
int** createMatrix(int n) {
    // 1. Allocate the array of row pointers
    int** matrix = (int**)malloc(n * sizeof(int*));
    if (!matrix) {
        fprintf(stderr, "Fatal: Pointer array allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // 2. Allocate the actual data as one giant 1D array using calloc 
    // calloc is strictly required here because it initializes everything to 0.
    int* data = (int*)calloc(n * n, sizeof(int));
    if (!data) {
        fprintf(stderr, "Fatal: Contiguous data allocation failed.\n");
        free(matrix);
        exit(EXIT_FAILURE);
    }

    // 3. Point each row pointer to the correct offset within the 1D data block
    for (int i = 0; i < n; i++) {
        matrix[i] = data + (i * n);
    }

    return matrix;
}

/**
 * Safely frees the contiguous matrix structure.
 */
void freeMatrix(int** matrix) {
    if (matrix) {
        free(matrix[0]); // Free the massive data block first
        free(matrix);    // Free the pointer array
    }
}

int main() {
    int n, m;
    
    // Read Vertices (n) and Edges (m)
    if (scanf("%d %d", &n, &m) != 2) return 1;

    // Create a 0-initialized n x n matrix
    int** adjMatrix = createMatrix(n);

    // Read the m pairs
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Bounds checking to prevent Segfaults from bad user input
        if (u < 0 || u >= n || v < 0 || v >= n) {
            fprintf(stderr, "Error: Edge (%d, %d) is out of bounds for %d vertices.\n", u, v, n);
            continue; 
        }

        // Populate the matrix
        adjMatrix[u][v] = 1; 
        
        // If the graph is explicitly DIRECTED, you would comment out the next line.
        // For UNDIRECTED graphs, the matrix must be symmetric.
        adjMatrix[v][u] = 1; 
    }

    // Output the n x n Adjacency Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    // Elite programmers clean up their memory
    freeMatrix(adjMatrix);

    return 0;
}