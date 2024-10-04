#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "DFS.h"
#include "BFS.h"


/*
     a. Purpose: Perform a Depth-First Search (DFS) on a graph starting from a given vertex using recursion.
     b. Parameters:
        - int v: The current vertex in the DFS traversal.
        - int visited[]: An array to track visited vertices.
        - char reference[MAX_ROWS][MAX_COLS]: An array containing vertex names.
        - int graph[MAX_ROWS][MAX_COLS]: The adjacency matrix of the graph.
        - int numVertices: The total number of vertices in the graph.
        - FILE *fp: A file pointer to log the traversal output.
    c. Return type: void
*/
void DFSRecursion(int v, int visited[], char reference[MAX_ROWS][MAX_COLS],
                  int graph[MAX_ROWS][MAX_COLS], int numVertices, FILE *fp) {
  int i, j, temp;
  visited[v] = 1;
  
  fprintf(fp, "%s ", reference[v]);
  
  int candidates[MAX_ROWS];
  int candidateCount = 0;

  for (i = 0; i < numVertices; i++){
      if(graph[v][i] == 1 && !visited[i]) {
          candidates[candidateCount++] = i;
      }
  }
  
  if(candidateCount > 0){
    for (i = 0; i < candidateCount - 1; i++) {
        for (j = i + 1; j < candidateCount; j++) {
            if (strcmp(reference[candidates[i]], reference[candidates[j]]) > 0) {
                temp = candidates[i]; 
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }
        }
    }
  }

  for (i = 0; i < candidateCount; i++) {
      if(!visited[candidates[i]])
      DFSRecursion(candidates[i], visited, reference, graph, numVertices, fp);
  }
}



/*
     a. Purpose: Initialize and start a Depth-First Search (DFS) on a graph from a specified start vertex.
     b. Parameters:
        - char reference[MAX_ROWS][MAX_COLS]: An array containing vertex names.
        - int graph[MAX_ROWS][MAX_COLS]: The adjacency matrix of the graph.
        - int numVertices: The total number of vertices in the graph.
        - char *startVertex: The name of the vertex to start the DFS from.
        - FILE *fp: A file pointer to log the traversal output.
    c. Return type: void
*/
void DFS(char reference[MAX_ROWS][MAX_COLS], int graph[MAX_ROWS][MAX_COLS],
         int numVertices, char *startVertex, FILE *fp) {
  int i;
  int visited[MAX_ROWS] = {0};
  int startIndex = -1;
  char lowerStartVertex[MAX_NAME_LEN];
  char lowerGraphVertex[MAX_NAME_LEN];

  strcpy(lowerStartVertex, startVertex);
  to_lowercase(lowerStartVertex);

  // Find startVertex index
  for (i = 0; i < numVertices; i++) {
    strcpy(lowerGraphVertex, reference[i]);
    to_lowercase(lowerGraphVertex);

    if (strcmp(lowerGraphVertex, lowerStartVertex) == 0) {
      startIndex = i;
      break;
    }
  }
  if (startIndex == -1) {
    printf("Vertex %s not found\n", startVertex);
    return;
  }

  DFSRecursion(startIndex, visited, reference, graph, numVertices, fp);
  fprintf(fp, "\n");
}
