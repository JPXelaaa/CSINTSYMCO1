/*

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

typedef struct Node{
    int node; //Node index
    int gCost; //cost going to this node
    int hCost; //Heuristic cost
    int fCost; //Total cost
    struct Node* parent; //Address of Parent node
} Node;



void aStar(int startIndex, int goalIndex, int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS], int numVertices) {

int openList[MAX_NODES], closedList[MAX_NODES];
Node nodeData[MAX_NODES];
int openCount = 0;

// Initialize node data
    for (int i = 0; i < numVertices; i++) {
        nodeData[i].node = i;
        nodeData[i].gCost = 0;
        nodeData[i].hCost = 0;
        nodeData[i].fCost = 0;
    }


nodeData[startIndex].gCost = 0;
nodeData[startIndex].hCost = calculateEuclideanDistance(coords[startIndex], coords[goalIndex]);
nodeData[startIndex].fCost = 0;

openList[openCount++] = startIndex;

while (openCount > 0){

        for (int i=1; i<openCount; i++){
            
        }
    }
    return -1; // IF NO GOAL NODE IS FOUND
}

