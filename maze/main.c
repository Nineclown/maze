#include "util.h"
#include "gen_maze.h"

int main() {
	int i = 0, j = 0;
	//Graph *graph = New_Graph();
	//Array *neighbor = New_Array();

	//start maze.
	genMaze(1, 1);

	//start game
	//runMiniGame();
	initMaze();
	draw();
	printf("is it? %s", maze[1 + 1 * width].c);

	
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

