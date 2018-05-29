#include "Graph.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

Edge *New_Edge(Vertex ep1, Vertex ep2, int weight) {
	Edge *edge = 0;
	edge = (Edge *)malloc(sizeof(Edge));
	edge->ep1 = ep1;
	edge->ep2 = ep2;
	edge->weight = weight;
	return edge;
}

Vertex Edge_AnOther(Edge *edge, Vertex pt) {
	if (strcmp(edge->ep1, pt) == 0) {
		return edge->ep2;
	}

	if (strcmp(edge->ep2, pt) == 0) {
		return edge->ep1;
	}
	return "";
}

int Edge_Include(Edge *edge, Vertex pt) {
	return (strcmp(edge->ep1, pt) == 0) || (strcmp(edge->ep2, pt) == 0);
}

Graph *New_Graph() {
	Graph *graph = 0;
	graph = (Graph *)malloc(sizeof(Graph));
	graph->vertexs = New_Array();
	graph->edges = New_Array();

	return graph;
}

void Delete_Graph(Graph *graph) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		free(edge);
	}

	Delete_Array(graph->vertexs);
	Delete_Array(graph->edges);
	free(graph);
}

int Graph_AddVertex(Graph *graph, Vertex pt) {

	if (Graph_ExistVertex(graph, pt)) {
		return 0;
	}

	Array_PushBack(graph->vertexs, (Element)pt);
	return 1;
}

int Graph_AddEdge(Graph *graph, Vertex ep1, Vertex ep2, int weight) {

	if (Graph_ExistVertex(graph, ep1) && Graph_ExistVertex(graph, ep2)) {
		Edge *edge = 0;
		if (Graph_ExistEdge(graph, ep1, ep2)) {
			return 0;
		}
		edge = New_Edge(ep1, ep2, weight);
		Array_PushBack(graph->edges, edge);

		return 1;
	}

	return 0;
}

int Graph_ExistVertex(Graph *graph, Vertex pt) {
	Iterator seek = 0, end = 0;
	Vertex stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		stored_pt = (Vertex)(*seek);

		if (strcmp(stored_pt, pt) == 0) {
			return 1;
		}
	}
	return 0;
}

int Graph_ExistEdge(Graph *graph, Vertex ep1, Vertex ep2) {
	Iterator seek = 0, end = 0;
	Edge *stored_eg = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		stored_eg = (Edge *)(*seek);
		if (Edge_Include(stored_eg, ep1) && Edge_Include(stored_eg, ep2)) {
			return 1;
		}
	}
	return 0;
}

void Graph_View(Graph *graph) {
	Graph_ViewVertexs(graph);
	Graph_ViewEdges(graph);
}

void Graph_ViewVertexs(Graph *graph) {

	Iterator seek = 0, end = 0;
	Vertex pt = 0;
	printf("정점 개수:%d\n", graph->vertexs->usage);
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		pt = (Vertex)(*seek);
		printf("%s\n", pt);
	}
}

void Graph_ViewEdges(Graph *graph) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	printf("간선 개수:%d\n", graph->edges->usage);
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		printf("(%s ,%s):%d\n", edge->ep1, edge->ep2, edge->weight);
	}
}

void Graph_FindNeighvor(Graph *graph, Vertex ep, Array *neighvor) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, ep)) {
			Vertex opt;
			opt = Edge_AnOther(edge, ep);
			Array_PushBack(neighvor, (Element)opt);
		}
	}
}

int Graph_GetWeight(Graph *graph, Vertex ep1, Vertex ep2) {

	Iterator seek = 0, end = 0;
	Edge *edge = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);
	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, ep1) && Edge_Include(edge, ep2)) {
			return edge->weight;
		}
	}

	return -1;
}