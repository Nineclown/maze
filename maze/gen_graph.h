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

int Maze_ReInit();
int Maze_FindDir(Node *n);

Graph *New_Graph();
Vertex *New_Vertex(int name, int x, int y);
Edge *New_Edge(Vertex vt1, Vertex vt2, int weight);
void Delete_Graph(Graph *graph);
int Graph_AddVertex(Graph *graph, int name, int x, int y);
int Graph_AddEdge(Graph *graph, Vertex vt1, Vertex vt2, int weight);
int Graph_ExistVertex(Graph *graph, int vt_name);
int Graph_ExistEdge(Graph *graph, Vertex vt1, Vertex vt2);
int Edge_Include(Edge * edge, Vertex vt);

void Graph_ViewVerexs(Graph *graph);

#endif