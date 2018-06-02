#include "util.h"
#include "gen_maze.h"
#include "gen_graph.h"
#include "main.h"

int main() {
	Node *start, *last;
	maze_graph = New_Graph();
	vertexs = New_Array();
	Array_SetSize(vertexs, 0, 0);

	//start maze.
	Maze_Generating(1, 1);

	//start game
	//runMiniGame();
	Maze_ReInit();
	Maze_Draw();

	start = maze + 1 + 1 * width;
	start->parent = start;
	last = start;
	while ((last = Graph_Generating(last)) != start);
	Graph_ViewVerexs(maze_graph);
	Graph_ViewEdges(maze_graph);
	


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

