#ifndef __GEN_GRAPH_H_
#define __GEN_GRAPH_H_

#include <stdio.h>
#include <Windows.h>
#include "util.h"
#include "gen_maze.h"

typedef const char * Vertex;

typedef struct _edge {
	Vertex ep1;
	Vertex ep2;
	int weight;
}Edge;

int NUM;

int findDirection(Node *n);

#endif