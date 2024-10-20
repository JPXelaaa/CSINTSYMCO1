/*
n' refers to the child of n I believe?

GAAAH

Algorithm A-Star

Initialize OPEN list (to the empty list)
Initialize CLOSED list (to the empty list)

Create goal node; call it node_goal
Create start node; call it node_start

Add node_start to the OPEN list

while the OPEN list is not empty
{
 Remove node n off the OPEN list with the lowest f(n)
 Add n to the CLOSED list
 IF n is the same as node_goal
 
we have found the solution; return Solution(n)

 ELSE: Generate each successor node n' of n
 for each successor node n' of n
 {
 Set the parent of n' to n
 Set h(n') to be the heuristically estimate distance to node_goal
 Set g(n') to be g(n) plus the cost to get to n' from n
 Set f(n') to be g(n') plus h(n')
 if n' is on the OPEN list and the existing one is as good or better
 then discard n' and continue
 if n' is on the CLOSED list and the existing one is as good or better
 then discard n' and continue
 Remove occurrences of n' from OPEN and CLOSED
 Add n' to the OPEN list
 }
}
return failure (if we reach this point, we’ve searched all reachable nodes and still
haven’t found the solution, therefore one doesn’t exist)

Reference Link:
https://robotics.caltech.edu/wiki/images/e/e0/Astar.pdf
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "A*.h"
#include "FileHandling.h"

#define MAX_NODES 50

void printSolutionPath(Node* goalNode, char reference[MAX_ROWS][MAX_COLS]) {
     if (goalNode == NULL) {
        printf("No path found.\n");
        return;
    }

    // Backtrack from the goal node to the start node using parent pointers
    Node* currentNode = goalNode;
    int path[MAX_NODES];
    int pathLength = 0;

    // Trace the path by following parent pointers
    while (currentNode != NULL) {
        path[pathLength++] = currentNode->node; // Store the node index in the path
        currentNode = currentNode->parent;      // Move to the parent node
    }

    // Print the path in reverse (from start to goal) with labels
    printf("Path found: ");
    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%s", reference[path[i]]);       // Print the node label using the reference array
        if (i > 0) 
            printf(" -> ");
    }
    printf("\n");
}

void aStar(int startIndex, int goalIndex, int adjMatrix[MAX_ROWS][MAX_COLS], 
           Coordinates coords[MAX_ROWS], 
           int numVertices, 
           char reference[MAX_ROWS][MAX_COLS]) {

    int openList[MAX_NODES], closedList[MAX_NODES];
    Node nodeData[MAX_NODES];
    int openCount = 0, closedCount = 0; // Used for the counting of OPEN and CLOSED list contents

    // Initialize node data
        for (int i = 0; i < numVertices; i++) {
            nodeData[i].node = i;
            nodeData[i].gCost = 0;
            nodeData[i].hCost = 0;
            nodeData[i].fCost = 0;
            nodeData[i].parent = NULL; // To initialize no parent
        }


    nodeData[startIndex].gCost = 0;
    nodeData[startIndex].hCost = calculateEuclideanDistance(coords[startIndex], coords[goalIndex]);
    nodeData[startIndex].fCost = nodeData[startIndex].hCost;

    openList[openCount++] = startIndex;

    while (openCount > 0){

            // Find the node in the OPEN list with the lowest fCost (f(n))
            int currentNode = openList[0];
            int currentIndex = 0;

            for (int i = 1; i < openCount; i++) {
                if (nodeData[openList[i]].fCost < nodeData[currentNode].fCost) {
                    currentNode = openList[i];
                    currentIndex = i;
                }
            }
        // remove current node from OPEN list and add it to CLOSED list
        openCount--;
        for (int i = currentIndex; i < openCount; i++) {
            openList[i] = openList[i + 1];
        }
            closedList[closedCount++] = currentNode;

        // Condition statement for if the current node is the goal, return the solution
        if (currentNode == goalIndex) {
            printf("Path found to the goal node.\n");
            printSolutionPath(&nodeData[currentNode], reference);
            return;
        }
    /*
    The other half of the code below will be responsible for generating an processing the successor nodes of the current 
    node being evaluted.


    */
    // This loop will generate over all node successors (neighbor nodes connected by edges)
        for (int i = 0; i < numVertices; i++) {
        //--------------------------------------I-Cannot-Think-Anymore-From:Philip-------------------------I will be back
            if (adjMatrix[currentNode][i] > 0) { // There is an edge
                int successor = i; 
                    // If node is in the CLOSED list, skip it
                    int inClosed = 0;
                    for (int j = 0; j < closedCount; j++) {
                        if (closedList[j] == successor) {
                            inClosed = 1;
                            break;
                        }
                    }
                    if (inClosed) continue;

                    // Calculate gCost, hCost, and fCost for successor
                    int gCost = nodeData[currentNode].gCost + adjMatrix[currentNode][successor];
                    int hCost = calculateEuclideanDistance(coords[successor], coords[goalIndex]);
                    int fCost = gCost + hCost;
             
                    //check if successor is in the open list:
                    int inOpen = 0;
                    for (int j = 0; j < openCount; j++) {
                        if (openList[j] == successor) {
                            inOpen = 1;
                            break;
                        }
                    }
                    // If successor is not in the OPEN list or found a better path (lower fCost)
                    if (!inOpen || fCost < nodeData[successor].fCost) {
                        nodeData[successor].gCost = gCost;
                        nodeData[successor].hCost = hCost;
                        nodeData[successor].fCost = fCost;
                        nodeData[successor].parent = &nodeData[currentNode];

                    // Add the successor to the OPEN list if it's not there
                    if (!inOpen) {
                        openList[openCount++] = successor;
                    }
                       
            }
       }
    }
    printf("No Goal Node Found!"); // IF NO GOAL NODE IS FOUND
}

