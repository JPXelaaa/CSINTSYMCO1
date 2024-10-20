#include <stdio.h>
#include <string.h>
#include "FileHandling.h"
#include "A*.h"

#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50

// Function to get the label for a given index
void getLabel(int index, char *label) {
    // List of labels
    const char *labels[] = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J1", "J2", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U"
    };

    // Assign the corresponding label to the output
    if (index >= 0 && index < sizeof(labels) / sizeof(labels[0])) {
        strcpy(label, labels[index]);
    } else {
        strcpy(label, "?");  // FFor out-of-range indices
    }
}

int main() {
    char reference[MAX_ROWS][MAX_COLS];  // Stores the node names
    int adjMatrix[MAX_ROWS][MAX_COLS];   // Stores the edge weights (adjacency matrix)
    Coordinates coords[MAX_ROWS];        // Stores the x, y coordinates of the nodes
    int numVertices;                     // Number of vertices in the graph
    char startNode[MAX_NAME_LEN], goalNode[MAX_NAME_LEN];
    char startIndex, goalIndex;

    // Read from input file
    if (readIDsFromFile("GRAPHS.TXT", reference, adjMatrix, coords, &numVertices)) {
        printf("File read successfully.\n");

        // Display number of vertices
        printf("Number of vertices: %d\n\n", numVertices);

        // Example: Show Euclidean distance between two nodes (e.g., D and P)
        printf("Euclidean distances between connected nodes:\n");
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] != 0) {  // If there's a connection (non-zero weight)
                    double distance = calculateEuclideanDistance(coords[i], coords[j]); 
                    printf("Distance between %s and %s: %.2f\n", reference[i], reference[j], distance);
                }
            }
        }

        // Display the adjacency matrix with edge weights
        printf("\nAdjacency Matrix (Edge Weights):\n");

        // Print column indices (header)
        printf("    ");  // Indentation for row labels
        char label[MAX_NAME_LEN];
        for (int i = 0; i < numVertices; i++) {
            getLabel(i, label);           // Get the label for the current index
            printf("%4s", label);         // Print the label with a width of 4 characters
        }
        printf("\n");

        // Print rows with labels and matrix data
        for (int i = 0; i < numVertices; i++) {
            getLabel(i, label);           // Get the label for the current row
            printf("%4s", label);         // Print the row label with a width of 4 characters
            for (int j = 0; j < numVertices; j++) {
                printf("%4d", adjMatrix[i][j]);  // Print matrix elements with a width of 4 characters
            }
            printf("\n");
        }
         
        printf("Enter the start node: ");
        scanf("%s", startNode);
        printf("Enter the goal node: ");
        scanf("%s", goalNode);

        // Find indices of the start and goal nodes using the reference array
        startIndex = indexCheck(reference, startNode);
        goalIndex = indexCheck(reference, goalNode);

        if (startIndex == -1 || goalIndex == -1) {
            printf("Invalid start or goal node.\n");
            return 1;
        }

        if (startIndex == -1 || goalIndex == -1) {
            printf("Invalid start or goal node.\n");
            return 1;
        }

        // Run A* algorithm
        aStar(startIndex, goalIndex, adjMatrix, coords, numVertices, reference);
    } else {
        printf("Error reading from file.\n");
    }

    return 0;
}