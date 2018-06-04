#ifndef __BFS_H_
#define __BFS_H_

#include "gen_graph.h"

int BFS(Graph *graph, int start);

void BFS_AddNeighbor(Graph * graph, int vt_name, Array * neighbor, Array * visited);

int BFS_CheckVisited(Array * visited, Vertex * target);

#endif