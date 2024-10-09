#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "FileHandling.h"

int indexCheck(char reference[MAX_ROWS][MAX_COLS], char temp[50]) {
    int i;
    for (i = 0; i < MAX_ROWS; i++) {
        if (strcmp(reference[i], temp) == 0) {
            return i;
        }
    }
    return -1;
}

/*
   a. Purpose: Reads vertex IDs, heuristic values, and edge weights from a file.
   b. Parameters:
      - char *filename: The name of the file to read from.
      - char reference[MAX_ROWS][MAX_COLS]: The array to store the vertex names.
      - int adjMatrix[MAX_ROWS][MAX_COLS]: The adjacency matrix to store edge weights.
      - int heuristic[MAX_ROWS]: The array to store heuristic values for each vertex.
      - int *numVertices: Pointer to an integer to store the number of vertices.
   c. Return type: int
*/
int readIDsFromFile(char *filename, char reference[MAX_ROWS][MAX_COLS],
                    int adjMatrix[MAX_ROWS][MAX_COLS], int heuristic[MAX_ROWS],
                    int *numVertices) {

    FILE *fp = fopen(filename, "r");
    char node[50], adjNode[50];
    int count = 0;
    char line[256];
    int heuristicVal, edgeWeight;
    int i;

    if (fp == NULL) {
        printf("Unable to open file\n");
        return 0;
    }

    // Initialize adjacency matrix to 0 (no connections by default)
    for (i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            adjMatrix[i][j] = 0;  // No connection (0 weight)
        }
    }

    // Read node definitions and heuristic values
    while (fgets(line, sizeof(line), fp)) {
        // Read the node, its heuristic, edge weight, and adjacent node
        if (sscanf(line, "%s %d %d %s", node, &heuristicVal, &edgeWeight, adjNode) == 4) {
            // Check if the node already exists in the reference array
            if (indexCheck(reference, node) == -1) {
                strcpy(reference[count], node);   // Store the node name
                heuristic[count] = heuristicVal;   // Store the heuristic value
                count++;
            }
        }

        // Stop reading when we reach the end marker
        if (strcmp(node, "-1") == 0) {
            break;  
        }
    }

    *numVertices = count;  // Update the number of vertices
    rewind(fp);  // Reset file pointer to read adjacency information

    // Read adjacency information
    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(line, "-1\n") == 0) {
            break;  // Stop reading if the end marker is found
        }

        if (sscanf(line, "%s %*d %d %s", node, &edgeWeight, adjNode) == 3) {
            int nodeIndex = indexCheck(reference, node);
            int adjIndex = indexCheck(reference, adjNode);

            if (nodeIndex != -1 && adjIndex != -1) {
                adjMatrix[nodeIndex][adjIndex] = edgeWeight;  // Store the edge weight in the matrix
            }
        }
    }

    fclose(fp);
    return 1;
}


/*
   a. Purpose: Writes the vertex information and degrees to a file named "TRAVERSALS.TXT"
   b. Parameters:
      - char *filename: The name of the input file (not used in this function)
      - char reference[MAX_ROWS][MAX_COLS]: The array containing the vertex names.
      - int heuristic[MAX_ROWS]: The array containing heuristic values.
      - int adjMatrix[MAX_ROWS][MAX_COLS]: The adjacency matrix containing edge weights.
      - int numVertices: The number of vertices in the graph.
   c. Return type: Void
*/
void createTraversal(char *filename, char reference[MAX_ROWS][MAX_COLS],
                     int heuristic[MAX_ROWS], int adjMatrix[MAX_ROWS][MAX_COLS],
                     int numVertices) {

    FILE *fp;
    int i, j;

    fp = fopen("TRAVERSALS.TXT", "w");
    fprintf(fp, "\n");

    // Print vertex names, heuristic values, and adjacency matrix (edge weights)
    for (i = 0; i < numVertices; i++) {
        fprintf(fp, "Vertex: %s, Heuristic: %d\n", reference[i], heuristic[i]);
        fprintf(fp, "Edges: ");
        for (j = 0; j < numVertices; j++) {
            if (adjMatrix[i][j] != 0) {
                fprintf(fp, "%s (Weight: %d) ", reference[j], adjMatrix[i][j]);
            }
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "\n");
    fclose(fp);
}
