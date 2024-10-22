#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "FileHandling.h"

#define MAX_NODES 50



void greedyBestFirstSearch(int startIndex, int goalIndex, int adjMatrix[MAX_ROWS][MAX_COLS], 
                           Coordinates coords[MAX_ROWS], 
                           int numVertices, 
                           char reference[MAX_ROWS][MAX_COLS]) {
                            
    int openList[MAX_ROWS], closedList[MAX_ROWS] = {0}; // openList for neighbors, closedList for visited
    int parent[MAX_ROWS];
    int openListCount = 0;
    int currentNode;
    int minIndex = 0; // Index of node in openList with smallest heuristic
    double minDistance; // Smallest heuristic value in openList
    double distance;

    float totalCostPath = 0;
    int fromNode;
    int toNode;
    float minutesTotalCostPath;

	int i, j;
	int finalPath[MAX_ROWS]; //Contains the final path
    int pathLength = 0; //Counting number of nodes in the final path
    int isInOpenList = 0;
	
	openList[openListCount++] = startIndex;
    parent[startIndex] = -1; // Start node has no parent

    printf("Start Index: %s, Goal Index: %s\n", reference[startIndex], reference[goalIndex]);
    
    while (openListCount > 0) {
        // Find node in openList with the lowest heuristic value
        minDistance = calculateEuclideanDistance(coords[openList[0]], coords[goalIndex]); // Heuristic of start node
        minIndex = 0;

        for (i = 1; i < openListCount; i++) {
            distance = calculateEuclideanDistance(coords[openList[i]], coords[goalIndex]);
            if (distance < minDistance) {
                minDistance = distance;
                minIndex = i;
            }
        }

        
        currentNode = openList[minIndex];
        printf("Current Node: %s, Min Distance: %.2f\n", reference[currentNode], minDistance);

        // Check if goal is reached
        if (currentNode == goalIndex) {
            
            for (j = goalIndex; j != -1; j = parent[j]) {
                finalPath[pathLength++] = j; // Backtracking
            }
            printf("\nFinal Path: ");
            for (i = pathLength - 1; i >= 0; i--) {
                printf("%s ", reference[finalPath[i]]);
            }
            printf("\n");

            // Calculate the total cost of the path
            totalCostPath = 0;
            for (i = pathLength - 1; i > 0; i--) {
                fromNode = finalPath[i];
                toNode = finalPath[i - 1];
                totalCostPath += adjMatrix[fromNode][toNode];
            }

            minutesTotalCostPath = totalCostPath/60;
            printf("\nTotal Cost of the Path: %.2f seconds (%.2f minutes)\n", totalCostPath, minutesTotalCostPath);
            return; //Path Found
        }

        // Mark currentNode as visited
        closedList[currentNode] = 1;
        for (i = minIndex; i < openListCount - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openListCount--;
        
        
        // Explore the neighbors
        for(i = 0; i < numVertices; i++){
            if(adjMatrix[currentNode][i] != 0 && !closedList[i]){
                isInOpenList = 0;
                for(j = 0; j < openListCount; j++){
                    if (openList[j] == i){
                        isInOpenList = 1;
                        break;
                    }
                }
                if(!isInOpenList){
                    openList[openListCount++] = i;
                    parent[i] = currentNode;
                }
            }
        }
    }
    
    printf("Goal Not Found");
}
