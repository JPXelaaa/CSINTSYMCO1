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



void greedyBestFirstSearch(int startIndex, int goal, int adjMatrix[MAX_ROWS][MAX_COLS], Coordinates coords[MAX_ROWS], int numVertices){
    int openList[MAX_ROWS], closedList[MAX_ROWS] = {0}; //openList for neighbors, closedList for visited
    int openListCount = 0;
    int currentNode;
    int minIndex = 0; // assigns index of node in openList w smallest heuristic
    double minDistance; // assigns smallest heuristic value sa lahat ng nodes na nasa openList
    double distance;

    openList[openListCount++] = startIndex; // u put da startIndex in da openList


    printf("Path: ");

    while (openListCount > 0){
        // Find node sa openList w lowest heuristic value
        minDistance = calculateEuclideanDistance(coords[openList[0]], coords[goal]); // heuristic of start node

        for(int i = 1; i < openListCount; i++){
            distance = calculateEuclideanDistance(coords[openList[i]], coords[goal]);
            if (distance < minDistance){
                minDistance = distance; 
                minIndex = i;
            }
        }
        // set current node to the node w the smallest heuristic
        currentNode = openList[minIndex];

    }
}
