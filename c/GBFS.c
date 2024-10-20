/*
function GreedyBestFirstSearch(Graph, start_node, goal_node)
{
    Create a priority queue (min-heap) to store nodes based on their heuristic values
    PriorityQueue pq;

    Initialize all nodes to have infinite heuristic values
    foreach node in Graph
        node.heuristic_value = INFINITY;

     Set the heuristic value of the start node (typically to zero or calculated heuristic)
    start_node.heuristic_value = heuristic(start_node, goal_node);

    Push the start node to the priority queue
    pq.push(start_node);

    Create an array to keep track of visited nodes
    bool visited[] = {false};

     Main loop of the algorithm
    while (!pq.empty())
    {
         Get the node with the lowest heuristic value
        current_node = pq.pop();

         Mark the current node as visited
        visited[current_node] = true;

         If the goal node is found, return the path or indicate success
        if (current_node == goal_node)
        {
            return "Goal found!";
        }

         Iterate through all neighbors of the current node
        foreach neighbor in current_node.neighbors
        {
             If the neighbor has not been visited
            if (!visited[neighbor])
            {
                 Calculate the heuristic value for the neighbor
                neighbor.heuristic_value = heuristic(neighbor, goal_node);

                 Add the neighbor to the priority queue
                pq.push(neighbor);
            }
        }
    }

     If the loop ends without finding the goal node, return failure
    return "Goal not found";
}

 Example of a heuristic function (e.g., Euclidean distance)
function heuristic(node, goal_node)
{
    return sqrt(pow((node.x - goal_node.x), 2) + pow((node.y - goal_node.y), 2));
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "FileHandling.h"

#define MAX_NODES 50



void greedyBestFirstSearch(int startIndex, int goalIndex, int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS], int numVertices) {
    int openList[MAX_ROWS], closedList[MAX_ROWS] = {0}; // openList for neighbors, closedList for visited
    int parent[MAX_ROWS]; // to keep track of the path
    int openListCount = 0;
    int currentNode;
    int minIndex = 0; // index of node in openList with smallest heuristic
    double minDistance; // smallest heuristic value in openList
    double distance;

    int i, j;
    int finalpath[MAX_ROWS]; //contains the final path 
    int pathLength = 0; //for counting the number of nodes in the final path
	
    openList[openListCount++] = startIndex; // u put da startIndex in da openList
    parent[startIndex] = -1; // start node has no parent
    
    while (openListCount > 0) 
	{
        // Find node in openList with the lowest heuristic value
        minDistance = calculateEuclideanDistance(coords[openList[0]], coords[goalIndex]); // heuristic of start node
        minIndex = 0;

        for (i = 1; i < openListCount; i++) 
		{
            distance = calculateEuclideanDistance(coords[openList[i]], coords[goalIndex]);
            if (distance < minDistance) {
                minDistance = distance; 
                minIndex = i;
            }
        }

        // set current node to the node w the smallest heuristic
        currentNode = openList[minIndex];

        // check if we have reached the goal
        if (currentNode == goalIndex) {
            //printing of the path
            for (j = goalIndex; j != -1; j = parent[j]) {
                path[pathLength++] = j; //collects the nodes of the path from the goal back to the start (backtracking toh in a way)
            }
            for (i = pathLength - 1; i >= 0; i--) {
                printf("%d ", path[i]); // should print them in the correct order now 
            }
            printf("\n");
            return; //path found wahoo
        }

        // you place da currentNode from openList to closedList
        closedList[currentNode] = 1; //make the 0 to 1 (boolean)
        for (i = minIndex; i < openListCount - 1; i++) {
            openList[i] = openList[i + 1]; // remove da node from openList by moving the values to the left 
        }
        openListCount--;
        
        //exploring da neighbors of the current node nlang here loop yes 
        
    }
    
    
    
    return -1 // if no goal node is found
}
