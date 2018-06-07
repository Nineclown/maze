#pragma once
#include <stdio.h>
#include "util.h"
#include "gen_maze.h"
#include "gen_graph.h"
#include "astar.h"
#include "dfs.h"
#include "bfs.h"
#include "dijkstra.h"
#include "rhand.h"

int al_cost[5];
double al_time[5];

void rh_run();
void dfs_run();
void bfs_run();
void dijk_run();
void astar_run();
int main();