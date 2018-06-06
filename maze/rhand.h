#ifndef __RHD_H_
#define __RHD_H_

#include "gen_graph.h"
#include "main.h"

void right(int *dir);
void left(int *dir);
void forward(int *x, int *y, int dir);
Node* Wall_ahead(Node *maze, int x, int y, int dir);
int still_in_maze(int x, int y);
void right_hand(Node *maze, int x, int y, int dir);


#endif
