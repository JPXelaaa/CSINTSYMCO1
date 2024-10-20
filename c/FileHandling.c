#include <stdio.h>
#include <string.h>
#include <math.h>
#include "FileHandling.h"

// Function to check the index of a node in the reference array
int indexCheck(char reference[MAX_ROWS][MAX_COLS], char temp[MAX_NAME_LEN], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(reference[i], temp) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to calculate Euclidean distance between two nodes
double calculateEuclideanDistance(Coordinates node1, Coordinates node2) {
    return sqrt(pow(node2.x - node1.x, 2) + pow(node2.y - node1.y, 2));
}

// Function to read vertex IDs, coordinates, and adjacency information from a file
int readIDsFromFile(char *filename, char reference[MAX_ROWS][MAX_COLS],
                    int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS],
                    int *numVertices) {
    FILE *fp = fopen(filename, "r");
    char node[MAX_NAME_LEN], adjNode[MAX_NAME_LEN];
    int count = 0;
    char line[256];
    int x, y, edgeWeight;

    if (fp == NULL) {
        printf("Unable to open file\n");
        return 0;
    }

    // Initialize adjacency matrix to 0 (no connections by default)
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    // Read node definitions and coordinates
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%s %d %d %d %s", node, &x, &y, &edgeWeight, adjNode) == 5) {
            // Check if the node already exists in the reference array
            if (indexCheck(reference, node, count) == -1) {
                strcpy(reference[count], node);   // Store the node name
                coords[count].x = x;             // Store the x-coordinate
                coords[count].y = y;             // Store the y-coordinate
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

        if (sscanf(line, "%s %*d %*d %d %s", node, &edgeWeight, adjNode) == 3) {
            int nodeIndex = indexCheck(reference, node, count);
            int adjIndex = indexCheck(reference, adjNode, count);

            if (nodeIndex != -1 && adjIndex != -1) {
                adjMatrix[nodeIndex][adjIndex] = edgeWeight;  // Store the edge weight in the matrix
            }
        }
    }

    fclose(fp);
    return 1;
}
