#include <stdio.h>
#include <string.h>
#include "BFS.h"

void backtrackPath(int parent[], int goalIndex, char reference[MAX_ROWS][MAX_COLS]) {
    int path[MAX_ROWS];
    int pathLength = 0;
    int currentIndex = goalIndex;

    // Reconstruct the path from the goal to the start
    while (currentIndex != -1) {
        path[pathLength++] = currentIndex;
        currentIndex = parent[currentIndex];
    }

    // Print the path from start to goal
    printf("Shortest Path to goal: ");
    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%s ", reference[path[i]]);
    }
    printf("\n");
}

void BFS(char reference[MAX_ROWS][MAX_COLS], int graph[MAX_ROWS][MAX_COLS], int numVertices, int startIndex, int goalIndex) {
    int i, j;
    int visited[MAX_ROWS] = {0};  // Track visited nodes
    int queue[MAX_ROWS];
    int front = 0, rear = 0;
    int currentIndex;

    // Array to track the order of visited nodes
    int visitedOrder[MAX_ROWS];
    int orderCount = 0;

    int parent[MAX_ROWS];  // To keep track of the path
    for (i = 0; i < MAX_ROWS; i++) {
        parent[i] = -1;  // Initialize parent array with -1
    }

    queue[rear++] = startIndex;  // Enqueue the start vertex
    visited[startIndex] = 1;  // Mark the start vertex as visited

    printf("Start Vertex: %s, Goal Vertex: %s\n", reference[startIndex], reference[goalIndex]);

    // BFS traversal
    while (front != rear) {
        currentIndex = queue[front++];  // Dequeue the next vertex

        // Debug: Show current vertex
        printf("Visiting: %s\n", reference[currentIndex]);  
        visitedOrder[orderCount++] = currentIndex;

        // Check if the goal node is reached
        if (currentIndex == goalIndex) {
            printf("Goal node %s found!\n", reference[goalIndex]);
            backtrackPath(parent, goalIndex, reference); // Call backtracking here
            return;  // Stop searching if the goal is found
        }

        // Collect unvisited adjacent nodes
        int tempVertices[MAX_ROWS];
        int tempCount = 0;

        for (j = 0; j < numVertices; j++) {
            if (graph[currentIndex][j] > 0 && !visited[j]) {  // There is a connection and it's unvisited
                tempVertices[tempCount++] = j;  // Store the adjacent vertex
            }
        }

        // Check for direct neighbors to the goal node
        for (j = 0; j < tempCount; j++) {
            if (tempVertices[j] == goalIndex) {
                // If goal is directly reachable from currentIndex
                parent[goalIndex] = currentIndex;
                printf("Direct path to goal found through %s\n", reference[currentIndex]);
                backtrackPath(parent, goalIndex, reference); // Call backtrack
                return; // Exit after finding the direct path
            }
        }

        // Sort collected vertices alphabetically (Bubble Sort for simplicity)
        for (i = 0; i < tempCount - 1; i++) {
            for (j = 0; j < tempCount - i - 1; j++) {
                if (strcmp(reference[tempVertices[j]], reference[tempVertices[j + 1]]) > 0) {
                    // Swap vertices based on alphabetical order
                    int temp = tempVertices[j];
                    tempVertices[j] = tempVertices[j + 1];
                    tempVertices[j + 1] = temp;
                }
            }
        }

        // Enqueue the sorted vertices and set the parent for path reconstruction
        for (i = 0; i < tempCount; i++) {
            int adjVertex = tempVertices[i];
            if (!visited[adjVertex]) { // Only enqueue if not visited
                queue[rear++] = adjVertex;  // Enqueue the adjacent node
                parent[adjVertex] = currentIndex;  // Set parent for path reconstruction
                visited[adjVertex] = 1; // Mark as visited when enqueuing
                printf("Enqueuing: %s\n", reference[adjVertex]);  
            }
        }
    }

    // Print all visited nodes at the end
    printf("Visited nodes in order: ");
    for (i = 0; i < orderCount; i++) {
        printf("%s ", reference[visitedOrder[i]]);
    }
    printf("\n");

    // If the goal node was not found
    if (currentIndex != goalIndex) {
        printf("Goal node %s not reachable from %s\n", reference[goalIndex], reference[startIndex]);
    }
}
