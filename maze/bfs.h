#ifndef __BFS_H_
#define __BFS_H_

#include "main.h"
#include "gen_graph.h"

int BFS(Graph *graph, int start);

int BFS_Routing(Array * visited);

int BFS_GetCost(Array * route);

void BFS_AddNeighbor(Graph * graph, Vertex * vt, Array * neighbor, Array * visited);

int BFS_CheckVisited(Array * visited, Vertex * target);

#endif