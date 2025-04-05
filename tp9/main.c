#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int writeGraphViz(Graph *g, char *filename) {
    // Check if graph or filename is null
    if (g == NULL || filename == NULL) {
        fprintf(stderr, "Error: Null graph or filename provided.\n");
        return 0;
    }

    // Open file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return 0;
    }

    // Write the DOT format header
    fprintf(fp, "digraph {\n");

    // Iterate through the graph vertices and edges
    Vertex *currentVertex = g->first;
    while (currentVertex != NULL) {
        Edge *currentEdge = currentVertex->connect.first;
        while (currentEdge != NULL) {
            // Write the edge in DOT format
            fprintf(fp, "    %c -> %c [label=\"%d\"];\n",
                    currentVertex->label, currentEdge->v->label, currentEdge->dist);
            currentEdge = currentEdge->next_e;
        }
        currentVertex = currentVertex->next_v;
    }

    // Close the DOT graph definition
    fprintf(fp, "}\n");

    // Close the file
    fclose(fp);
    return 1;
}


int initDijkstra(Graph * g, Vertex * v1) {
    Vertex * current = g->first;
    while (current != NULL) {
        current->already_visited = 0;
        current ->dist_to_origin = MY_INFINITY;
        //Clear any previous path
        current->path.first = current->path.last = current->path.current = NULL;

        current = current->next_v;
    }
    v1->dist_to_origin = 0;
    return 1;
}

// Helper function to find minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

void updatePath(Vertex *currentVertex, Vertex *neighbor, Edge *connectingEdge) {
    // Free the existing path of the neighbor
    Edge *oldPath = neighbor->path.first;
    while (oldPath != NULL) {
        Edge *next = oldPath->next_e;
        free(oldPath);
        oldPath = next;
    }
    neighbor->path.first = neighbor->path.current = neighbor->path.last = NULL;

    // Copy the path from the current vertex
    Edge *srcEdge = currentVertex->path.first;
    while (srcEdge != NULL) {
        Edge *newEdge = (Edge *)malloc(sizeof(Edge));
        if (newEdge == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return;
        }
        *newEdge = *srcEdge; // Copy edge details
        newEdge->next_e = NULL;

        // Append the edge to the neighbor's path
        if (neighbor->path.last == NULL) {
            neighbor->path.first = neighbor->path.last = newEdge;
        } else {
            neighbor->path.last->next_e = newEdge;
            neighbor->path.last = newEdge;
        }
        srcEdge = srcEdge->next_e;
    }

    // Add the final edge leading to the neighbor
    Edge *finalEdge = (Edge *)malloc(sizeof(Edge));
    if (finalEdge == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }
    *finalEdge = *connectingEdge; // Copy the edge
    finalEdge->next_e = NULL;

    // Append the final edge
    if (neighbor->path.last == NULL) {
        neighbor->path.first = neighbor->path.last = finalEdge;
    } else {
        neighbor->path.last->next_e = finalEdge;
        neighbor->path.last = finalEdge;
    }
}

void updateNeighborsDistances(Vertex *currentVertex) {
    // Iterate through all edges of the current vertex
    Edge *currentEdge = currentVertex->connect.first;
    while (currentEdge != NULL) {
        Vertex *neighbor = currentEdge->v;
        int newDistance = currentVertex->dist_to_origin + currentEdge->dist;

        // Update the neighbor's distance if a shorter path is found
        if (newDistance < neighbor->dist_to_origin) {
            neighbor->dist_to_origin = newDistance;

            // Use the helper function to update the path
            updatePath(currentVertex, neighbor, currentEdge);
        }

        // Move to the next edge
        currentEdge = currentEdge->next_e;
    }
}


Vertex* findNextVertex(Graph* g) {
    Vertex* minVertex = NULL;
    int minDistance = MY_INFINITY;

    // Look through all vertices
    Vertex* current = g->first;
    while (current != NULL) {
        // If this vertex is unvisited and has a shorter distance
        if (!current->already_visited &&
            current->dist_to_origin < minDistance) {
            minDistance = current->dist_to_origin;
            minVertex = current;
            }
        current = current->next_v;
    }

    return minVertex;
}

int shortestPathDijkstra(Graph *g, char label1, char label2) {
    // Step 1: Find the start (v1) and end (v2) vertices using findVertexGraph
    Vertex *v1 = findVertexGraph(g, label1);
    Vertex *v2 = findVertexGraph(g, label2);

    // If either vertex is not found, return an error
    if (v1 == NULL || v2 == NULL) {
        return -1; // Error: One or both vertices not found
    }

    // Step 2: Initialize Dijkstra's algorithm
    initDijkstra(g, v1);

    // Step 3: Iterate until all vertices are visited or we reach the target
    Vertex *currentVertex = v1;
    while (currentVertex != NULL) {
        // Update distances and paths of neighbors
        updateNeighborsDistances(currentVertex);

        // Mark the current vertex as visited
        currentVertex->already_visited = 1;

        // Stop if we reached the target vertex
        if (currentVertex == v2) {
            break;
        }

        // Select the next vertex with the smallest distance
        currentVertex = findNextVertex(g);
    }

    // Step 4: Return the shortest distance to the target vertex
    return v2->dist_to_origin;
}


int main()
{

    Graph g;
    int dist_to_origin;
    int resultWrite;

    initGraph(&g);

    addVertexGraph(&g,'A');
    addVertexGraph(&g,'B');
    addVertexGraph(&g,'C');
    addVertexGraph(&g,'D');
    addVertexGraph(&g,'E');
    addVertexGraph(&g,'F');
    addVertexGraph(&g,'G');
    addVertexGraph(&g,'H');
    addVertexGraph(&g,'I');
    addVertexGraph(&g,'J');
    addVertexGraph(&g,'K');
    addVertexGraph(&g,'L');
    addVertexGraph(&g,'M');

    addEdgeGraph(&g, 'A', 'B', 10);
    addEdgeGraph(&g, 'B', 'C', 10);
    addEdgeGraph(&g, 'A', 'C', 10);


    addEdgeGraph(&g, 'D', 'E', 10);
    addEdgeGraph(&g, 'E', 'F', 5);
    addEdgeGraph(&g, 'F', 'E', 5);
    addEdgeGraph(&g, 'F', 'G', 40);
    addEdgeGraph(&g, 'G', 'H', 30);
    addEdgeGraph(&g, 'E', 'M', 30);
    addEdgeGraph(&g, 'M', 'L', 2);
    addEdgeGraph(&g, 'M', 'K', 5);
    addEdgeGraph(&g, 'K', 'G', 5);
    addEdgeGraph(&g, 'D', 'J', 25);
    addEdgeGraph(&g, 'J', 'I', 30);
    addEdgeGraph(&g, 'I', 'H', 5);

    printGraph(&g);

    resultWrite = writeGraphViz(&g,"graph.dot");
    printf("Result of graph.dot overwriting: %d \n",resultWrite);


    dist_to_origin = shortestPathDijkstra(&g,'D','H');
    printf("Shortest path from %c to %c : %dkm\n",'D','H',dist_to_origin);
    printf("This path is \n");
    printEdgeList(&findVertex(&g,'H')->path);

    deleteGraph(&g);

    return EXIT_SUCCESS;
}


