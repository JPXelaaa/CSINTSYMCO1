#define MAX_ROWS 50
#define MAX_COLS 50
#define MAX_NAME_LEN 50

void to_lowercase(char *str);
void BFS(char reference[MAX_ROWS][MAX_COLS], int graph[MAX_ROWS][MAX_COLS], int numVertices, int startIndex, int goalIndex);

