#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50


int indexCheck(char reference[MAX_ROWS][MAX_COLS], char temp[50]);
int readIDsFromFile(char *filename, char reference[MAX_ROWS][MAX_COLS],
                     int names[MAX_ROWS][MAX_COLS], char startVertex[MAX_NAME_LEN],
                     int vertexDegree[MAX_ROWS], int *numVertices);
void createTraversal(char *filename, char reference[MAX_ROWS][MAX_COLS],
                     int vertexDegree[MAX_ROWS], int numVertices);
