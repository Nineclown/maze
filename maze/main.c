#include "util.h"
#include "gen_maze.h"
#include "gen_graph.h"
#include "main.h"

int main() {
	//start maze.
	Maze_Generating(1, 1);

	//start game
	//runMiniGame();
	Graph_Generating();

	//Delete_Maze(maze);
	//Delete_Graph(maze_graph);
	return 0;

}

