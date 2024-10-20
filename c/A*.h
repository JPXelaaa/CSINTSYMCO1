#ifndef ASTAR_H
#define ASTAR_H

#include "FileHandling.h"

typedef struct Node{
    int node; //Node index
    int gCost; //cost going to this node
    int hCost; //Heuristic cost
    float fCost; //Total cost
    struct Node* parent; //Address of Parent node
} Node;

void printSolutionPath(Node* goalNode, char reference[MAX_ROWS][MAX_COLS], float totalCost);

void aStar(int start, int goal, int adjMatrix[MAX_ROWS][MAX_COLS], 
           Coordinates coords[MAX_ROWS], 
           int numVertices, 
           char reference[MAX_ROWS][MAX_COLS]);

#endif