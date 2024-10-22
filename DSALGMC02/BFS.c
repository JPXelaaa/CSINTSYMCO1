#include <stdio.h>
#include <string.h>
#include "BFS.h"

// #define MAX_ROWS 100
// #define MAX_COLS 100

void BFS(char reference[MAX_ROWS][MAX_COLS], int graph[MAX_ROWS][MAX_COLS], int numVertices, int startIndex, int goalIndex) {
    int i, j;
    int visited[MAX_ROWS] = {0};
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

    visited[startIndex] = 1;  // Mark the start vertex as visited
    queue[rear++] = startIndex;  // Enqueue the start vertex

    printf("Start Vertex: %s, Goal Vertex: %s\n", reference[startIndex], reference[goalIndex]);

    // Variables to hold total costs
    int totalPathCost = 0;

    // BFS traversal
    while (front != rear) {
        currentIndex = queue[front++];  // Dequeue the next vertex
        printf("Visiting: %s\n", reference[currentIndex]);  // Debug: Show current vertex
        visitedOrder[orderCount++] = currentIndex;

        // Check if the goal node is reached
        if (currentIndex == goalIndex) {
            printf("Goal node %s found!\n", reference[goalIndex]);
            break;  // Stop searching if the goal is found
        }

        // Collect unvisited adjacent nodes and their weights
        int tempVertices[MAX_ROWS];
        int tempWeights[MAX_ROWS];
        int tempCount = 0;

        for (j = 0; j < numVertices; j++) {
            if (graph[currentIndex][j] > 0 && !visited[j]) {  // There is a connection and it's unvisited
                tempVertices[tempCount] = j;  // Store the adjacent vertex
                tempWeights[tempCount] = graph[currentIndex][j];  // Store its weight
                tempCount++;
            }
        }

        // Simple sorting of collected vertices based on weights (Bubble Sort for simplicity)
        for (i = 0; i < tempCount - 1; i++) {
            for (j = 0; j < tempCount - i - 1; j++) {
                if (tempWeights[j] > tempWeights[j + 1]) {
                    // Swap weights
                    int weightTemp = tempWeights[j];
                    tempWeights[j] = tempWeights[j + 1];
                    tempWeights[j + 1] = weightTemp;

                    // Swap corresponding vertices
                    int vertexTemp = tempVertices[j];
                    tempVertices[j] = tempVertices[j + 1];
                    tempVertices[j + 1] = vertexTemp;
                }
            }
        }

        // Enqueue the sorted vertices and mark them for later processing
        for (i = 0; i < tempCount; i++) {
            queue[rear++] = tempVertices[i];  // Enqueue the adjacent node
            parent[tempVertices[i]] = currentIndex;  // Set parent for path reconstruction
            // Do not mark as visited yet, will mark when expanded
            printf("Enqueuing: %s (Weight: %d)\n", reference[tempVertices[i]], tempWeights[i]);  // Debug: Show enqueued vertex
        }

        // Mark the current node as visited after processing its adjacent nodes
        visited[currentIndex] = 1;  // Mark as visited
    }

    // Check if the goal was found and reconstruct the path
    if (currentIndex == goalIndex) {
        // Now reconstruct the path from start to goal
        int path[MAX_ROWS];
        int pathLength = 0;
        currentIndex = goalIndex;

        // Reconstruct the path from the goal to the start
        while (currentIndex != -1) {
            path[pathLength++] = currentIndex;
            currentIndex = parent[currentIndex];
        }

        // Print the path from start to goal and calculate the total path cost
        printf("Path from %s to %s: ", reference[startIndex], reference[goalIndex]);
        for (i = pathLength - 1; i >= 0; i--) {
            printf("%s ", reference[path[i]]);
            // If not the start, add the cost of the edge
            if (i < pathLength - 1) {
                totalPathCost += graph[path[i]][path[i + 1]];  // Add the cost of the edge
            }
        }
        printf("\n");

        // Print total costs
        printf("Total cost of the path: %d\n", totalPathCost);

        // Print all visited nodes at the end
        printf("Visited nodes in order: ");
        for (i = 0; i < orderCount; i++) {
            printf("%s ", reference[visitedOrder[i]]);
        }
        printf("\n");
    } else {
        printf("Goal node %s not reachable from %s\n", reference[goalIndex], reference[startIndex]);
    }
}
