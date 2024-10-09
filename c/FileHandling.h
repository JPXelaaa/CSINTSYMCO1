#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50

// Function to convert strings to lowercase (utility function)
void to_lowercase(char *str);

// Function to check the index of a node in the reference array
int indexCheck(char reference[MAX_ROWS][MAX_COLS], char temp[MAX_NAME_LEN]);

// Function to read vertex IDs, heuristic values, and adjacency information from a file
int readIDsFromFile(char *filename, char reference[MAX_ROWS][MAX_COLS],
                    int names[MAX_ROWS][MAX_COLS], int heuristic[MAX_ROWS],
                    int *numVertices);

// Function to write traversal data to a file
void createTraversal(char *filename, char reference[MAX_ROWS][MAX_COLS],
                     int heuristic[MAX_ROWS], int adjMatrix[MAX_ROWS][MAX_COLS],
                     int numVertices);

#endif
