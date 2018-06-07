#ifndef __RHS_H_
#define __RHS_H_

#include "gen_graph.h"
#include "main.h"

void RHS_Right(char * dir);

void RHS_Left(char * dir);

void RHS_Forward(int * x, int * y, char dir);

int RHS_Wall_Ahead(Node *maze, int x, int y, char dir);

int RHS_FindEnd(int x, int y);

void RHS(int x, int y, char dir);

#endif
