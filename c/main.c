#include <stdio.h>
#include "FileHandling.h"

#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50

int main() {
    char reference[MAX_ROWS][MAX_COLS];  // Stores the node names
    int adjMatrix[MAX_ROWS][MAX_COLS];   // Stores the edge weights (adjacency matrix)
    Coordinates coords[MAX_ROWS];        // Stores the x, y coordinates of the nodes
    int numVertices;                     // Number of vertices in the graph

    // Read from input file
    if (readIDsFromFile("GRAPHS.TXT", reference, adjMatrix, coords, &numVertices)) {
        printf("File read successfully.\n");

        // Display number of vertices
        printf("Number of vertices: %d\n\n", numVertices);

        // Example: Show Euclidean distance between two nodes (e.g., A and B)
        int node1Index = indexCheck(reference, "A");
        int node2Index = indexCheck(reference, "B");

        if (node1Index != -1 && node2Index != -1) {
            double distance = calculateEuclideanDistance(coords[node1Index], coords[node2Index]);
            printf("Euclidean distance between %s and %s: %.2f\n", reference[node1Index], reference[node2Index], distance);
        } else {
            printf("Nodes not found in the graph.\n");
        }

        // Display the adjacency matrix with edge weights
        printf("\nAdjacency Matrix (Edge Weights):\n");
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                printf("%d ", adjMatrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Error reading from file.\n");
    }

    return 0;
}
