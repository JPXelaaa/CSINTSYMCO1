#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "BFS.h"



/*
     a. Purpose: Convert string to lowercase
     b. Parameters:
        - char *string: String to be converted to lowercase
    c. Return type: Void
*/
void to_lowercase(char *string) {
  int i;
  for (i = 0; string[i]; i++) {
    string[i] = tolower(string[i]);
  }
}

/*
     a. Purpose: Performs a Breadth-First-Search Algorithm on graph given by GRAPH.txt
     b. Parameters:
        - char reference[MAX_ROWS][MAX_COLS]: The array containing vertex names
        - int graph[MAX_ROWS][MAX_COLS]: The adjency matrix representing the graph
        - int numVertices: The number of vertices in the graph
        - char *startVertex: The starting vertex of the BFS traversal
        - FILE *fp: The file pointer to write the BFS traversal result
     c. Return type: Void
*/

void BFS(char reference[MAX_ROWS][MAX_COLS], int graph[MAX_ROWS][MAX_COLS], int numVertices, char *startVertex, FILE *fp){
    int i, j, temp;
    int visited[MAX_ROWS] = {0};
    int queue[MAX_ROWS];
    int front = 0, rear = 0;
    int startIndex = -1;
    int currentIndex;
    char lowerStartVertex[MAX_NAME_LEN];
    char lowerGraphVertex[MAX_NAME_LEN];
        
    strcpy(lowerStartVertex, startVertex);
    to_lowercase(lowerStartVertex);

    // Find startVertex index
    for(i = 0; i < numVertices; i++){
        strcpy(lowerGraphVertex, reference[i]);
        to_lowercase(lowerGraphVertex);

        if(strcmp(lowerGraphVertex, lowerStartVertex) == 0){
            startIndex = i;
            break;
        }
    }

    if(startIndex == -1){
        printf("Vertex %s not found\n", startVertex);
        return;
    }

    visited[startIndex] = 1;
    queue[rear++] = startIndex;

    while(front != rear){
        currentIndex = queue[front++];       
        fprintf(fp, "%s ", reference[currentIndex]);

        int candidates[MAX_ROWS];
        int candidateCount = 0;

        for (j = 0; j < numVertices; j++){
            if(graph[currentIndex][j] == 1 && !visited[j]) {
                candidates[candidateCount++] = j;
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
        
        for(j = 0; j < candidateCount; j++){
                queue[rear++] = candidates[j];
                visited[candidates[j]] = 1;
        }
    }
    fprintf(fp, "\n\n");
}

