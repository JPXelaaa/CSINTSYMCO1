#include <stdio.h>
#include <string.h>
#include "FileHandling.h"
#include "A*.h"
#include "GBFS.h"
#include <stdbool.h>

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

void sampleData(int adjMatrix[MAX_ROWS][MAX_COLS], 
                Coordinates coords[MAX_ROWS], 
                int numVertices, 
                char reference[MAX_ROWS][MAX_COLS]){

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
}

bool checkAdmissibility(int adjMatrix[MAX_ROWS][MAX_COLS], 
                        Coordinates coords[MAX_ROWS], 
                        int numVertices, char reference[MAX_ROWS][MAX_COLS]) {
    bool admissible = true;  // Assume the heuristic is admissible

    printf("\nChecking admissibility of heuristics...\n");

    // Loop over all pairs of nodes
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j && adjMatrix[i][j] != 0) {  // Only check connected nodes
                // Calculate heuristic (Euclidean distance)
                double heuristic = calculateEuclideanDistance(coords[i], coords[j]);
                
                // Get actual cost from adjacency matrix
                int actualCost = adjMatrix[i][j];

                // Check if the heuristic overestimates the actual cost
                if (heuristic > actualCost) {
                    char labelA = reverseIndexCheck(reference, i);
                    char labelB = reverseIndexCheck(reference, j);
                    printf("Heuristic from %c to %c is not admissible: h = %.2f, actual cost = %d\n", labelA, labelB, heuristic, actualCost);
                    admissible = false;  // Set flag to false if heuristic is not admissible
                }
                else{
                    char labelA = reverseIndexCheck(reference, i);
                    char labelB = reverseIndexCheck(reference, j);
                    float difference = actualCost-heuristic;
                    printf("Heuristic from %c to %c is admissible: h = %.2f, actual cost = %d, difference = %.2f\n", labelA, labelB, heuristic, actualCost, difference);
                }
                
            }
        }
    }

    if (admissible) {
        printf("All heuristics are admissible.\n");
    } else {
        printf("Some heuristics are not admissible.\n");
    }

    return admissible;
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
        sampleData(adjMatrix, coords, numVertices, reference); 
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

        bool isAdmissible = checkAdmissibility(adjMatrix, coords, numVertices, reference);

        if (!isAdmissible) {
            printf("Heuristics are not admissible, check the distances and weights.\n");
        } else {
            printf("Heuristics are admissible, proceeding with algorithms.\n");
            // Continue with BFS, DFS, A* and GBFS algorithms as usual
        }

        printf("\n================BLIND SEARCH===============\n");
        printf("\n-------------------------------------------\n");
        printf("\nBFS Algorithm Pathing: \n\n");
        //BFS(); // ---> Please input BFS algorithm when finished here <---
        printf("\n-------------------------------------------\n");

        printf("\nDFS Algorithm Pathing: \n\n");
        //DFS(); // ---> Please input DFS algorithm when finished here <---
        printf("\n-------------------------------------------\n");

        printf("\n=============HEAURISTIC SEARCH=============\n");
        printf("\n-------------------------------------------\n");
        printf("\nA* Algorithm Pathing: \n\n");
        aStar(startIndex, goalIndex, adjMatrix, coords, numVertices, reference); // A* STAR ALGORITHM
        printf("\n-------------------------------------------\n");

        printf("\nGreedy Best First Search Algorithm Pathing: \n\n");
        greedyBestFirstSearch(startIndex, goalIndex, adjMatrix, coords, numVertices, reference); // GBFS ALGORITHM
        printf("\n-------------------------------------------\n");
        
        
    } else {
        printf("Error reading from file.\n");
    }

    return 0;
}
