#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50

// Struct to hold x and y coordinates of each node
typedef struct {
    int x;
    int y;
} Coordinates;

// Function to check the index of a node in the reference array
int indexCheck(char reference[MAX_ROWS][MAX_COLS], char temp[MAX_NAME_LEN]);

// Function to calculate Euclidean distance between two nodes
double calculateEuclideanDistance(Coordinates node1, Coordinates node2);

// Function to read vertex IDs, coordinates, and adjacency information from a file
int readIDsFromFile(char *filename, char reference[MAX_ROWS][MAX_COLS],
                    int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS],
                    int *numVertices);

// Function to write traversal data to a file
void createTraversal(char *filename, char reference[MAX_ROWS][MAX_COLS],
                     Coordinates coords[MAX_ROWS], int adjMatrix[MAX_ROWS][MAX_COLS],
                     int numVertices);

#endif
