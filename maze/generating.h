#ifndef __GNR_MAZE_H_
#define __GNR_MAZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct node {
	int x, y; //Node position - little waste of memory, but it allows faster generation
	void *parent; //Pointer to parent node
	char c; //Character to be displayed
	char dirs; //Directions that still haven't been explored
} Node;

Node *nodes; //Nodes array
int width, height; //Maze dimensions

int init(int *x, int *y);
Node * link(Node * n);
void draw();

#endif