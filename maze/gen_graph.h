#ifndef __GEN_GRAPH_H_
#define __GEN_GRAPH_H_

#include <stdio.h>
#include <Windows.h>
#include "util.h"
#include "gen_maze.h"
#include "Array.h"

typedef struct _vertex {
	int name;
	int x, y;
}Vertex;
typedef struct _edge {
	Vertex vt1;
	Vertex vt2;
	int weight;
}Edge;
typedef struct _graph {
	Array *vertexs;
	Array *edges;
}Graph;

Graph *maze_graph;
int NUM;
int COUNT;
Array *vertexs;

int Maze_ReInit();

int Maze_FindDir(Node *n);
int Graph_SetVnE(Node * n);
Node *Graph_Link(Node * n);
int Graph_Generating();
Graph *New_Graph();
Vertex *New_Vertex(int name, int x, int y);
Edge *New_Edge(Vertex vt1, Vertex vt2, int weight);
void Delete_Graph(Graph *graph);
int Graph_AddVertex(Graph *graph, int name, int x, int y);
Vertex *Graph_GetVertex(Graph * graph, int x, int y);
int Graph_AddEdge(Graph *graph, Vertex vt1, Vertex vt2, int weight);
int Graph_ExistVertex(Graph *graph, int x, int y);
Vertex *Graph_GetVertexByName(Graph *graph, int vt_name);
int Graph_ExistEdge(Graph *graph, Vertex vt1, Vertex vt2);
int Edge_Include(Edge * edge, int vt_name);
Vertex *Edge_AnOther(Edge * edge, int vt_name);
void Graph_FindNeighbor(Graph * graph, int vt_name, Array * neighbor);
Vertex * Graph_getVertexByXY(Graph * graph, int x, int y);
void Graph_ViewVerexs(Graph *graph);
void Array_View(Array * array);
void Graph_ViewEdges(Graph *graph);
#endif