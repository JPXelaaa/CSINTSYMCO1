#ifndef ASTAR_H
#define ASTAR_H

#include "FileHandling.h"

void aStar(int start, int goal, int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS], int numVertices);

#endif