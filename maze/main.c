#include "util.h"
#include "gen_maze.h"
#include "gen_graph.h"

int main() {
	int i = 0, j = 0;
	maze_graph = New_Graph();
	Array *neighbor = New_Array();

	//start maze.
	Maze_Generating(1, 1);

	//start game
	//runMiniGame();
	Maze_ReInit();
	Maze_Draw();
	printf("is it? %s", maze[1 + 1 * width].c);
	Graph_ViewVerexs(maze_graph);
	
	//시작 값 초기화.
	//maze->parent = start.






	//Graph_AddVertex(graph, "S");
	//Graph_AddEdge(graph, "J", "K", 3);

	//Graph_FindNeighvor(graph, "A", neighbor);
	//Iterator seek = 0, end = 0;
	//Vertex pt = 0;
	//seek = Array_Begin(neighbor);
	//end = Array_End(neighbor);

	//for (seek = seek; seek != end; ++seek) {
	//	pt = (Vertex)(*seek);
	//	printf("%s\n", pt);
	//}


	////Graph_View(graph);

	//Delete_Graph(graph);
	return 0;

}

