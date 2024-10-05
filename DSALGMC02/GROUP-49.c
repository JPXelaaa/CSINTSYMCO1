/* ror

[DATA STRUCTURE IMPLEMENTATION - ADJACENCY MATRIX]
We decided to make use of an adjacency matrix to implement the DFS and BFS
algorithms. We created a 2D array to store the adjacency matrix, representing
the connections between vertices. For the DFS implementation, we utilized a
recursive approach, where each vertex's adjacency list was accessed via the
matrix to explore unvisited vertices. In the BFS implementation, we employed a
queue to manage the vertices to be explored, using the adjacency matrix to
enqueue unvisited adjacent vertices. This approach allowed us to efficiently
traverse the graph and perform the necessary searches while maintaining clear
and straightforward data structures for storing and accessing graph information.

[BRIEF DESCRIPTION OF PROGRAM ALGORITHM]
The program reads an undirected graph from a .TXT file and performs both
Breadth-First Search (BFS) and Depth-First Search (DFS) traversals. It starts by
prompting the user for the filename of the graph and asks for the starting
vertex of the traversals. Through reading the file, a 2D array is initialized to
store the adjacency matrix of the graph, representing the connection between the
vertices. This allows us to efficiently manage and access vertex connections.
For the BFS traversal, the program uses a queue to explore vertices level by
level, ensuring that all vertices at the current depth are visited before
proceeding to the next level. On the other hand, the DFS traversal is
implemented using a stack or recursion to ensure that each vertex is explored
before backtracking. The program marks visited vertices to avoid reprocessing
and efficiently tracks traversal paths using the adjacency matrix. Once both
traversals are complete, the results, including vertex degrees, BFS order, and
DFS order, are written to an output file named "TRAVERSALS.TXT". This output
provides a detailed view of the graph�s structure and the sequences of the
traversals.

We created a 2D array to store the adjacency matrix, representing the
connections between vertices.

[PROGRAM ERRORS]
  N/A

*/



#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "BFS.c"
#include "DFS.c"
#include "FileHandling.c"



int main() { 

  FILE *fp; // FILE POINTER
  char filename[50]; // TO RECEIVE FILENAME INPUT
  int numVertices; // TO STORE THE TOTAL NUM OF VERTICES (FIRST NUMBER IN GRAPH.TXT)
  char reference[MAX_ROWS][MAX_COLS] = {{0}}; // TO ASSIGN A NAME TO AN INDEX (FIRST RUN)
  int graph[MAX_ROWS][MAX_COLS] = {{0}}; // OVERALL VERTEX INFORMATION STORER (SECOND RUN)
  int vertexDegree[MAX_ROWS] = {0}; // COUNTS THE DEGREE OF EACH VERTEX ACCORDING TO INDEX
  char startVertex[MAX_NAME_LEN];
  


  printf("Input filename: ");
    printf("yes, it works!");
  
  scanf("%s", filename);

  if ((fp = fopen(filename, "r")) == NULL) {
    printf("%s not found. \n", filename);
    return 0;
  }

  printf("Input start vertex for the traversal: ");
  scanf("%s", startVertex);

  if(readIDsFromFile(filename, reference, graph, startVertex, vertexDegree, &numVertices) == -1)
  {
    return 0;
  } // read the graph data in GRAPH.txt

  fclose(fp);
  
  createTraversal(filename, reference, vertexDegree, numVertices);
  
  BFS(reference, graph, numVertices, startVertex, fp);

  DFS(reference, graph, numVertices, startVertex, fp);
  
  fclose(fp);

    
  return 0;
}
