#ifndef GBFS_H
#define GBFS_H

#include "FileHandling.h"

void greedyBestFirstSearch(int start, int goal, int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS], int numVertices);

#endif
