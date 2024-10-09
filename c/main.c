/*
[main.c CURRENT UPDATE]
The current main.c program handles the file reading alogirthm displaying the information found
in the GRAPHS.TXT file.

Run to test.

The heuristic values are to follow.
*/

#include <stdio.h>
#include "FileHandling.h"

#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50

int main() {
    char reference[MAX_ROWS][MAX_COLS];  // Stores the node names
    int adjMatrix[MAX_ROWS][MAX_COLS];   // Stores the edge weights (adjacency matrix)
    int heuristic[MAX_ROWS];             // Stores the heuristic values
    int numVertices;                     // Number of vertices in the graph

    // Read from input file
    if (readIDsFromFile("GRAPHS.TXT", reference, adjMatrix, heuristic, &numVertices)) {
        printf("File read successfully.\n");

        // Display number of vertices
        printf("Number of vertices: %d\n\n", numVertices);

        // Display the heuristic values
        printf("Heuristic values:\n");
        for (int i = 0; i < numVertices; i++) {
            printf("Node: %s, Heuristic: %d\n", reference[i], heuristic[i]);
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
