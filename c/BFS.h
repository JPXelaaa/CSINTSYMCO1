#ifndef BFS_H
#define BFS_H

#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50

void backtrackPath(int parent[], int goalIndex, int adjMatrix[MAX_ROWS][MAX_COLS], char reference[MAX_ROWS][MAX_COLS]);
void BFS(char reference[MAX_ROWS][MAX_COLS], int graph[MAX_ROWS][MAX_COLS], int numVertices, int startIndex, int goalIndex);

#endif
