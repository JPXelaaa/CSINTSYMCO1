#include <stdio.h>
#include <string.h>
#include "DFS.h"

void DFS(char reference[MAX_ROWS][MAX_COLS], int graph[MAX_ROWS][MAX_COLS], int numVertices, int startIndex, int goalIndex) {
    int visited[MAX_ROWS] = {0};  // Track visited nodes
    int stack[MAX_ROWS];           // Stack for DFS
    int top = -1;                  // Top of the stack
    int currentIndex;

    // Array to track the order of visited nodes
    int visitedOrder[MAX_ROWS];
    int orderCount = 0;

    // Array to keep track of parents
    int parent[MAX_ROWS];
    for (int i = 0; i < numVertices; i++) {
        parent[i] = -1; // Initialize all parents to -1 (no parent)
    }

    // Push the start vertex onto the stack
    stack[++top] = startIndex;  
    visited[startIndex] = 1;     // Mark the start vertex as visited

    printf("Start Vertex: %s, Goal Vertex: %s\n", reference[startIndex], reference[goalIndex]);

    // DFS traversal
    while (top != -1) {
        currentIndex = stack[top--];  // Pop the top vertex from the stack

        // Debug: Show current vertex
        printf("Visiting: %s\n", reference[currentIndex]);  
        visitedOrder[orderCount++] = currentIndex;

        // Check if the goal node is reached
        if (currentIndex == goalIndex) {
            printf("Goal node %s found!\n", reference[goalIndex]);
            break;  // Stop searching if the goal is found
        }

        // Collect unvisited adjacent nodes
        int tempVertices[MAX_ROWS];
        int tempCount = 0;

        for (int j = 0; j < numVertices; j++) {
            if (graph[currentIndex][j] > 0 && !visited[j]) {  // There is a connection and it's unvisited
                tempVertices[tempCount++] = j;  // Store the index of the adjacent node
                parent[j] = currentIndex; // Set the parent of this node
            }
        }

        // Sort the collected vertices alphabetically using Bubble Sort
        for (int i = 0; i < tempCount - 1; i++) {
            for (int j = 0; j < tempCount - i - 1; j++) {
                if (strcmp(reference[tempVertices[j]], reference[tempVertices[j + 1]]) > 0) {
                    // Swap indices based on alphabetical order
                    int temp = tempVertices[j];
                    tempVertices[j] = tempVertices[j + 1];
                    tempVertices[j + 1] = temp;
                }
            }
        }

        // Push sorted vertices onto the stack in reverse order (to visit them in alphabetical order)
        for (int i = tempCount - 1; i >= 0; i--) {
            int adjVertex = tempVertices[i];
            stack[++top] = adjVertex;  // Push the adjacent node onto the stack
            visited[adjVertex] = 1;     // Mark as visited
            printf("Pushing: %s\n", reference[adjVertex]);  
        }
    }

    // Print all visited nodes at the end
    printf("Visited nodes in order: ");
    for (int i = 0; i < orderCount; i++) {
        printf("%s ", reference[visitedOrder[i]]);
    }
    printf("\n");

    // If the goal node was found, display the path
    if (visited[goalIndex]) {
        printf("Path from %s to %s: ", reference[startIndex], reference[goalIndex]);
        int path[MAX_ROWS];
        int pathCount = 0;

        // Reconstruct the path
        for (int v = goalIndex; v != -1; v = parent[v]) {
            path[pathCount++] = v;
        }

        // Print the path in reverse order
        for (int i = pathCount - 1; i >= 0; i--) {
            printf("%s", reference[path[i]]);
            if (i != 0) {
                printf(" -> "); // Print arrow between nodes
            }
        }
        printf("\n");
    } else {
        // If the goal node was not found
        printf("Goal node %s not reachable from %s\n", reference[goalIndex], reference[startIndex]);
    }
}
