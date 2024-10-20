#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "FileHandling.h"

#define MAX_NODES 50

// good job !! <3 gets ko ung code kahet ganyan comments -phlip

void greedyBestFirstSearch(int startIndex, int goalIndex, int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS], int numVertices, char reference[MAX_ROWS][MAX_COLS]) {
    int openList[MAX_ROWS], closedList[MAX_ROWS] = {0}; // openList for neighbors, closedList for visited
    int parent[MAX_ROWS]; // to keep track of the path
    int openListCount = 0;
    int currentNode;
    int minIndex = 0; // index of node in openList with smallest heuristic
    double minDistance; // smallest heuristic value in openList
    double distance;

    //Variables por da calculation of da cost path
    float totalCostPath = 0;
    int fromNode;
    int toNode;
    float minutesTotalCostPath;

	int i, j;
	int finalPath[MAX_ROWS]; //contains the final path 
    int pathLength = 0; //for counting the number of nodes in the final path
    int isInOpenList = 0;

    char label; // To be used to show the label of the node you are currently in (FOR READABILITY)
	
	openList[openListCount++] = startIndex; // u put da startIndex in da openList
    parent[startIndex] = -1; // start node has no parent

    printf("Debug: openListCount = %d\n", openListCount);

    label = reverseIndexCheck(reference, startIndex);

    printf("Start Index: %c, Goal Index: %d\n", label, goalIndex);
    
    while (openListCount > 0) {
        // Find node in openList with the lowest heuristic value
        minDistance = calculateEuclideanDistance(coords[openList[0]], coords[goalIndex]); // heuristic of start node
        minIndex = 0;

        for (i = 1; i < openListCount; i++) {
            distance = calculateEuclideanDistance(coords[openList[i]], coords[goalIndex]);
            if (distance < minDistance) {
                minDistance = distance;
                minIndex = i;
            }
        }

        // set current node to the node w the smallest heuristic
        currentNode = openList[minIndex];
        label = reverseIndexCheck(reference, currentNode); // Changed the current node to display label

        printf("Current Node: %c, Min Distance: %.2f\n", label, minDistance);

        // check if we have reached the goal
        if (currentNode == goalIndex) {
            //printing of the path
            for (j = goalIndex; j != -1; j = parent[j]) {
                finalPath[pathLength++] = j; //collects the nodes of the path from the goal back to the start (backtracking toh in a way)
            }
            printf("\nFinal Path: ");
            for (i = pathLength - 1; i >= 0; i--) {
                printf("%s ", reference[finalPath[i]]); // should print them in the correct order now in letters (wah so cool)
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
            return; //path found wahoo
        }

        // you place da currentNode from openList to closedList
        closedList[currentNode] = 1; //make the 0 to 1 (boolean)
        for (i = minIndex; i < openListCount - 1; i++) {
            openList[i] = openList[i + 1]; // remove da node from openList by moving the values to the left 
        }
        openListCount--;
        
        //exploring da neighbors of the current node nlang here loop yes
        
        for(i = 0; i < numVertices; i++){
            if(adjMatrix[currentNode][i] != 0 && !closedList[i]){
                // add da neighbor sa openList if wala pa don
                isInOpenList = 0;
                for(j = 0; j < openListCount; j++){
                    if (openList[j] == i){
                        isInOpenList = 1;
                        break;
                    }
                }
                if(!isInOpenList){
                    openList[openListCount++] = i;
                    parent[i] = currentNode; // u set the parent of the current node
                }
            }
        }
    }
    
    printf("goal aint found /in Chrytel voice"); // for accuracy - philip
}
