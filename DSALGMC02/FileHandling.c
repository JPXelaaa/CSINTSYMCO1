#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "FileHandling.h"


int indexCheck(char reference[MAX_ROWS][MAX_COLS], char temp[50]){
  int i;
  for (i = 0; i < MAX_ROWS; i++){
    if(strcmp(reference[i], temp) == 0){
      return i;
    }
  }
  return -1;
}

/*
     a. Purpose: Reads vertex IDs and their adjacency information from a file and populates the graph and vertex degree arrays.
     b. Parameters:
        - char *filename: The name of the file to read from.
        - char names[MAX_ROWS][MAX_COLS][MAX_NAME_LEN]: The 3D array to store the vertex IDs and adjacency information.
        - int vertexDegree[MAX_ROWS]: The array to store the degree of each vertex.
        - int *numVertices: Pointer to an integer to store the number of vertices.
     c. Return type: int
*/

int readIDsFromFile(char *filename, char reference[MAX_ROWS][MAX_COLS],
                     int names[MAX_ROWS][MAX_COLS], char startVertex[MAX_NAME_LEN],
                     int vertexDegree[MAX_ROWS], int *numVertices) {

  FILE *fp = fopen(filename, "r");
  char temp[50];
  int row = 0;
  int col = 0;
  int count = 0;
  int vertexCount = 0;
  int next = 0;
  char line[256];
  char check[50];
  int i;
  char lowerStartVertex[MAX_NAME_LEN];
  char lowerGraphVertex[MAX_NAME_LEN];
  int checker = -1;

  if (fp == NULL) {
    printf("Unable to open file\n");
    return 0;
  }

  fscanf(fp, "%d", numVertices); // reads the number of vertices


  //----------------------------FIRST ITERATION--------------------------------------
  while (fgets(line, sizeof(line), fp)) {
    if (sscanf(line, "%s", temp) == 1) {

            strcpy(reference[count], temp);
            count++;
        } 
    }

  fseek(fp, 2, SEEK_SET);


  strcpy(lowerStartVertex, startVertex);
  to_lowercase(lowerStartVertex);

  // Find startVertex index
  for(i = 0; i < *numVertices; i++){
      strcpy(lowerGraphVertex, reference[i]);
      to_lowercase(lowerGraphVertex);

      if(strcmp(lowerGraphVertex, lowerStartVertex) == 0){
          checker = i;
          break;
      }
  }

  if(checker == -1){
      printf("Vertex %s not found\n", startVertex);
      return -1;
  }

//------------------SECOND ITERATION-------------------------------------
  while (fscanf(fp, "%s", temp) != EOF || *numVertices != row) {

    if(next == 0)
    {
      strcpy(check, temp);
      next = 1;
    }

    if (strcmp(temp, "-1") == 0) {
      vertexDegree[row] = vertexCount-1;  // set the vertex degree
      row++;
      vertexCount = 0;
      vertexDegree[row] = 0;
      col = 0;
      next = 0;
      if (row >= MAX_ROWS) {
        printf("Exceeded maximum rows limit\n");
        break;
      }
    }

    else {
      vertexCount++;
      if(strcmp(temp, check) != 0)
      {
      //  printf("temp: %s, check: %s, \n", temp, check);
        names[row][indexCheck(reference, temp)] = 1;  // assign adjacency matrix index to 1 indicating adjacency
      }
      col++;
      if (col >= MAX_COLS) {
        printf("Exceeded maximum columns limit in row %d\n", row);
        break;
      }
    }
  }
  return 1;
}
/*
     a. Purpose: Writes the traversal information to a file named "TRAVERSALS.TXT"
     b. Parameters:
        - char *filename: The name of the input file (not used in this function)
        - char graph[MAX_ROWS][MAX_COLS][MAX_NAME_LEN]: The 3D array containing the graph                                                           information
        - int vertexDegree[MAX_ROWS]: The array containing the degree of each vertex
        - int numVertices: The number of vertices in the graph
    c. Return type: Void
*/
void createTraversal(char *filename, char reference[MAX_ROWS][MAX_COLS],
                     int vertexDegree[MAX_ROWS], int numVertices){

      FILE *fp;
      int i;

      fp = fopen("TRAVERSALS.TXT", "w");
      fprintf(fp, "\n");

      for (i = 0; i < numVertices; i++) {
        fprintf(fp, "%s   %d", reference[i], vertexDegree[i]); // write the vertex and its degree to the TRAVERSAL.TXT file                                                            
        fprintf(fp, "\n");
      }
      fprintf(fp, "\n");
   }
