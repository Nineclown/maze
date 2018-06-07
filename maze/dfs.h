#ifndef __DFS_H_
#define __DFS_H_

#include "gen_graph.h"
#include "main.h"

Array *result;
int DFS(Graph * graph, int start);
int DFS_Runner(Graph * graph, int start, Array * visited, Array * stack);
int DFS_Routing(Array * visited);
int DFS_GetCost(Array * route);
void DFS_AddNeighbor(Graph * graph, Vertex * vt, Array * stack, Array * visited);
int DFS_CheckVisited(Array *visited, Vertex *target);
#endif