#ifndef __DFS_H_
#define __DFS_H_

#include "gen_graph.h"
#include "main.h"

int count;
Array *result;
int DFS(Graph * graph, int start);
int DFS_Runner(Graph * graph, int start, Array * visited, Array * stack);
int dfs_cost(Array * visited);
void DFS_AddNeighbor(Graph *graph, int vt_name, Array *neighbor, Array *result);
int DFS_CheckVisited(Array *visited, Vertex *target);
#endif