#ifndef __GRAPH_H_
#define __GRAPH_H_

#include "Array.h"

typedef const char * Vertex;

typedef struct _edge {
	Vertex ep1;
	Vertex ep2;
	int weight;
}Edge;

typedef struct _graph {
	Array *vertexs;
	Array *edges;
}Graph;

Graph *New_Graph();
void Delete_Graph(Graph *graph);
int Graph_AddVertex(Graph *graph, Vertex pt);
int Graph_AddEdge(Graph *graph, Vertex ep1, Vertex ep2, int weight);
int Graph_ExistVertex(Graph *graph, Vertex pt);
int Graph_ExistEdge(Graph *graph, Vertex ep1, Vertex ep2);
void Graph_View(Graph *graph);
void Graph_ViewVertexs(Graph *graph);
void Graph_ViewEdges(Graph *graph);
void Graph_FindNeighvor(Graph *graph, Vertex ep, Array *neighvor);
int Graph_GetWeight(Graph *graph, Vertex ep1, Vertex ep2);

#endif